
#����ͷ�ļ�������·��
INCLUDEPATH += $$PWD/openCV\include

#��ӵĿ�·���Ϳ�����
LIBS += -L$$PWD/openCV\x86\vc12\lib \
      -lopencv_core2411 \
      -lopencv_calib3d2411 \
      -lopencv_contrib2411 \
      -lopencv_features2d2411 \
      -lopencv_flann2411 \
      -lopencv_gpu2411 \
      -lopencv_highgui2411 \
      -lopencv_imgproc2411 \
      -lopencv_legacy2411 \
      -lopencv_ml2411 \
      -lopencv_nonfree2411 \
      -lopencv_objdetect2411 \
      -lopencv_ocl2411 \
      -lopencv_photo2411 \
      -lopencv_stitching2411 \
      -lopencv_superres2411 \
      -lopencv_ts2411 \
      -lopencv_video2411 \
      -lopencv_videostab2411

#�����а�����ͷ�ļ�
HEADERS += $$PWD/detector.h\

#�����а�����Դ�ļ�
SOURCES += $$PWD/detector.cpp

