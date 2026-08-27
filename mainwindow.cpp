#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::quit);
    connect(ui->playButton, &QPushButton::clicked, this, &MainWindow::playStream);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopStream);
    connect(ui->resolutionButton, &QPushButton::clicked, this, &MainWindow::setupResolutionMenu);

    // default video before user activates the stream from drone
    QString defaultImage = QCoreApplication::applicationDirPath() + "/wait_image.jpg";
    QString url = "udp://127.0.0.1:5000";

    // Checking if image (in wait mode) exists
    if (QFileInfo::exists(defaultImage)) {
        qDebug() << "Loading default image:" << defaultImage;
        ui->imageLabel->setPixmap(QPixmap(defaultImage));
    } else {
        qDebug() << "Error: Image not found at" << defaultImage;
        ui->imageLabel->setText("No Signal / Waiting for drone stream...");
    }

    videoManager = new VideoManager(ui->videoWidget, this);
    //videoManager->setUrlSource(url);
    videoManager->setUrlSource("sample-5s.mp4"); //sample-5s.mp4

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::quit() {
    qDebug() << "Quitting ...";
    close();
}

void MainWindow::playStream() {
    qDebug() << "Start streaming ...";
    ui->stackedWidget->setCurrentIndex(1);
    videoManager->setPlay(true);

}

void MainWindow::stopStream(){
    qDebug() << "Stop streaming ...";
    ui->stackedWidget->setCurrentIndex(0);
    videoManager->setPlay(false);
}

void MainWindow::setupResolutionMenu() {
    qDebug() << "Resolution";
    QMenu menu(this);

    const QStringList resolutions = {
        "Auto", "2160p 4K", "1440p HD", "1080p HD",
        "720p", "480p", "360p", "240p", "144p"
    };

    QActionGroup *group = new QActionGroup(&menu);
    group->setExclusive(true);

    for (const QString &res : resolutions) {
        QAction *action = menu.addAction(res);
        action->setCheckable(true);
        action->setChecked(res == m_currentResolution);
        group->addAction(action);
    }

    QAction *chosen = menu.exec(
        ui->resolutionButton->mapToGlobal(ui->resolutionButton->rect().bottomLeft())
        );

    if (chosen) {
        m_currentResolution = chosen->text();
        ui->resolutionButton->setText(m_currentResolution.section(' ', 0, 0) + "  \u25BE");

        // \u25BE unicode character for down arrow

        // video quality change here !
        // changeVideoQuality(m_currentResolution);
    }

}