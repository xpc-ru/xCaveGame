#include "dlg_connect_enter_ip.h"
dlgConnectEnterIP::dlgConnectEnterIP(QDialog *pWidget /* = nullptr*/)
	: QDialog(pWidget)
{
	setupUi(this);
	QObject::connect(pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
}

void dlgConnectEnterIP::on_pushButton_clicked()
{
	ip = lineEdit->text();
	(this)->close();
}