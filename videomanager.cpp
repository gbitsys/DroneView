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
    // Note: Qt is using automated Qt::QueuedConnection in cross-thread signals.
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

int VideoManager::getHeightRes() const { return heightRes; }
void VideoManager::setHeightRes(int newHeightRes) { heightRes = newHeightRes; }

int VideoManager::getWidthRes() const { return widthRes; }
void VideoManager::setWidthRes(int newWidthRes) { widthRes = newWidthRes; }

bool VideoManager::getPlay() const { return isPlaying; }

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

        GstMapInfo map;
        gst_buffer_map(buffer, &map, GST_MAP_READ);

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