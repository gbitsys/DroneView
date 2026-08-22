#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QVideoWidget>
#include <QtMultimedia>

class VideoManager : public QObject
{
    Q_OBJECT
public:
    explicit VideoManager(QVideoWidget *videoWidget, QObject *parent = nullptr);

    QString getUrlSource() const;
    void setUrlSource(const QString &newUrlSource);

    int getHeightRes() const;
    void setHeightRes(int newHeightRes);

    int getWidthRes() const;
    void setWidthRes(int newWidthRes);

    bool getPlay() const;
    void setPlay(bool newPlay);

    // widget in page index 1 stacked widget
     QVideoWidget* getVideoWidget() const { return videoWidget; }

private:
    QString urlSource;
    QVideoWidget *videoWidget;
    QMediaPlayer *mediaPlayer;
    QAudioOutput *audioOutput;
    int heightRes;
    int widthRes;
    bool isPlaying;

};

#endif // VIDEOMANAGER_H
