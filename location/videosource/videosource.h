#ifndef VIDEOSOURCE_H
#define VIDEOSOURCE_H

//------------ģ��˵��------------------
//�������̣�
//           CameraInit
//               ��
//         starCaptureVideo
//               ��
//        emit (generateFrame)
//               ��
//         stopCaptureVideo
//
//-------------------------------------

//ͷ�ļ�������
#include <windows.h>
#include <QObject>
#include <QSettings>
#include "HCNetSDK.h"
#include "plaympeg4.h"
#include "struct-data.h"


//��������
#define FRAME_LENGTH 1382400
#define FRAME_WIDTH 1280
#define FRAME_HEIGH 720


//������
class VideoSource : public QObject
{
    Q_OBJECT
public:
    explicit VideoSource(QSettings &config, QObject *parent = 0);
    ~VideoSource();
    //���к���
    bool starCaptureVideo(void);
    void stopCaptureVideo(void);


signals:
    //�µ�ͼ��֡�����ź�
    void frameGenerated(FrameRawDataStruct frame);

private:
    //˽�к���
    static void CALLBACK ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser);
    static void CALLBACK RealDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,void* pUser);
    static void CALLBACK DecCallBack(LONG nPort,char* pBuf,LONG nSize,FRAME_INFO *pFrameInfo,LONG nUser,LONG nReserved2);

    //˽�б���
    LONG lUserID;
    LONG lRealPlayHandle = -1;
    LONG lPort; //ȫ�ֵĲ��ſ�port��
    HWND hWndPlay=NULL;//ȫ�ֲ��Ŵ��ڵľ��
    NET_DVR_DEVICEINFO_V30 struDeviceInfo;
    NET_DVR_PREVIEWINFO struPlayInfo;

    IPCameraParamStruct camera_param_;
    bool is_video_capturing_ = false;

};

#endif // VIDEOSOURCE_H
