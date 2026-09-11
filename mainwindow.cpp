#include "mainwindow.h"
#include "./ui_mainwindow.h"

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
    //videoManager->setUrlSource("https://gstreamer.freedesktop.org/data/media/sintel_trailer-480p.webm");
    //videoManager->setUrlSource("");
    // alternative for drone e.g. UDP h264 stream
    //videoManager->setCustomPipeline("udpsrc port=5000 caps=\"application/x-rtp,media=video,encoding-name=H264,payload=96\" ! rtpjitterbuffer latency=200 ! rtph264depay ! h264parse ! avdec_h264 ! videoconvert ! video/x-raw,format=RGB ! appsink name=mysink emit-signals=true drop=true max-buffers=1");
    /*
    videoManager->setCustomPipeline(
        "udpsrc port=5000 caps=\"application/x-rtp,media=video,encoding-name=H264,payload=96\" ! "
        "rtpjitterbuffer latency=200 ! rtph264depay ! h264parse ! avdec_h264 ! "
        "videoconvert ! videocrop name=cropper ! videoscale ! "
        "video/x-raw,format=RGB ! appsink name=mysink emit-signals=true drop=true max-buffers=1"
        ); // videocrop for zoom
    */
    videoManager->setCustomPipeline(
        "udpsrc port=5000 caps=\"application/x-rtp,media=video,clock-rate=90000,encoding-name=H264,payload=96\" ! "
        "rtpjitterbuffer latency=50 ! rtph264depay ! h264parse ! avdec_h264 ! "
        "videoconvert ! videocrop name=cropper ! videoscale ! "
        "video/x-raw,format=RGB ! appsink name=mysink emit-signals=true drop=true max-buffers=1 sync=false"
        ); // this one worked with khadas

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
//----------------------------------------------------


//------- settingsScreen controls  -----------------
void MainWindow::backPushButton()
{
    // goes back to waiting screen
    // also saves user settings
    ui->stackedWidget->setCurrentIndex(0);

    QString codec = ui->codecComboBox->currentText();
    QString transmissionProtocol = ui->protocolComboBox->currentText();
    QString bitrateMode = ui->bitrateComboBox->currentText();



    if (codec.startsWith("Select") || transmissionProtocol.startsWith("Select") || bitrateMode.startsWith("Select")) {
        // invalid settings
        return;
    }
    // 2. Φτιάχνουμε το νέο pipeline
    // videoManager->menuPipelineBuild(codec, transmissionProtocol, bitrateMode);

    // 3. Γυρίζουμε στην οθόνη του βίντεο (Stream Screen)
    ui->stackedWidget->setCurrentWidget(ui->streamScreen);
}

//----------------------------------------------------
