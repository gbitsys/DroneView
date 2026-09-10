/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "aspectratiolabel.h"
#include "gstvideowidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave;
    QAction *actionLoad;
    QAction *actionQuit;
    QAction *actionSet_Url;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_4;
    QStackedWidget *stackedWidget;
    QWidget *waitScreen;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_4;
    AspectRatioLabel *imageLabel;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *playButton;
    QPushButton *settingsButton;
    QSpacerItem *horizontalSpacer_4;
    QWidget *streamScreen;
    QVBoxLayout *verticalLayout_5;
    GstVideoWidget *gstVideoWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *stopButton;
    QPushButton *recordButton;
    QPushButton *screenshotButton;
    QPushButton *resolutionButton;
    QVBoxLayout *verticalLayout_2;
    QSlider *zoomSlider_2;
    QLabel *zoomLabel_2;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QRadioButton *stream1Button;
    QRadioButton *stream2Button;
    QRadioButton *stream3Button;
    QSpacerItem *horizontalSpacer_6;
    QWidget *settingsScreen;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *backButton;
    QPushButton *pushButton;
    QVBoxLayout *verticalLayout;
    QComboBox *codecComboBox;
    QComboBox *protocolComboBox;
    QComboBox *bitrateComboBox;
    QSpacerItem *verticalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(743, 617);
        MainWindow->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName("actionLoad");
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName("actionQuit");
        actionSet_Url = new QAction(MainWindow);
        actionSet_Url->setObjectName("actionSet_Url");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        horizontalLayout_4 = new QHBoxLayout(centralwidget);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        stackedWidget->setAutoFillBackground(false);
        waitScreen = new QWidget();
        waitScreen->setObjectName("waitScreen");
        verticalLayout_8 = new QVBoxLayout(waitScreen);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        imageLabel = new AspectRatioLabel(waitScreen);
        imageLabel->setObjectName("imageLabel");
        sizePolicy.setHeightForWidth(imageLabel->sizePolicy().hasHeightForWidth());
        imageLabel->setSizePolicy(sizePolicy);
        imageLabel->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        imageLabel->setScaledContents(false);
        imageLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(imageLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        playButton = new QPushButton(waitScreen);
        playButton->setObjectName("playButton");
        playButton->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStart));
        playButton->setIcon(icon);

        horizontalLayout->addWidget(playButton);

        settingsButton = new QPushButton(waitScreen);
        settingsButton->setObjectName("settingsButton");
        settingsButton->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::DocumentProperties));
        settingsButton->setIcon(icon1);

        horizontalLayout->addWidget(settingsButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout_4->addLayout(horizontalLayout);


        verticalLayout_8->addLayout(verticalLayout_4);

        stackedWidget->addWidget(waitScreen);
        streamScreen = new QWidget();
        streamScreen->setObjectName("streamScreen");
        streamScreen->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        verticalLayout_5 = new QVBoxLayout(streamScreen);
        verticalLayout_5->setObjectName("verticalLayout_5");
        gstVideoWidget = new GstVideoWidget(streamScreen);
        gstVideoWidget->setObjectName("gstVideoWidget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(gstVideoWidget->sizePolicy().hasHeightForWidth());
        gstVideoWidget->setSizePolicy(sizePolicy1);

        verticalLayout_5->addWidget(gstVideoWidget);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        stopButton = new QPushButton(streamScreen);
        stopButton->setObjectName("stopButton");
        stopButton->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStop));
        stopButton->setIcon(icon2);

        horizontalLayout_5->addWidget(stopButton);

        recordButton = new QPushButton(streamScreen);
        recordButton->setObjectName("recordButton");
        recordButton->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::MediaRecord));
        recordButton->setIcon(icon3);

        horizontalLayout_5->addWidget(recordButton);

        screenshotButton = new QPushButton(streamScreen);
        screenshotButton->setObjectName("screenshotButton");
        screenshotButton->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        QIcon icon4(QIcon::fromTheme(QIcon::ThemeIcon::Phone));
        screenshotButton->setIcon(icon4);

        horizontalLayout_5->addWidget(screenshotButton);

        resolutionButton = new QPushButton(streamScreen);
        resolutionButton->setObjectName("resolutionButton");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(resolutionButton->sizePolicy().hasHeightForWidth());
        resolutionButton->setSizePolicy(sizePolicy2);
        resolutionButton->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        QIcon icon5(QIcon::fromTheme(QIcon::ThemeIcon::VideoDisplay));
        resolutionButton->setIcon(icon5);

        horizontalLayout_5->addWidget(resolutionButton);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        zoomSlider_2 = new QSlider(streamScreen);
        zoomSlider_2->setObjectName("zoomSlider_2");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(zoomSlider_2->sizePolicy().hasHeightForWidth());
        zoomSlider_2->setSizePolicy(sizePolicy3);
        zoomSlider_2->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        zoomSlider_2->setOrientation(Qt::Orientation::Horizontal);

        verticalLayout_2->addWidget(zoomSlider_2);

        zoomLabel_2 = new QLabel(streamScreen);
        zoomLabel_2->setObjectName("zoomLabel_2");
        zoomLabel_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(zoomLabel_2);


        horizontalLayout_5->addLayout(verticalLayout_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_5);


        verticalLayout_5->addLayout(verticalLayout_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        stream1Button = new QRadioButton(streamScreen);
        stream1Button->setObjectName("stream1Button");
        stream1Button->setChecked(true);

        horizontalLayout_3->addWidget(stream1Button);

        stream2Button = new QRadioButton(streamScreen);
        stream2Button->setObjectName("stream2Button");

        horizontalLayout_3->addWidget(stream2Button);

        stream3Button = new QRadioButton(streamScreen);
        stream3Button->setObjectName("stream3Button");

        horizontalLayout_3->addWidget(stream3Button);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        verticalLayout_5->addLayout(horizontalLayout_3);

        stackedWidget->addWidget(streamScreen);
        settingsScreen = new QWidget();
        settingsScreen->setObjectName("settingsScreen");
        verticalLayout_6 = new QVBoxLayout(settingsScreen);
        verticalLayout_6->setObjectName("verticalLayout_6");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_7);

        backButton = new QPushButton(settingsScreen);
        backButton->setObjectName("backButton");
        QIcon icon6(QIcon::fromTheme(QIcon::ThemeIcon::GoPrevious));
        backButton->setIcon(icon6);

        horizontalLayout_2->addWidget(backButton);

        pushButton = new QPushButton(settingsScreen);
        pushButton->setObjectName("pushButton");
        QIcon icon7(QIcon::fromTheme(QIcon::ThemeIcon::HelpAbout));
        pushButton->setIcon(icon7);

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout_6->addLayout(horizontalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        codecComboBox = new QComboBox(settingsScreen);
        codecComboBox->addItem(QString());
        codecComboBox->addItem(QString());
        codecComboBox->addItem(QString());
        codecComboBox->addItem(QString());
        codecComboBox->setObjectName("codecComboBox");
        codecComboBox->setEnabled(true);
        sizePolicy2.setHeightForWidth(codecComboBox->sizePolicy().hasHeightForWidth());
        codecComboBox->setSizePolicy(sizePolicy2);
        codecComboBox->setMaximumSize(QSize(150, 16777215));
        codecComboBox->setInsertPolicy(QComboBox::InsertPolicy::NoInsert);

        verticalLayout->addWidget(codecComboBox);

        protocolComboBox = new QComboBox(settingsScreen);
        protocolComboBox->addItem(QString());
        protocolComboBox->setObjectName("protocolComboBox");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(protocolComboBox->sizePolicy().hasHeightForWidth());
        protocolComboBox->setSizePolicy(sizePolicy4);
        protocolComboBox->setMaximumSize(QSize(150, 16777215));

        verticalLayout->addWidget(protocolComboBox);

        bitrateComboBox = new QComboBox(settingsScreen);
        bitrateComboBox->addItem(QString());
        bitrateComboBox->addItem(QString());
        bitrateComboBox->addItem(QString());
        bitrateComboBox->addItem(QString());
        bitrateComboBox->setObjectName("bitrateComboBox");
        sizePolicy4.setHeightForWidth(bitrateComboBox->sizePolicy().hasHeightForWidth());
        bitrateComboBox->setSizePolicy(sizePolicy4);
        bitrateComboBox->setMaximumSize(QSize(150, 16777215));

        verticalLayout->addWidget(bitrateComboBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        verticalLayout_6->addLayout(verticalLayout);

        stackedWidget->addWidget(settingsScreen);

        horizontalLayout_4->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 743, 23));
        menubar->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "DroneView", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "&Save", nullptr));
        actionLoad->setText(QCoreApplication::translate("MainWindow", "Load", nullptr));
        actionQuit->setText(QCoreApplication::translate("MainWindow", "&Quit", nullptr));
        actionSet_Url->setText(QCoreApplication::translate("MainWindow", "Set &Url", nullptr));
        imageLabel->setText(QString());
        playButton->setText(QCoreApplication::translate("MainWindow", "Play ", nullptr));
        settingsButton->setText(QCoreApplication::translate("MainWindow", "Settings ", nullptr));
        stopButton->setText(QCoreApplication::translate("MainWindow", "Stop ", nullptr));
        recordButton->setText(QCoreApplication::translate("MainWindow", "Record ", nullptr));
        screenshotButton->setText(QCoreApplication::translate("MainWindow", "Prt Sc", nullptr));
        resolutionButton->setText(QCoreApplication::translate("MainWindow", "Resolution ", nullptr));
        zoomLabel_2->setText(QCoreApplication::translate("MainWindow", "Zoom", nullptr));
        stream1Button->setText(QCoreApplication::translate("MainWindow", "Stream 1", nullptr));
        stream2Button->setText(QCoreApplication::translate("MainWindow", "Stream 2", nullptr));
        stream3Button->setText(QCoreApplication::translate("MainWindow", "Stream 3", nullptr));
        backButton->setText(QString());
        pushButton->setText(QString());
        codecComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Select Codec ...", nullptr));
        codecComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "H264 (software)", nullptr));
        codecComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "H264 (hardware)", nullptr));
        codecComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "H265", nullptr));

        protocolComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Select Protocol ...", nullptr));

        bitrateComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Select Bitrate ...", nullptr));
        bitrateComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Constant (CBR)", nullptr));
        bitrateComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Variable   (VBR)", nullptr));
        bitrateComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Constraint VBR", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
