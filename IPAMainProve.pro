#-------------------------------------------------
#
# Project created by QtCreator 2015-02-23T21:34:23
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = FlowLoop
TEMPLATE = app

QMAKE_CXXFLAGS = -std=c++11

SOURCES += main.cpp\
        meterwindow.cpp \
    myudp.cpp

HEADERS  += meterwindow.h \
    myudp.h

FORMS    += meterwindow.ui
