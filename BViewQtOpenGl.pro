#-------------------------------------------------
#
# Project created by QtCreator 2012-03-27T15:06:30
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = BViewQtOpenGl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    openglcanvas.cpp \
    bimagemanager.cpp \
    bdirectory.cpp \
    BViewQtOpenGl_gtest.cpp \
    bmpfileloader.cpp \
    DataAllocator.cpp \
    bimage.cpp \
    brender.cpp \
    bimageprocess.cpp

HEADERS  += mainwindow.h \
    openglcanvas.h \
    bimagemanager.h \
    bdirectory.h \
    fileloaderfactory.h \
    fileloader.h \
    bsingletoncache.h \
    bcache.h \
    icacheitem.h \
    bmpfileloader.h \
    DataAllocator.h \
    bimage.h \
    bimagefileloader.h \
    globalstruct.h \
    brender.h \
    bimageprocess.h

FORMS    += mainwindow.ui

INCLUDEPATH += "gtest/include"
LIBS += -Llibs -lgtestd -lbmplib
CONFIG += console
