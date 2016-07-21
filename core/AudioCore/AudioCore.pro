#-------------------------------------------------
#
# Project created by QtCreator 2016-06-25T09:36:14
#
#-------------------------------------------------

QT       += core
QT       += multimedia widgets
QT       -= gui
QT       += testlib

TARGET = AudioCore
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app



SOURCES += fourier.cpp \
    SignalWait.cpp
SOURCES += main.cpp
SOURCES += audiocore.cpp


HEADERS += audiocore.h \
    SignalWait.h
HEADERS += fourier.h
