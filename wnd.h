#ifndef WND_H
#define WND_H

#include <QMainWindow>
#include <QString>
#include <QImage>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QPoint>
#include <QPointF>
#include <QSound>
#include <QCoreApplication>
#include <string>
#include "gSocket.h"

const unsigned short data_max = 768;
const QImage qimageNull("\0");

enum EState
{
	MainMenu = 0,
	Inventory = 1,
	World = 2,
	Singleplayer = 3,
	Multiplayer = 4,
	MPWorld = 5,
	Settings = 6
};
struct SData
{
	unsigned short ID;
	QString file;
	QImage img;
	SData()
	{
		ID = 0;
		file = "";
		img = qimageNull;
	}
};

std::string Q2Cstr(const QString& qStr);
QString C2Qstr(const std::string& str);

class CWnd : public QMainWindow
{
	Q_OBJECT

private:
	enum EDirection { UP, DOWN, LEFT, RIGHT };

	SData data[data_max] = {};
	QPointF curPos{ 0, 0 };
	QPoint player{ 0, 0 }, other_player{ 0, 0 };
	unsigned short game[60][80] = {};
	unsigned short inv[40] = {};
	unsigned short health = 100, armor = 0, air = 100, active_id = 0;
	unsigned short dim = 1; //it will work in new versions (Singleplayer > World #dim), used to switch
	bool unableDIM[10] = {};//between biomes but, some biomes aren't accessible while you don't open them
	QString path;
	QMediaPlayer *main_sound;
	QMediaPlaylist *playlist;
	EState state = MainMenu;
	qreal painterX = 1, painterY = 1, transform = 1;
	unsigned int resX = 640, resY = 480;
	GSocket loc, cli;
public:
	unsigned short vol = 100;
	QString name = "player";

public:
	CWnd(QWidget *parent = 0);
	~CWnd();
	void operator=(CWnd &w);
protected:
	virtual void paintEvent(QPaintEvent *pPaintEvent);
	virtual void mouseMoveEvent(QMouseEvent *pMouseEvent);
	virtual void mousePressEvent(QMouseEvent *pMouseEvent);
	virtual void keyPressEvent(QKeyEvent *pKeyEvent);
	virtual void closeEvent(QCloseEvent *pCloseEvent);
	virtual void resizeEvent(QResizeEvent *pResizeEvent);
private:
	void game_print(QPainter *pPainter);
	void save();
	void load();
	bool tryGo(EDirection d, bool bClient = false);
	void savedata();
	void loaddata();
};

#endif // WND_H
