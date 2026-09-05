#include "mainwindow.h"

#include <QApplication>
#include <gst/gst.h>

int main(int argc, char *argv[])
{
    gst_init(&argc, &argv);
    qputenv("QT_QPA_PLATFORM", "xcb");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QCoreApplication::exec();


}
