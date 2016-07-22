#-------------------------------------------------
#
# Project created by QtCreator 2016-06-25T09:36:14
#
#-------------------------------------------------
QT       += core gui
QT       += core
QT       += multimedia widgets
QT       -= gui
QT       += testlib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = AudioCore
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += fourier.cpp \
    SignalWait.cpp \
    qcustomplot.cpp \
    mainwindow.cpp
SOURCES += main.cpp
SOURCES += audiocore.cpp


HEADERS += audiocore.h \
    SignalWait.h \
    qcustomplot.h \
    mainwindow.h
HEADERS += fourier.h

FORMS += \
    mainwindow.ui
