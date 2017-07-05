#include "dlg_settings.h"

dlgSettings::dlgSettings(CWnd *set)
	: QDialog(set)
{
	SET = set;
	setupUi(this);
	horizontalSlider->setValue(SET->vol);
	nickname->setText(SET->name);
	QObject::connect(show_full, SIGNAL(clicked(bool)), this, SLOT(fullscr()));
	QObject::connect(show_window, SIGNAL(clicked(bool)), this, SLOT(window()));
	QObject::connect(show_maximise, SIGNAL(clicked(bool)), this, SLOT(maximise()));
	QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setVol(int)));
	QObject::connect(nickname, SIGNAL(textChanged(const QString &)), this, SLOT(setname(const QString &)));
}

void dlgSettings::fullscr()
{
	SET->showFullScreen();
}
void dlgSettings::window()
{
	SET->showNormal();
}
void dlgSettings::maximise()
{
	SET->showMaximized();
}
void dlgSettings::setVol(int new_vol)
{
	SET->vol = new_vol;
}
void dlgSettings::setname(const QString &name)
{
	SET->name = name;
}
