/********************************************************************************
** Form generated from reading UI file 'urldialog.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_URLDIALOG_H
#define UI_URLDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>

QT_BEGIN_NAMESPACE

class Ui_UrlDialog
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *UrlDialog)
    {
        if (UrlDialog->objectName().isEmpty())
            UrlDialog->setObjectName("UrlDialog");
        UrlDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(UrlDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        retranslateUi(UrlDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, UrlDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, UrlDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(UrlDialog);
    } // setupUi

    void retranslateUi(QDialog *UrlDialog)
    {
        UrlDialog->setWindowTitle(QCoreApplication::translate("UrlDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UrlDialog: public Ui_UrlDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_URLDIALOG_H
