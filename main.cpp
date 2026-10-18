#include "mainwindow.h"

#include <QApplication>
#include <gst/gst.h>

int main(int argc, char *argv[])
{
    gst_init(&argc, &argv); // required for GStreamer
    qputenv("QT_QPA_PLATFORM", "xcb"); // force x11

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QCoreApplication::exec();


}
