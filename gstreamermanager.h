#ifndef GSTREAMERMANAGER_H
#define GSTREAMERMANAGER_H

#include <QObject>
#include <QString>
#include <gst/gst.h>

class GstreamerManager : public QObject {
    Q_OBJECT // Απαραίτητο για να έχεις Signals & Slots

public:
    explicit GstreamerManager(QObject *parent = nullptr);
    ~GstreamerManager();

public slots:
    // Το UI καλεί αυτά τα slots όταν ο χρήστης πατάει κουμπιά
    void startPipeline();
    void stopPipeline();

signals:
    // Η κλάση εκπέμπει αυτά τα σήματα για να ενημερώσει το UI
    void errorOccurred(const QString &errorMessage);
    void stateChanged(const QString &newState);
    void endOfStream();

private:
    GstElement *pipeline;
    // Εδώ βάζεις όλες τις εσωτερικές συναρτήσεις (π.χ. bus callbacks)
};

#endif // GSTREAMERMANAGER_H