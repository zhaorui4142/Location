#-------------------------------------------------
#
# Project created by QtCreator 2016-12-28T11:18:54
#
#-------------------------------------------------

#QTģ�����
QT       += core gui widgets

#���Ŀ��
TARGET   = location
TEMPLATE = app

#����ͷ�ļ�������·��
INCLUDEPATH += $$PWD

#�����Զ���ģ��
include(videosource/videosource.pri)
include(mainwindow/mainwindow.pri)
include(glwidget/glwidget.pri)
include(detector/detector.pri)

#QT����ģ�龯��
DEFINES  += QT_DEPRECATED_WARNINGS

#����Դ�ļ�
SOURCES += main.cpp\

#����ͷ�ļ�
HEADERS += struct-data.h

DISTFILES += \
    readme.txt \

RESOURCES += \
    resource/shaders.qrc \
    resource/textures.qrc


