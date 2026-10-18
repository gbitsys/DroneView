#include "videomanager.h"
#include "gstvideowidget.h"
#include <QDebug>
#include <gst/app/gstappsink.h>

VideoManager::VideoManager(GstVideoWidget *videoWidget, QObject *parent)
    : QObject(parent)
    , isPlaying(false)
    , urlSource("")
    , heightRes(0)
    , widthRes(0)
    , videoWidget(videoWidget)
    , pipeline(nullptr)
{
    // Connecting the signal (GStreamer thread) with the widget's slot (ui thread)
    // Note(!): Qt is using automated Qt::QueuedConnection in cross-thread signals.
    if (videoWidget) {
        connect(this, &VideoManager::newFrameAvailable,
                videoWidget, &GstVideoWidget::updateFrame);
    }
}

QString VideoManager::getUrlSource() const {
    return urlSource;
}

void VideoManager::setUrlSource(const QString &newUrlSource) {
    if (urlSource == newUrlSource) return;
    urlSource = newUrlSource;

    // Creation of a dynamic pipeline that reads the URI,
    // converts it to RGB and sends it to appsink
    QString pipelineStr = QString("uridecodebin uri=%1 ! videoconvert ! video/x-raw,format=RGB ! appsink name=mysink emit-signals=true drop=true max-buffers=1")
                              .arg(urlSource);

    setCustomPipeline(pipelineStr);
}

void VideoManager::setCustomPipeline(const QString &pipelineString) {
    cleanupPipeline();

    GError *error = nullptr;
    pipeline = gst_parse_launch(pipelineString.toUtf8().constData(), &error);

    if (error) {
        qWarning() << "GStreamer pipeline error:" << error->message;
        g_error_free(error);
        return;
    }

    // Looking for appsink in pipeline in order to connect the callback
    GstElement *sink = gst_bin_get_by_name(GST_BIN(pipeline), "mysink");
    if (sink) {
        // Connecting the signal "new-sample" of appsink with our static method
        g_signal_connect(sink, "new-sample", G_CALLBACK(onNewSample), this);
        gst_object_unref(sink);
    } else {
        qWarning() << "'appsink' was not found with the name 'mysink' in pipeline!";
    }
}

// ... (other functions) ...

QString VideoManager::menuPipelineBuild(CodecType codec, DecodingType decodingType, ProtocolType protocol, const QString &receiverIp) {
    // 1. Defining depayloader and encoding name based on the codec enum
    QString depayloader;
    QString encodingName;

    switch (codec) {
    case CodecType::H265:
        depayloader = "rtph265depay";
        encodingName = "H265";
        break;
    case CodecType::VP8:
        depayloader = "rtpvp8depay";
        encodingName = "VP8";
        break;
    case CodecType::VP9:
        depayloader = "rtpvp9depay";
        encodingName = "VP9";
        break;
    case CodecType::H264:
    default:
        depayloader = "rtph264depay";
        encodingName = "H264";
        break;
    }

    // 2. Network Source Block (Receiver) using constants
    QString networkSourceBlock = "";
    QString targetIp = receiverIp.isEmpty() ? DEFAULT_IP : receiverIp;

    if (protocol == ProtocolType::RTSP) {
        networkSourceBlock = QString("rtspsrc location=rtsp://%1:%2/live latency=%3 ! %4")
        .arg(targetIp)
            .arg(DEFAULT_PORT)
            .arg(DEFAULT_LATENCY)
            .arg(depayloader);
    } else { // UDP / RTP
        networkSourceBlock = QString("udpsrc port=%1 caps=\"application/x-rtp,media=video,clock-rate=90000,encoding-name=%2,payload=96\" ! "
                                     "rtpjitterbuffer latency=%3 ! %4")
                                 .arg(DEFAULT_PORT)
                                 .arg(encodingName)
                                 .arg(DEFAULT_LATENCY)
                                 .arg(depayloader);
    }

    // 3. Decoder Block (PC / Receiver - based on decodingType)
    QString parser = "";
    QString decoder = "";
    bool isHardwareDecode = (decodingType == DecodingType::Hardware);

    switch (codec) {
    case CodecType::H265:
        parser = "h265parse";
        decoder = isHardwareDecode ? "vaapidecodebin" : "avdec_h265";
        break;
    case CodecType::VP8:
        parser = "";
        decoder = isHardwareDecode ? "vaapidecodebin" : "vp8dec";
        break;
    case CodecType::VP9:
        parser = "";
        decoder = isHardwareDecode ? "vaapidecodebin" : "vp9dec";
        break;
    case CodecType::H264:
    default:
        parser = "h264parse";
        decoder = isHardwareDecode ? "vaapidecodebin" : "avdec_h264";
        break;
    }

    QString teeBlock = parser.isEmpty() ? "tee name=vid_tee" : QString("%1 ! tee name=vid_tee").arg(parser);

    // 4. Sink Block (remains the same)
    QString displayBranch = QString("queue ! %1 ! videocrop name=cropper ! videoconvert ! video/x-raw,format=RGB ! appsink name=mysink emit-signals=true drop=true max-buffers=1 sync=false").arg(decoder);

    // 5. Record Block (remains the same)
    QString recordBranch = "queue ! valve name=rec_valve drop=true ! matroskamux name=rec_mux  ! filesink name=rec_sink async=false location=dummy.mkv";

    // 6. Assembly (remains the same)
    QString finalReceiverPipeline = QString("%1 ! %2 ! %3  vid_tee. ! %4")
                                        .arg(networkSourceBlock)
                                        .arg(teeBlock)
                                        .arg(displayBranch)
                                        .arg(recordBranch);

    qDebug() << "Pipeline: " << finalReceiverPipeline;
    return finalReceiverPipeline;
}

int VideoManager::getHeightRes() const { return heightRes; }
void VideoManager::setHeightRes(int newHeightRes) { heightRes = newHeightRes; }

int VideoManager::getWidthRes() const { return widthRes; }
void VideoManager::setWidthRes(int newWidthRes) { widthRes = newWidthRes; }

bool VideoManager::getPlay() const { return isPlaying; }

int VideoManager::getZoom() const { return zoom; }

void VideoManager::setZoom(int newZoom) {
    zoom = newZoom;

    if (!pipeline) return;

    // Should have this element in pipeline for zoom slider to function
    GstElement *cropper = gst_bin_get_by_name(GST_BIN(pipeline), "cropper");
    if (!cropper) {
        qWarning() << "'cropper' element not found in pipeline!";
        return;
    }

    // zoom: 100 = no zoom , 200 = 2x
    if (widthRes <= 0 || heightRes <= 0) {
        qWarning() << "Width/Height resolution not set, cannot compute zoom crop!";
        gst_object_unref(cropper);
        return;
    }

    double factor = 1.0 - (100.0 / newZoom); // e.g. 200% -> 0.5
    int cropLeftRight = static_cast<int>(widthRes * factor / 2.0);
    int cropTopBottom = static_cast<int>(heightRes * factor / 2.0);

    g_object_set(cropper,
                 "left", cropLeftRight,
                 "right", cropLeftRight,
                 "top", cropTopBottom,
                 "bottom", cropTopBottom,
                 NULL);

    gst_object_unref(cropper);

    qDebug() << "Zoom is now set to:" << newZoom << "% (crop L/R:" << cropLeftRight << "T/B:" << cropTopBottom << ")";
}

void VideoManager::setPlay(bool newPlay) {
    if (isPlaying == newPlay || !pipeline) return;

    isPlaying = newPlay;
    if (isPlaying) {
        gst_element_set_state(pipeline, GST_STATE_PLAYING);
    } else {
        gst_element_set_state(pipeline, GST_STATE_PAUSED); // or GST_STATE_NULL for full stop
    }
}

void VideoManager::cleanupPipeline() {
    if (pipeline) {
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);
        pipeline = nullptr;
    }
}

GstFlowReturn VideoManager::onNewSample(GstElement *sink, VideoManager *self) {
    GstSample *sample;
    // Extracting frame from appsink
    g_signal_emit_by_name(sink, "pull-sample", &sample);

    if (sample) {
        GstBuffer *buffer = gst_sample_get_buffer(sample);
        GstCaps *caps = gst_sample_get_caps(sample);
        GstStructure *structure = gst_caps_get_structure(caps, 0);

        int width, height;
        gst_structure_get_int(structure, "width", &width);
        gst_structure_get_int(structure, "height", &height);

        // Update resolution members
        if (self->widthRes != width || self->heightRes != height) {
            self->widthRes = width;
            self->heightRes = height;
        }

        GstMapInfo map;
        gst_buffer_map(buffer, &map, GST_MAP_READ); //

        // Creating our QImage from raw data coming from GStreamer
        // RGB888 corresponds to video/x-raw, format=RGB which we requested in pipeline
        QImage image(map.data, width, height, QImage::Format_RGB888);

        // Achtung! map.data belongs to GStreamer and will be released
        // We have to deep copy (.copy()) in order for the image to survive until the UI thread
        QImage copiedImage = image.copy();

        gst_buffer_unmap(buffer, &map);
        gst_sample_unref(sample);

        // Calling UI to paint new frame
        emit self->newFrameAvailable(copiedImage);

        return GST_FLOW_OK;
    }
    return GST_FLOW_ERROR;
}

void VideoManager::setRecording(bool record, const QString &path) {
    if (!pipeline) return;

    GstElement *valve = gst_bin_get_by_name(GST_BIN(pipeline), "rec_valve");
    GstElement *sink = gst_bin_get_by_name(GST_BIN(pipeline), "rec_sink");
    GstElement *mux = gst_bin_get_by_name(GST_BIN(pipeline), "rec_mux");

    if (!valve || !sink || !mux) {
        qWarning() << "No recording elements found in pipeline!";
        if(valve) gst_object_unref(valve);
        if(sink) gst_object_unref(sink);
        if(mux) gst_object_unref(mux);
        return;
    }

    if (record) {
        // Restore sink and muxer
        gst_element_set_state(sink, GST_STATE_NULL);
        gst_element_set_state(mux, GST_STATE_NULL);

        // Setting new file
        g_object_set(sink, "location", path.toUtf8().constData(), NULL);

        // Starting and opening the valve
        gst_element_set_state(mux, GST_STATE_PLAYING);
        gst_element_set_state(sink, GST_STATE_PLAYING);
        g_object_set(valve, "drop", FALSE, NULL);

        qDebug() << "Recording started at:" << path;
    } else {
        // Closing valve in order for data stream to close
        g_object_set(valve, "drop", TRUE, NULL);

        // Sending EOS in muxer in order to mkv file to close succesfully
        gst_element_send_event(mux, gst_event_new_eos());
        qDebug() << "Recording stopped";
    }

    gst_object_unref(valve);
    gst_object_unref(sink);
    gst_object_unref(mux);
}

