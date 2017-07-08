/********************************************************************************
** Form generated from reading UI file 'connect_enter_ip.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECT_ENTER_IP_H
#define UI_CONNECT_ENTER_IP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Connect
{
public:
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QDialog *Connect)
    {
        if (Connect->objectName().isEmpty())
            Connect->setObjectName(QStringLiteral("Connect"));
        Connect->setWindowModality(Qt::ApplicationModal);
        Connect->resize(270, 25);
        lineEdit = new QLineEdit(Connect);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(110, 0, 91, 20));
        label = new QLabel(Connect);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 101, 20));
        pushButton = new QPushButton(Connect);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(200, 0, 61, 23));

        retranslateUi(Connect);

        QMetaObject::connectSlotsByName(Connect);
    } // setupUi

    void retranslateUi(QDialog *Connect)
    {
        Connect->setWindowTitle(QApplication::translate("Connect", "Connect by ip", Q_NULLPTR));
        lineEdit->setInputMask(QApplication::translate("Connect", "000.000.000.000;_", Q_NULLPTR));
        label->setText(QApplication::translate("Connect", "Enter IP to connect:", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Connect", "Connect", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Connect: public Ui_Connect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECT_ENTER_IP_H
