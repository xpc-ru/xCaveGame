#ifndef DLG_SETTINGS_H
#define DLG_SETTINGS_H
#include "wnd.h"
#include "ui_settings.h"
class dlgSettings : public QDialog, public Ui::Settings
{
	Q_OBJECT
	CWnd *SET;
private slots:
	void fullscr();
	void window();
	void maximise();
	void setVol(int new_vol);
	void setname(const QString &name);
public:
	dlgSettings(CWnd *set);
};

#endif // DLG_SETTINGS_H
