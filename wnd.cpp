#include "wnd.h"
#include "dlg_connect_enter_ip.h"
#include "dlg_settings.h"
#include "tcp_protocol.h"
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPen>
#include <QKeyEvent>
#include <QMessageBox>
#include <QCloseEvent>
#include <QAbstractButton>
#include <QRectF>
#include <QIcon>
#include <QFont>
#include <QSplashScreen>
#include <QPixmap>
#include <QSize>
#include <QResizeEvent>
#include <QThread>
#include <QDir>
#include <QUrl>
#include <vector>
#include <stdio.h>
using namespace std;

const unsigned short INV_ELEMS   = 40;
const unsigned short GAME_ROWS   = 60;
const unsigned short GAME_COLS   = 80;
const unsigned short SPAWN_ROW   = 14;
const unsigned short SPAWN_COL   =  0;

//=============================================================================
string Q2Cstr(const QString& str)
{
	QByteArray ba = str.toLocal8Bit();
	string NEWstr = ba.data();
	return NEWstr;
}
QString C2Qstr(const string& str)
{
	QString qStr = QString::fromLocal8Bit(str.c_str());
	return qStr;
}
//=============================================================================

CWnd::CWnd(QWidget *parent)
	: QMainWindow(parent)
	, path(QCoreApplication::applicationDirPath())
	, main_sound(0)
	, playlist(0)
{
	QString str = path;
	str += "/data/id/splash.png";
	QPixmap pixmap(str);
	QSplashScreen scr(pixmap);
	scr.showMessage("Music and main icon loading...",
		Qt::AlignLeft | Qt::AlignBottom, Qt::white);
	scr.show();

	setMouseTracking(true);
	QIcon main_icon(path + "/data/id/3.png");
	setWindowIcon(main_icon);
	main_sound = new QMediaPlayer();
	playlist = new QMediaPlaylist();
	main_sound->setVolume(100);
	playlist->addMedia(QUrl::fromLocalFile(path + "/data/media/sound1.wav"));
	playlist->setPlaybackMode(QMediaPlaylist::Loop);
	main_sound->setPlaylist(playlist);
	main_sound->play();
	scr.showMessage("Initialising blocks...",
		Qt::AlignLeft | Qt::AlignBottom, Qt::white);

	for(int i = 0; i < data_max; ++i)
	{
		data[i].ID = i;
		data[i].file = path + "/data/id/" + QString::number(i) + ".png";
		QImage img(data[i].file);
		data[i].img = img;
	}
	scr.showMessage("Initialising window size...",
		Qt::AlignLeft | Qt::AlignBottom, Qt::white);

	setMinimumWidth(640);
	setMinimumHeight(480);
	active_id = 0;
	scr.showMessage("Initialising game space...",
		Qt::AlignLeft | Qt::AlignBottom, Qt::white);

	for(int i = 0; i < GAME_ROWS; ++i)
	{
		for(int j = 0; j < GAME_COLS; ++j)
		{
			if(i == 59)
				game[i][j] = 5;   //bedrock
			else if(i < 15)
				game[i][j] = 0;   //air
			else if(i == 15)
				game[i][j] = 3;   //grass
			else if(i == 16)
				game[i][j] = 4;   //dirt
			else
				game[i][j] = 1;   //stone
		}
	}
	game[SPAWN_ROW-1][SPAWN_COL] = 6; //player
	game[SPAWN_ROW][SPAWN_COL] = 7; //body

	game[14][1] = 5;
	game[13][2] = 5;
	game[12][3] = 5;
	game[11][4] = 5;
	game[10][5] = 5;
	game[9][6]  = 5;
	game[8][7]  = 5;
	game[7][8]  = 5;
	game[6][9]  = 5;
	game[5][10] = 5;
	game[4][11] = 5;
	game[3][12] = 5;
	game[2][13] = 5;

	player.setX(SPAWN_COL);
	player.setY(SPAWN_ROW);
	other_player.setX(SPAWN_COL);
	other_player.setY(SPAWN_ROW-1);
	scr.showMessage("Initialising null singleplayer inventory...",
		Qt::AlignLeft | Qt::AlignBottom, Qt::white);

	for(int i = 0; i < INV_ELEMS; ++i)
		inv[i] = 0;
	scr.showMessage("All components loaded successfully. Showing window...",
		Qt::AlignLeft | Qt::AlignBottom, Qt::white);

	show();
	scr.finish(this);
	loaddata();
}
CWnd::~CWnd()
{
	delete main_sound;
	main_sound = 0;
}
void CWnd::operator =(CWnd &w)
{
	w.player = player;
	w.other_player = player;
	w.main_sound = main_sound;
	w.vol = vol;
	w.state = state;
}

void CWnd::paintEvent(QPaintEvent * /*pPaintEvent*/)
{
	painterX = ((qreal)resX)/640.0;
	painterY = ((qreal)resY)/480.0;
	transform = (painterX > painterY ? painterY : painterX);
	QPainter p(this);
	QFont oldFont = p.font();
	QFont font(oldFont);
	QPen oldPen = p.pen();
	QPen pen(Qt::white);
	pen.setWidth(1);
	font.setPixelSize(8);
	p.setPen(pen);
	p.setFont(font);
	p.scale(transform, transform);
	game_print(&p);
	p.setPen(oldPen);
	p.setFont(oldFont);
}
void CWnd::mouseMoveEvent(QMouseEvent *pMouseEvent)
{
	curPos = (QPointF)pMouseEvent->pos();
	curPos.setX(curPos.x() / transform);
	curPos.setY(curPos.y() / transform);
	repaint();
}
void CWnd::mousePressEvent(QMouseEvent *pMouseEvent)
{
	curPos = (QPointF)pMouseEvent->pos();
	curPos.setX(curPos.x() / transform);
	curPos.setY(curPos.y() / transform);
	repaint();
	Qt::MouseButton mouse_btn = pMouseEvent->button();

	if (mouse_btn == Qt::LeftButton)
	{
		if (state == Inventory)
		{
			QRectF closeMenu(2, 454, 16, 16);
			QRectF qtt(48, 454, 16, 16);
			QRectF save(104, 454, 16, 16);
			QRectF load(152, 454, 16, 16);
			QRectF aboutGame(569, 454, 16, 16);
			QRectF aboutQt(622, 454, 16, 16);
			if (closeMenu.contains(curPos))
				state = World;
			else if (save.contains(curPos))
				CWnd::save();
			else if (load.contains(curPos))
				CWnd::load();
			else if (qtt.contains(curPos))
				state = MainMenu;
			else if (aboutGame.contains(curPos))
				QMessageBox::about(0, "xCaveGame", "xCaveGame beta ver. 1.0\n(C) 2017, xPC");
			else if (aboutQt.contains(curPos))
				QMessageBox::aboutQt(0, "xCaveGame");
		}
		else if (state == MainMenu)
		{
			QRectF sp(18, 106, 30, 30);
			QRectF mp(18, 160, 30, 30);
			QRectF settings(18, 218, 30, 30);
			QRectF exit(18, 276, 30, 30);
			if (sp.contains(curPos))
				state = Inventory; //state = SinglePlayer;
			else if (mp.contains(curPos))
				state = Multiplayer;
			else if (settings.contains(curPos))
			{
				dlgSettings set(this);
				bool fullscr = isFullScreen();
				int old_vol = vol;
				QString old_name = name;
				if (set.exec() == QDialog::Rejected)
				{
					vol = old_vol;
					name = old_name;
					if (fullscr)
						showFullScreen();
					else
						showNormal();
				}
				main_sound->setVolume(vol);
				savedata();
			}
			else if (exit.contains(curPos))
				close();
		}
		else if (state == Multiplayer)
		{
			QRectF create(62, 83, 160, 160);
			QRectF connect(226, 83, 160, 160);
			QRectF btt(390, 83, 160, 160);
			if (create.contains(curPos))
			{
				int iRes = QMessageBox::critical(0,
					"xCaveGame",
					"WARNING! You won't start playing server while somebody don't connect to your server. Are you sure to continue?",
					QMessageBox::Yes, QMessageBox::No);
				if (QMessageBox::No == iRes)
				{
					state = Multiplayer;
					goto mouseMoveEvent_end;
				}
				loc.CreateServer(XCG_PORT);
				loc.AcceptClientConnection(&cli);
				unsigned char CLI_VER = 0;
				iRes = loc.ReadByte(CLI_VER);
				if (-1 == iRes)
				{
					QMessageBox::critical(0, "xCaveGame", "Invalid client", QMessageBox::Ok);
					loc.Close();
				}
				iRes = loc.WriteByte(TCP_PROTOCOL_VER);
				if (-1 == iRes)
				{
					QMessageBox::critical(0, "xCaveGame", "Invalid client", QMessageBox::Ok);
					loc.Close();
				}
				//state = MPWorld;
				state = MainMenu;
			}
			else if (connect.contains(curPos))
			{
				dlgConnectEnterIP dlgCEI(nullptr);
				if (dlgCEI.exec() == QDialog::Accepted)
				{
					QString ip = dlgCEI.ip;
					QMessageBox::about(0, "xCG b1.0", "UC! You are connecting to: " + ip);
					const char *addr = Q2Cstr(ip).c_str();
					loc.CreateClient();
					int iRes = loc.ConnectToServer(XCG_PORT, addr, 10);
					if (-3 == iRes)
					{
						QMessageBox::critical(0, "xCaveGame", "Timeout (10 secs) expired!", QMessageBox::Ok);
						loc.Close();
					}
					iRes = loc.WriteByte(TCP_PROTOCOL_VER);
					if (-1 == iRes)
					{
						QMessageBox::critical(0, "xCaveGame", "Invalid server", QMessageBox::Ok);
						loc.Close();
					}
					unsigned char SERV_VER = 0;
					iRes = loc.ReadByte(SERV_VER);
					if (-1 == iRes)
					{
						QMessageBox::critical(0, "xCaveGame", "Invalid server", QMessageBox::Ok);
						loc.Close();
					}
					if (TCP_PROTOCOL_VER != SERV_VER)
					{
						QMessageBox::critical(0,
							"xCaveGame",
							"Invalid version, please use " +
							QString::number(SERV_VER) +
							", or contact server administrator to change destination version",
							QMessageBox::Ok);
						loc.Close();
					}
					if (loc.isClosed())
					{
						state = Multiplayer;
						load();
					}
					else
					{
						//state = MPWorld;
						//game[other_player.y()][other_player.x()] = 7; //6 - host; 8 - client
						//game[other_player.y()-1][other_player.x()] = 8; //7 - body
						state = MainMenu;
					}
				}
			}
			else if (btt.contains(curPos))
				state = MainMenu;
		}
	}

mouseMoveEvent_end:
	repaint();
}
void CWnd::keyPressEvent(QKeyEvent *pKeyEvent)
{
	repaint();

	int cmd = pKeyEvent->key();
	if (cmd == Qt::Key_Pause)
		close(); //closin window if key = [PAUSE|BREAK]
	else if (cmd == Qt::Key_Escape)
	{
		if (state == World)
			state = Inventory;
		else if (state == Inventory)
			state = World;
	}
	else if (state == World)
	{
		if (cmd == Qt::Key_Up)
			tryGo(UP);
		else if (cmd == Qt::Key_Down)
			tryGo(DOWN);
		else if (cmd == Qt::Key_Left)
			tryGo(LEFT);
		else if (cmd == Qt::Key_Right)
			tryGo(RIGHT);
		repaint();

		double unlive = 0;
		for (int i = 0; true; ++i)
		{
			if (i > 3)
				unlive = i / 2;
			if (tryGo(DOWN) != true)
				break;
		}
		health -= unlive;

		if ((player.y() == GAME_ROWS - 1) ||
			(health < 1))
		{
			game[player.y()][player.x()] = 0;
			game[player.y()-1][player.x()] = 0;
			QMessageBox died(QMessageBox::Information,
				"xCaveGame World",
				"YOU DIED!");
			died.addButton("Respawn", QMessageBox::YesRole);
			died.addButton("Load saved game", QMessageBox::NoRole);
			int dexec = died.exec();
			if (dexec == 0)
			{
				player.setX(SPAWN_COL);
				player.setY(SPAWN_ROW);
				game[player.y()][player.x()] = 7;
				game[player.y()-1][player.x()] = 6;
				health = 100;
			}
			else
				load();
		}
	}

	repaint();
}
void CWnd::closeEvent(QCloseEvent *pCloseEvent)
{
	repaint();

	QMessageBox qmbExit(QMessageBox::Question,
											"xCaveGame b1.0",
											"Do you really want to exit xCG b1.0?",
											QMessageBox::No | QMessageBox::Yes);
	qmbExit.setDefaultButton(QMessageBox::No);
	int iRes = qmbExit.exec();
	switch(iRes)
	{
		case QMessageBox::Yes:
			pCloseEvent->accept();
			break;
		default:
			pCloseEvent->ignore();
	}
}
void CWnd::resizeEvent(QResizeEvent *pResizeEvent)
{
	QSize newSize = pResizeEvent->size();
	resX = newSize.width();
	resY = newSize.height();
	repaint();
}

void CWnd::game_print(QPainter *pPainter)
{
	if(state == World)
	{
		QString bgpath = path;
		bgpath += "/data/id/main_bg.png";
		QImage main_bg(bgpath);
		pPainter->drawImage(0, 0, main_bg);
		for(int i = 0; i < GAME_ROWS; ++i)
		{
			for(int j = 0; j < GAME_COLS; ++j)
			{
				if(game[i][j] != 0)
				{
					unsigned short x = 8*j;
					unsigned short y = 8*i;
					QImage img = data[game[i][j]].img;
					pPainter->drawImage(x, y, img);
				}
			}
		}
	}
	else if(state == Inventory)
	{
		QString invpath = path;
		invpath += "/data/id/inv.png";
		QImage inv(invpath);
		pPainter->drawImage(0, 0, inv);
	}
	else if(state == MainMenu)
	{
		QString menupath = path;
		menupath += "/data/id/main.png";
		QImage menu(menupath);
		pPainter->drawImage(0, 0, menu);
	}
	else if(state == Multiplayer)
	{
		QString mpmenupath = path;
		mpmenupath += "/data/id/mp_main.png";
		QImage mpmenu(mpmenupath);
		pPainter->drawImage(0, 0, mpmenu);
	}
	pPainter->drawText(
		QRect(QPoint(0, 472), QPoint(640, 480)),
		Qt::AlignLeft | Qt::AlignBottom,
		"xCaveGame b1.0 - X:" +
		QString::number(curPos.x()) +
		"; Y:" +
		QString::number(curPos.y()) +
		"; Active item (in inventory):" +
		QString::number(active_id) +
		"; " +
		QString::number(health) +
		"-" +
		QString::number(armor) +
		"-" +
		QString::number(air) +
		"; " +
		QString::number(resX) +
		"x" +
		QString::number(resY)
	);
}
void CWnd::save()
{
	string new_path = Q2Cstr(path);
	new_path += "/data/world/";
	new_path += Q2Cstr(QString::number(dim));
	new_path += ".xcg";
	FILE *file = fopen(new_path.c_str(), "w+t");
	if(file != 0)
	{
		fprintf(file, "xcg-version:1.0\n");
		for(int i = 0; i < GAME_ROWS; ++i)
		{
			for(int j = 0; j < GAME_COLS; ++j)
				fprintf(file, "%hu ", game[i][j]);
			fprintf(file, "\n");
		}
		fclose(file);
		new_path = Q2Cstr(path) + string("/data/world/player.xcg");
		file = fopen(new_path.c_str(), "w+t");
		for (int i = 0; i < INV_ELEMS; ++i)
			fprintf(file, "%hu ", inv[i]);
		fprintf(file, "\n");
		fprintf(file, "%hu %hu %hu %hu",
			health, armor, air, active_id);
		fclose(file);
		QMessageBox::information(0, "xCaveGame 1.0",
			"Saving world success!");
	}
	else
		QMessageBox::critical(0, "xCaveGame 1.0 ERROR",
			"File is corrupted, secured, opened in another application or disk is full");
}
void CWnd::load()
{
	string new_path = Q2Cstr(path);
	const int tlen = 18;
	char temp[tlen] = { "\0" };
	new_path += "/data/world/";
	new_path += Q2Cstr(QString::number(dim));
	new_path += ".xcg";
	FILE *file = fopen(new_path.c_str(), "r+t");
	if(file != 0)
	{
		//fprintf(file, "xcg-version:1.0\n");
		fgets(temp, tlen, file);
		for(int i = 0; i < GAME_ROWS; ++i)
		{
			for(int j = 0; j < GAME_COLS; ++j)
				fscanf(file, "%hu ", &game[i][j]);
			fscanf(file, "\n");
		}
		fclose(file);
		new_path = Q2Cstr(path) + string("/data/world/player.xcg");
		file = fopen(new_path.c_str(), "r+t");
		for(int i = 0; i < INV_ELEMS; ++i)
			fscanf(file, "%hu ", &inv[i]);
		fscanf(file, "\n");
		fscanf(file, "%hu %hu %hu %hu",
						&health, &armor, &air, &active_id);
		fclose(file);
		QString loadsuccess = "Loading world success! ";
		loadsuccess += temp;
		QMessageBox::information(0, "xCaveGame",
			loadsuccess);
	}
	else
		QMessageBox::critical(0, "xCaveGame ERROR",
			"File is corrupted, secured, opened in another application or disk is full");
}
bool CWnd::tryGo(EDirection d, bool bClient /* = false*/) //ONLY FOR PLAYERS!!!
{
	//Bug XCG-0001: you see bedrock stairs. you climb them once.
	//              but when you try again - you can't get up.
	//              magic!
	//Report #0001 from  7/06/2017
	//Fix    #0001 from  7/08/2017
	//Commit 98788b73 add
	//Commit 517b900a fix: I fixed this adding XCG-0002

	//Bug XCG-0002: Added 2 bl. up and 1 bl. wide player - it seems like minecraft
	//              But when going "outside" by map:
	//                          Array[5][5]:
	//                Array[5][5]:[][][][][]
	//                  [][][][][][][][][][]
	//                  [][][][][][][][][][]
	//                  [][][][][][][][][][]
	//                ->[][][][][][][][][][]-> //blocks from [4][0] to [5][5]
	//                  [][][][][]
	//              frome one side to another we see our head flying - xcg-0003. It's
	//              not a bug, xcg-0000 (go outside the map), it's a feature with this
	//              bug...
	//Report #0002 from  7/08/2017
	//Fix    #0002 from  7/08/2017
	//Commit 517b900a add
	//Commit d5fe5b07 fix I fixed this adding XCG-0003

	//Bug XCG-0003: Head duplicates and flies when you go "left outside"
	//Report #0003 from  7/08/2017
	//Fix    #0003 from --/--/20--
	//Commit d5fe5b07 add
	//Commit          fix
	QPoint *pl;
	if(bClient)
		pl = &other_player;
	else
		pl = &player;
	bool moved = false;
	game[pl->y()][pl->x()] = 0;
	game[pl->y()-1][pl->x()] = 0;
	switch(d)
	{
		case UP:
			if((pl->y()-1 == 0) ||
			   (game[pl->y()-2][pl->x()] != 0))
				break;
			moved = true;
			pl->setY(pl->y()-1);
			break;
		//===================================================
		case DOWN:
			if((pl->y() == GAME_ROWS-1) ||
			   (game[pl->y()+1][pl->x()] != 0))
				break;
			moved = true;
			pl->setY(pl->y()+1);
			break;
		//===================================================
		case LEFT:
			if((pl->x() == 0) ||
			   (game[pl->y()][pl->x()-1] != 0))
				if(!tryGo(UP))
					break;
			moved = true;
			game[pl->y()][pl->x()] = 0;
			game[pl->y()][pl->x() - 1] = 0;
			pl->setX(pl->x()-1);
			break;
		//===================================================
		case RIGHT:
			if((pl->x() == GAME_COLS-1) ||
			   (game[pl->y()][pl->x()+1] != 0))
				if(!tryGo(UP))
					break;
			moved = true;
			game[pl->y()][pl->x()] = 0;
			game[pl->y()-1][pl->x()] = 0;
			pl->setX(pl->x()+1);
			break;
		//===================================================
		default:
			break;
	}
	game[pl->y()][pl->x()] = 7;
	game[pl->y() - 1][pl->x()] = (bClient ? 8 : 6);;
	return moved;
}

void CWnd::savedata()
{
	string new_path = Q2Cstr(path) + "/data/set.xcg";
	FILE *file = fopen(new_path.c_str(), "w+t");
	if(file != 0)
	{
		size_t namelen = name.size();
		string tmp = Q2Cstr(name);
		fprintf(file, "%llu ", namelen);
		fprintf(file, "%s", tmp.c_str());
		fprintf(file, "\n");
		int mode = isFullScreen();
		fprintf(file, "%i ", mode);
		fprintf(file, "%hu", vol);
		fclose(file);
	}
	else
		QMessageBox::critical(0, "xCaveGame ERROR - Save settings",
			"File is corrupted, secured, opened in another application or disk is full");
}
void CWnd::loaddata()
{
	string new_path = Q2Cstr(path) + "/data/set.xcg";
	FILE *file = fopen(new_path.c_str(), "r+t");
	if(file != 0)
	{
		size_t namelen;
		fscanf(file, "%llu ", &namelen);
		string sss;
		for(size_t i = 0; i < namelen; ++i)
		{
			char ccc;
			fscanf(file, "%c", &ccc);
			sss += ccc;
		}
		name = C2Qstr(sss);
		fscanf(file, "\n");
		int mode; //1 - full; 0 - wnd
		fscanf(file, "%i ", &mode);
		switch(mode)
		{
		case 1:
			showFullScreen();
			break;
			showNormal();
			break;
		default:
			showNormal();
			break;
		}
		fscanf(file, "%hu", &vol);
		main_sound->setVolume(vol);
		fclose(file);
	}
	else
		QMessageBox::critical(0, "xCaveGame ERROR - Load settings",
			"File is corrupted, secured, opened in another application or disk is full");
}
