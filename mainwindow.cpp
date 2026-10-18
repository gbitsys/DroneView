#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    //------- Connecting signals and slots --------------
    connect(ui->playButton, &QPushButton::clicked, this, &MainWindow::playStream);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopStream);
    connect(ui->settingsButton, &QPushButton::clicked, this, &MainWindow::settingsMenu);
    connect(ui->backButton, &QPushButton::clicked, this, &MainWindow::backPushButton);
    connect(ui->resolutionButton, &QPushButton::clicked, this, &MainWindow::setupResolutionMenu);
    connect(ui->zoomSlider_2, &QSlider::valueChanged, this, &MainWindow::onZoomChanged);
    connect(ui->screenshotButton, &QPushButton::clicked, this, &MainWindow::takeScreenshot);
    connect(ui->recordButton, &QPushButton::clicked, this, &MainWindow::toggleRecording);
    //----------------------------------------------------

    //------- IP receiver settingsScreen -----------------
    // regex for ipv4 used in settings screen IP text edit
    QRegularExpression ipRegex(
        "^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}"
        "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$"
        );
    QRegularExpressionValidator *ipValidator = new QRegularExpressionValidator(ipRegex, this);
    ui->ipReceiver->setValidator(ipValidator);
    //----------------------------------------------------


    // welcome page image
    QString defaultImage = QCoreApplication::applicationDirPath() + "/wait_image.jpg";

    QString url = "udp://127.0.0.1:5000";

    // Checking if image (in wait mode) exists
    if (QFileInfo::exists(defaultImage)) {
        qDebug() << "Loading default image:" << defaultImage;
        ui->imageLabel->setPixmap(QPixmap(defaultImage));
    } else {
        qDebug() << "Error: Image not found at" << defaultImage;
        ui->imageLabel->setText("Press start for streaming / Settings for more");
    }

    videoManager = new VideoManager(ui->gstVideoWidget, this);

    // Load default UDP/H264 stream automatically
    QString defaultPipeline = videoManager->menuPipelineBuild(CodecType::H264, DecodingType::Software, ProtocolType::UDP, VideoManager::DEFAULT_IP);
    videoManager->setCustomPipeline(defaultPipeline);
}

MainWindow::~MainWindow()
{
    delete ui;
}



//------- waitScreen controls  -----------------------
void MainWindow::playStream() {
    qDebug() << "Start streaming ...";
    ui->stackedWidget->setCurrentIndex(1);
    videoManager->setPlay(true);

}

void MainWindow::settingsMenu()
{
    ui->stackedWidget->setCurrentIndex(2);
}

//----------------------------------------------------

//------- streamScreen controls  -----------------

void MainWindow::stopStream(){
    qDebug() << "Stop streaming ...";
    ui->stackedWidget->setCurrentIndex(0);
    videoManager->setPlay(false);
}

void MainWindow::onZoomChanged(int value)
{
    videoManager->setZoom(value+100);
    qDebug() << "Zoom is now set to: " << value;
}

void MainWindow::setupResolutionMenu() {
    // Requires communication with sender
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

void MainWindow::takeScreenshot()
{
    QImage frame = ui->gstVideoWidget->getCurrentFrame();
    if (frame.isNull()) {
        qWarning() << "No available frame for saving!";
        return;
    }

    QString defaultName = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation) +
                          "/DroneView_" + QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss") + ".jpg";

    QString fileName = QFileDialog::getSaveFileName(this, "Saving frame", defaultName, "Images (*.jpg *.png)");
    if (!fileName.isEmpty()) {
        frame.save(fileName);
        qDebug() << "Screenshot saved:" << fileName;
    }
}

void MainWindow::toggleRecording()
{
    if (!m_isRecording) {
        QString defaultName = QStandardPaths::writableLocation(QStandardPaths::MoviesLocation) +
                              "/DroneRecord_" + QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss") + ".mkv";
        QString fileName = QFileDialog::getSaveFileName(this, "Saving video", defaultName, "Video (*.mkv)");

        if (!fileName.isEmpty()) {
            m_isRecording = true;
            ui->recordButton->setText("Stop Rec");
            ui->recordButton->setStyleSheet("color: red;");
            videoManager->setRecording(true, fileName);
        }
    } else {
        m_isRecording = false;
        ui->recordButton->setText("Record ");
        ui->recordButton->setStyleSheet("");
        videoManager->setRecording(false);
    }
}
//----------------------------------------------------


//------- settingsScreen controls  -----------------
void MainWindow::backPushButton()
{
    // Go back to waiting screen (Also saves user settings)
    ui->stackedWidget->setCurrentIndex(0);

    QString codecStr = ui->codecComboBox->currentText();
    QString transmissionProtocolStr = ui->protocolComboBox->currentText();
    QString decodingTypeStr = ui->decodingTypeCB->currentText();
    QString receiverIp = ui->ipReceiver->text();

    if (codecStr.startsWith("Select") || transmissionProtocolStr.startsWith("Select")) {
        // Invalid settings, do not build pipeline
        return;
    }

    // --- CONVERTING STRINGS TO ENUMS ---
    CodecType codecEnum = CodecType::Unknown;
    if (codecStr.contains("H264")) codecEnum = CodecType::H264;
    else if (codecStr.contains("H265")) codecEnum = CodecType::H265;
    else if (codecStr.contains("VP8")) codecEnum = CodecType::VP8;
    else if (codecStr.contains("VP9")) codecEnum = CodecType::VP9;

    DecodingType decodingEnum = DecodingType::Unknown;
    if (decodingTypeStr == "Hardware") decodingEnum = DecodingType::Hardware;
    else if (decodingTypeStr == "Software") decodingEnum = DecodingType::Software;

    ProtocolType protocolEnum = ProtocolType::Unknown;
    if (transmissionProtocolStr == "UDP") protocolEnum = ProtocolType::UDP;
    else if (transmissionProtocolStr == "RTP") protocolEnum = ProtocolType::RTP;
    else if (transmissionProtocolStr == "RTSP") protocolEnum = ProtocolType::RTSP;
    // -----------------------------------

    // Build and set the new pipeline
    QString pipelineRecv = videoManager->menuPipelineBuild(codecEnum, decodingEnum, protocolEnum, receiverIp);
    videoManager->setCustomPipeline(pipelineRecv);
}
//----------------------------------------------------
