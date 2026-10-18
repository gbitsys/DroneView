/*
 This class is a bridge between GStreamer and Qt

Implementation of:
Playback logic
Sync between GStreamer and GUI
*/

#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include <QObject>
#include <QString>
#include <QImage>
#include <QUrl>
#include <gst/gst.h>

class GstVideoWidget;

enum class CodecType {
    H264,
    H265,
    VP8,
    VP9,
    Unknown
};

enum class DecodingType {
    Software,
    Hardware,
    Unknown
};

enum class ProtocolType {
    UDP,
    RTP,
    RTSP,
    Unknown
};

class VideoManager : public QObject
{
    Q_OBJECT
public:
    explicit VideoManager(GstVideoWidget *videoWidget, QObject *parent = nullptr);

    static constexpr int DEFAULT_PORT = 5000;
    static constexpr int DEFAULT_LATENCY = 50;
    static constexpr const char* DEFAULT_IP = "127.0.0.1";

    QString getUrlSource() const;
    void setUrlSource(const QString &newUrlSource);

    // for dynamic pipelines
    void setCustomPipeline(const QString &pipelineString);
    QString menuPipelineBuild(CodecType codec, DecodingType decodingType, ProtocolType protocol, const QString &receiverIp);

    int getHeightRes() const;
    void setHeightRes(int newHeightRes);

    int getWidthRes() const;
    void setWidthRes(int newWidthRes);

    bool getPlay() const;
    void setPlay(bool newPlay);

    int getZoom() const;
    void setZoom(int newZoom);

    void setRecording(bool record, const QString &path = "");

signals:
    // Signal that transfers frames to widget
    void newFrameAvailable(const QImage &frame);

private:
    bool isPlaying;
    QString urlSource;
    int heightRes;
    int widthRes;
    int zoom;

    GstVideoWidget *videoWidget;

    // GStreamer objects
    GstElement *pipeline;
    void cleanupPipeline();

    // GStreamer callback which runs when we have a new frame
    // ACHTUNG! this should be static
    static GstFlowReturn onNewSample(GstElement *sink, VideoManager *self);
};

#endif // VIDEOMANAGER_H