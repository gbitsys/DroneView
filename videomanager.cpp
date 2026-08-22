#include "videomanager.h"


VideoManager::VideoManager(QVideoWidget *videoWidget, QObject *parent)
    : QObject{parent}
{
    isPlaying = false;
    mediaPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);

    mediaPlayer->setAudioOutput(audioOutput);
    mediaPlayer->setVideoOutput(videoWidget);

}

QString VideoManager::getUrlSource() const
{
    return urlSource;
}

void VideoManager::setUrlSource(const QString &newUrlSource)
{
    urlSource = newUrlSource;
    mediaPlayer->setSource(QUrl::fromLocalFile(urlSource));
}

int VideoManager::getHeightRes() const
{
    return heightRes;
}

void VideoManager::setHeightRes(int newHeightRes)
{
    heightRes = newHeightRes;
}

int VideoManager::getWidthRes() const
{
    return widthRes;
}

void VideoManager::setWidthRes(int newWidthRes)
{
    widthRes = newWidthRes;
}

bool VideoManager::getPlay() const
{
    return isPlaying;
}

void VideoManager::setPlay(bool newPlay)
{
    isPlaying = newPlay;
    if (isPlaying) {
        mediaPlayer->play();
    }
    else {
        mediaPlayer->stop();
    }
}
