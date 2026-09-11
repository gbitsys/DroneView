#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QStackedWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo> // Απαραίτητο για τον έλεγχο ύπαρξης του αρχείου
#include <QMenu>
#include <QActionGroup>
#include "videomanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onZoomChanged(int value);
    void playStream(); // play button for streaming
    void setupResolutionMenu();
    void stopStream();
    void settingsMenu();
    void backPushButton(); // from settings menu back to main
    // acts as a save button too

private:

    Ui::MainWindow *ui;
    QString m_currentResolution = "Auto";
    VideoManager *videoManager;
};
#endif // MAINWINDOW_H
