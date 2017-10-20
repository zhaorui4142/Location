#-------------------------------------------------
#
# Project created by QtCreator 2016-12-28T11:18:54
#
#-------------------------------------------------

#QT模块加载
QT       += core gui widgets

#输出目标
TARGET   = location
TEMPLATE = app

#包含头文件的搜索路径
INCLUDEPATH += $$PWD

#包含自定义模块
include(videosource/videosource.pri)
include(mainwindow/mainwindow.pri)
include(glwidget/glwidget.pri)
include(detector/detector.pri)

#QT废弃模块警告
DEFINES  += QT_DEPRECATED_WARNINGS

#包含源文件
SOURCES += main.cpp\

#包含头文件
HEADERS += struct-data.h

DISTFILES += \
    readme.txt \

RESOURCES += \
    resource/shaders.qrc \
    resource/textures.qrc


