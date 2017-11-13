#-------------------------------------------------
#
# Project created by QtCreator 2017-11-12T22:33:07
#
#-------------------------------------------------

QT       += core gui
QT += core
QT       += network
QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = preparev2
TEMPLATE = app
CONFIG   += console

SOURCES += main.cpp\
        mainwindow.cpp \
    filess.cpp

HEADERS  += mainwindow.h \
    filess.h

FORMS    += mainwindow.ui

RESOURCES += \
    resourceapp.qrc
