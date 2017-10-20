#ifndef VIDEOSOURCE_H
#define VIDEOSOURCE_H

//------------模块说明------------------
//工作流程：
//           CameraInit
//               ↓
//         starCaptureVideo
//               ↓
//        emit (generateFrame)
//               ↓
//         stopCaptureVideo
//
//-------------------------------------

//头文件包含区
#include <windows.h>
#include <QObject>
#include <QSettings>
#include "HCNetSDK.h"
#include "plaympeg4.h"
#include "struct-data.h"


//常量定义
#define FRAME_LENGTH 1382400
#define FRAME_WIDTH 1280
#define FRAME_HEIGH 720


//类声明
class VideoSource : public QObject
{
    Q_OBJECT
public:
    explicit VideoSource(QSettings &config, QObject *parent = 0);
    ~VideoSource();
    //共有函数
    bool starCaptureVideo(void);
    void stopCaptureVideo(void);


signals:
    //新的图像帧生成信号
    void frameGenerated(FrameRawDataStruct frame);

private:
    //私有函数
    static void CALLBACK ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser);
    static void CALLBACK RealDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,void* pUser);
    static void CALLBACK DecCallBack(LONG nPort,char* pBuf,LONG nSize,FRAME_INFO *pFrameInfo,LONG nUser,LONG nReserved2);

    //私有变量
    LONG lUserID;
    LONG lRealPlayHandle = -1;
    LONG lPort; //全局的播放库port号
    HWND hWndPlay=NULL;//全局播放窗口的句柄
    NET_DVR_DEVICEINFO_V30 struDeviceInfo;
    NET_DVR_PREVIEWINFO struPlayInfo;

    IPCameraParamStruct camera_param_;
    bool is_video_capturing_ = false;

};

#endif // VIDEOSOURCE_H
