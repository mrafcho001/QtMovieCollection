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
    movielistmodel.cpp \
    moviefilterproxymodel.cpp \
    filtersearchwidget.cpp \
    moviecollection.cpp \
    moviecollectionstreemodel.cpp \
    addnewmoviedialog.cpp

HEADERS  += mainwindow.h \
    movieinfo.h \
    movielistmodel.h \
    moviefilterproxymodel.h \
    filtersearchwidget.h \
    moviecollection.h \
    moviecollectionstreemodel.h \
    constants.h \
    addnewmoviedialog.h

FORMS    += mainwindow.ui \
    filtersearchwidget.ui \
    addnewmoviedialog.ui

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

RESOURCES += \
    ../resources/resources.qrc
