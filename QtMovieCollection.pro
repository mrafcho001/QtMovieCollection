#-------------------------------------------------
#
# Project created by QtCreator 2012-03-04T18:41:22
#
#-------------------------------------------------

QT       += core gui

TARGET = QtMovieCollection
TEMPLATE = app


SOURCES += src/main.cpp\
		src/mainwindow.cpp \
    src/movieinfo.cpp \
    src/movielistmodel.cpp \
    src/moviefilterproxymodel.cpp \
    src/filtersearchwidget.cpp \
    src/moviecollection.cpp \
    src/moviecollectionstreemodel.cpp \
    src/addnewmoviedialog.cpp \
    src/importlist.cpp

HEADERS  += src/mainwindow.h \
    src/movieinfo.h \
    src/movielistmodel.h \
    src/moviefilterproxymodel.h \
    src/filtersearchwidget.h \
    src/moviecollection.h \
    src/moviecollectionstreemodel.h \
    src/constants.h \
    src/addnewmoviedialog.h \
    src/importlist.h

FORMS    += src/mainwindow.ui \
    src/filtersearchwidget.ui \
    src/addnewmoviedialog.ui \
    src/importlist.ui

OBJECTS_DIR = build/.obj
MOC_DIR = build/.moc
RCC_DIR = build/.rcc
UI_DIR = build/.ui

CONFIG(debug, debug|release){
    DESTDIR = build/debug

	CONFIG -= release
	CONFIG += debug
	QMAKE_CXXFLAGS_RELEASE += -g
	QMAKE_CFLAGS_RELEASE += -g
}
else {
    DESTDIR = build/release

	CONFIG += release
	CONFIG -= debug
}

RESOURCES += \
    resources/resources.qrc

OTHER_FILES += \
    resources/importlist.sample
