
#����ͷ�ļ�������·��
INCLUDEPATH += $$PWD/include

#��ӵĿ�·���Ϳ�����
LIBS += -L$$PWD/lib \
      -lHCCore \
      -lHCNetSDK \
      -lPlayCtrl

#�����а�����ͷ�ļ�
HEADERS += $$PWD/videosource.h

#�����а�����Դ�ļ�
SOURCES += $$PWD/videosource.cpp

