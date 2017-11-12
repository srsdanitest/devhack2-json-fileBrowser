#-------------------------------------------------
#
# Project created by QtCreator 2017-11-12T10:50:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    filedownloader.cpp

HEADERS  += mainwindow.h \
    filedownloader.h

FORMS    += mainwindow.ui
QT += network
QT += core
CONFIG += console
