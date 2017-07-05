#pragma once
#include "ui_connect_enter_ip.h"
#include "wnd.h"

class dlgConnectEnterIP : public QDialog, public Ui::Connect
{
	Q_OBJECT

public:
	dlgConnectEnterIP(QDialog *pWidget = nullptr);
	QString ip;
public slots:
	void on_pushButton_clicked();
};