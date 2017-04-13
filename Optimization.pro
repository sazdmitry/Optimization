#-------------------------------------------------
#
# Project created by QtCreator 2016-12-16T21:33:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Optimization
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Domain.cpp \
    MyFunction.cpp \
    Nelder_mead.cpp \
    RandomSearch.cpp \
    Stopper.cpp \
    drawingarea.cpp \
    funcinformation.cpp

HEADERS  += mainwindow.h \
    Domain.h \
    MyFunction.h \
    Nelder_mead.h \
    RandomSearch.h \
    Stopper.h \
    drawingarea.h \
    funcinformation.h

FORMS    += mainwindow.ui
