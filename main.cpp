//xCaveGame
//(C) 2017, xPC
//Made in Russia
//Uses Qt 5.8.0 for MSVC 2015, 64-bit
//Git binaries - Windows 7 x64
#include "wnd.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CWnd w;

	return a.exec();
}
