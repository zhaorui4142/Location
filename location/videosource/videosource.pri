
#包含头文件的搜索路径
INCLUDEPATH += $$PWD/include

#添加的库路径和库名称
LIBS += -L$$PWD/lib \
      -lHCCore \
      -lHCNetSDK \
      -lPlayCtrl

#工程中包含的头文件
HEADERS += $$PWD/videosource.h

#工程中包含的源文件
SOURCES += $$PWD/videosource.cpp

