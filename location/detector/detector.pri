
#包含头文件的搜索路径
INCLUDEPATH += $$PWD/openCV\include

#添加的库路径和库名称
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

#工程中包含的头文件
HEADERS += $$PWD/detector.h\

#工程中包含的源文件
SOURCES += $$PWD/detector.cpp

