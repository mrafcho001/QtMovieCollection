#-------------------------------------------------
#
# Project created by QtCreator 2012-03-04T18:41:22
#
#-------------------------------------------------

QT       += core gui

TARGET = QtMovieCollection
TEMPLATE = app


SOURCES += main.cpp\
		mainwindow.cpp \
    movieinfo.cpp \
    collectionmanager.cpp \
    movielistmodel.cpp \
    moviefilterproxymodel.cpp \
    filtersearchwidget.cpp

HEADERS  += mainwindow.h \
    movieinfo.h \
    collectionmanager.h \
    movielistmodel.h \
    moviefilterproxymodel.h \
    filtersearchwidget.h

FORMS    += mainwindow.ui \
    filtersearchwidget.ui

OBJECTS_DIR = ../build/.obj
MOC_DIR = ../build/.moc
RCC_DIR = ../build/.rcc
UI_DIR = ../build/.ui

CONFIG(debug, debug|release){
	DESTDIR = ../build/debug

	CONFIG -= release
	CONFIG += debug
	QMAKE_CXXFLAGS_RELEASE += -g
	QMAKE_CFLAGS_RELEASE += -g
}
else {
	DESTDIR = ../build/release

	CONFIG += release
	CONFIG -= debug
}
