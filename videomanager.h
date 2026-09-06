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

class VideoManager : public QObject
{
    Q_OBJECT
public:
    explicit VideoManager(GstVideoWidget *videoWidget, QObject *parent = nullptr);

    QString getUrlSource() const;
    void setUrlSource(const QString &newUrlSource);

    // for dynamic pipelines
    void setCustomPipeline(const QString &pipelineString);

    int getHeightRes() const;
    void setHeightRes(int newHeightRes);

    int getWidthRes() const;
    void setWidthRes(int newWidthRes);

    bool getPlay() const;
    void setPlay(bool newPlay);

    int getZoom() const;
    void setZoom(int newZoom);

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