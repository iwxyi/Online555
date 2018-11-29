#-------------------------------------------------
#
# Project created by QtCreator 2018-11-04T15:25:17
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Online555
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    loginwindow.cpp \
    chequer.cpp \
    boardwidget.cpp \
    boardwindow.cpp \
    gametablewidget.cpp \
    fileutil.cpp \
    socketutil.cpp \
    stringutil.cpp \
    globals.cpp

HEADERS  += mainwindow.h \
    loginwindow.h \
    chequer.h \
    boardwidget.h \
    boardwindow.h \
    gametablewidget.h \
    fileutil.h \
    socketutil.h \
    stringutil.h \
    globals.h
FORMS    += mainwindow.ui


RESOURCES += \
    Resources/src.qrc
