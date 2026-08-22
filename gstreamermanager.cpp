#include "gstreamermanager.h"
#include <QDebug>

GstreamerManager::GstreamerManager(QObject *parent)
    : QObject(parent), pipeline(nullptr)
{
    qDebug() << "Ο GstreamerManager δημιουργήθηκε.";
}

GstreamerManager::~GstreamerManager()
{
    qDebug() << "Ο GstreamerManager καταστρέφεται.";
    stopPipeline();
}

void GstreamerManager::startPipeline()
{
    qDebug() << "Κλήθηκε η startPipeline()...";
}

void GstreamerManager::stopPipeline()
{
    qDebug() << "Κλήθηκε η stopPipeline()...";
}