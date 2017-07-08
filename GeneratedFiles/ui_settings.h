/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_Settings
{
public:
    QDialogButtonBox *buttonBox;
    QSlider *horizontalSlider;
    QLabel *label;
    QPushButton *show_full;
    QPushButton *show_window;
    QPushButton *show_maximise;
    QLabel *label_2;
    QLineEdit *nickname;

    void setupUi(QDialog *Settings)
    {
        if (Settings->objectName().isEmpty())
            Settings->setObjectName(QStringLiteral("Settings"));
        Settings->resize(258, 101);
        Settings->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        buttonBox = new QDialogButtonBox(Settings);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(90, 70, 161, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);
        horizontalSlider = new QSlider(Settings);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(80, 30, 171, 16));
        horizontalSlider->setOrientation(Qt::Horizontal);
        label = new QLabel(Settings);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 71, 16));
        show_full = new QPushButton(Settings);
        show_full->setObjectName(QStringLiteral("show_full"));
        show_full->setGeometry(QRect(10, 10, 80, 21));
        show_window = new QPushButton(Settings);
        show_window->setObjectName(QStringLiteral("show_window"));
        show_window->setGeometry(QRect(90, 10, 80, 21));
        show_maximise = new QPushButton(Settings);
        show_maximise->setObjectName(QStringLiteral("show_maximise"));
        show_maximise->setGeometry(QRect(170, 10, 80, 21));
        label_2 = new QLabel(Settings);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 50, 111, 16));
        nickname = new QLineEdit(Settings);
        nickname->setObjectName(QStringLiteral("nickname"));
        nickname->setGeometry(QRect(120, 50, 131, 21));

        retranslateUi(Settings);
        QObject::connect(buttonBox, SIGNAL(accepted()), Settings, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Settings, SLOT(reject()));

        QMetaObject::connectSlotsByName(Settings);
    } // setupUi

    void retranslateUi(QDialog *Settings)
    {
        Settings->setWindowTitle(QApplication::translate("Settings", "Settings", 0));
        label->setText(QApplication::translate("Settings", "Sound volume", 0));
        show_full->setText(QApplication::translate("Settings", "Fullscreen", 0));
        show_window->setText(QApplication::translate("Settings", "Window", 0));
        show_maximise->setText(QApplication::translate("Settings", "Maximise", 0));
        label_2->setText(QApplication::translate("Settings", "Nickname (multiplayer)", 0));
    } // retranslateUi

};

namespace Ui {
    class Settings: public Ui_Settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
