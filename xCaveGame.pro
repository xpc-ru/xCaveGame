#--------------------------------------------------#
# Project created by QtCreator 2017-03-30T16:27:47 #
#--------------------------------------------------#

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = xCaveGame
TEMPLATE = app
QMAKE_LFLAGS += -O0

SOURCES += main.cpp \
           wnd.cpp \
           gSocket.cpp \
           dlg_connect_enter_ip.cpp \
           dlg_settings.cpp

HEADERS  += wnd.h \
            gSocket.h \
            tcp_protocol.h \
            dlg_connect_enter_ip.h \
            dlg_settings.h

RESOURCES +=

FORMS += connect_enter_ip.ui \
         settings.ui
