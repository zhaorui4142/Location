#include "videosource.h"
#include <QMessageBox>

//���캯��================================================
VideoSource::VideoSource(QSettings &config, QObject *parent) : QObject(parent)
{
    //���ļ���ȡIPC����
    camera_param_.IpAddress       = config.value("LOGIN/IP").toString();
    camera_param_.UserName        = config.value("LOGIN/USER_NAME").toString();
    camera_param_.Password        = config.value("LOGIN/PASSWORD").toString();
    camera_param_.channalNameEN   = config.value("CHANNAL_NAME/DISPLAY").toBool();
    camera_param_.channalName     = config.value("CHANNAL_NAME/NAME").toString();
    camera_param_.channalNameX    = config.value("CHANNAL_NAME/POS_X").toInt();
    camera_param_.channalNameY    = config.value("CHANNAL_NAME/POS_Y").toInt();
    camera_param_.OSD_EN          = config.value("OSD/DISPLAY").toBool();
    camera_param_.OSD_DispWeekEN  = config.value("OSD/DISP_WEEK").toBool();
    camera_param_.OSD_X           = config.value("OSD/POS_X").toInt();
    camera_param_.OSD_Y           = config.value("OSD/POS_Y").toInt();
    camera_param_.OSD_Type        = config.value("OSD/DATE_TYPE").toInt();
    camera_param_.OSD_HourOSDType = config.value("OSD/HOUR_TYPE").toInt();
    camera_param_.OSD_FontSize    = config.value("OSD/FONT_TYPE").toInt();
}

//��������================================================
VideoSource::~VideoSource()
{
    stopCaptureVideo();
}

//��ʼȡ��================================================
bool VideoSource::starCaptureVideo(void)
{
    if(is_video_capturing_ == true)
        return true;

    //SDK��ʼ��
    if(!NET_DVR_Init())
        return false;

    //��������ʱ��
    NET_DVR_SetConnectTime(1000,1);
    NET_DVR_SetReconnect(10000,true);

    //����ע����Ϣ
    QByteArray IpAddress = camera_param_.IpAddress.toLatin1();
    QByteArray UserName = camera_param_.UserName.toLatin1();
    QByteArray Password = camera_param_.Password.toLatin1();

    //ע���豸
    lUserID = NET_DVR_Login_V30(IpAddress.data(),8000,UserName.data(),Password.data(),&struDeviceInfo);
    if(lUserID<0)
    {
        QMessageBox::warning(NULL,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("���������ʧ�ܣ�"), QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
        NET_DVR_Cleanup();
        return false;
    }

    //��ȡͨ������������Ϣ
    DWORD dwReturnLen;
    NET_DVR_PICCFG_V40 channalParams = {0};
    int iRet = NET_DVR_GetDVRConfig(lUserID, NET_DVR_GET_PICCFG_V40, struDeviceInfo.byStartChan,&channalParams, sizeof(NET_DVR_PICCFG_V40), &dwReturnLen);
    if (!iRet)
    {
        NET_DVR_Logout(lUserID);
        NET_DVR_Cleanup();
        return false;
    }

    //�޸�ͨ������������Ϣ
    for(int i=0; (i<camera_param_.channalName.size())&&(i<NAME_LEN); i++)
    {
        QByteArray nameByte = camera_param_.channalName.toLatin1();
        channalParams.sChanName[i] = (BYTE)nameByte.at(i);//ͨ������
    }
    channalParams.dwShowChanName = (DWORD)(camera_param_.channalNameEN);//Ԥ����ͼ�����Ƿ���ʾͨ�����ƣ�0-����ʾ��1-��ʾ�������С704*576��
    channalParams.wShowNameTopLeftX = (WORD)camera_param_.channalNameX;//ͨ��������ʾλ�õ�x����
    channalParams.wShowNameTopLeftY = (WORD)camera_param_.channalNameY;//ͨ��������ʾλ�õ�y����
    channalParams.dwShowOsd = (DWORD)(camera_param_.OSD_EN);//Ԥ����ͼ�����Ƿ���ʾOSD��0-����ʾ��1-��ʾ�������С704*576��
    channalParams.wOSDTopLeftX = (WORD)camera_param_.OSD_X;//OSD��x����
    channalParams.wOSDTopLeftY = (WORD)camera_param_.OSD_Y;//OSD��y����
    channalParams.byOSDType = (BYTE)camera_param_.OSD_Type;//OSD����(�����ո�ʽ)��
    channalParams.byDispWeek = (BYTE)camera_param_.OSD_DispWeekEN;//�Ƿ���ʾ���ڣ�0-����ʾ��1-��ʾ
    channalParams.byHourOSDType = (BYTE)camera_param_.OSD_HourOSDType;//Сʱ�ƣ�0��ʾ24Сʱ�ƣ�1��ʾ12Сʱ�ƻ�am/pm
    channalParams.byFontSize = (BYTE)camera_param_.OSD_FontSize;//�����С��0- 16*16(��)/8*16(Ӣ)��1- 32*32(��)/16*32(Ӣ)��2- 64*64(��)/32*64(Ӣ)��3- 48*48(��)/24*48(Ӣ)��0xff-����Ӧ(adaptive)

    //д��ͨ������������Ϣ
    iRet = NET_DVR_SetDVRConfig(lUserID, NET_DVR_SET_PICCFG_V40, struDeviceInfo.byStartChan,&channalParams, sizeof(NET_DVR_PICCFG_V40));
    if (!iRet)
    {
        NET_DVR_Logout(lUserID);
        NET_DVR_Cleanup();
        return false;
    }

    //ע���쳣��Ϣ�ص�����
    NET_DVR_SetExceptionCallBack_V30(0, NULL, ExceptionCallBack, this);

    //����Ԥ�������ûص�������
    struPlayInfo.hPlayWnd     = NULL;    //��ҪSDK����ʱ�����Ϊ��Чֵ����ȡ��������ʱ����Ϊ��
    struPlayInfo.lChannel     = 1;       //Ԥ��ͨ����
    struPlayInfo.dwStreamType = 0;       //0-��������1-��������2-����3��3-����4���Դ�����
    struPlayInfo.dwLinkMode   = 0;       //0- TCP��ʽ��1- UDP��ʽ��2- �ಥ��ʽ��3- RTP��ʽ��4-RTP/RTSP��5-RSTP/HTTP
    lRealPlayHandle = NET_DVR_RealPlay_V40(lUserID, &struPlayInfo, RealDataCallBack, this);
    if (lRealPlayHandle < 0)
    {
        NET_DVR_Logout(lUserID);
        NET_DVR_Cleanup();
        return false;
    }

    is_video_capturing_ = true;
    return true;
}

//ֹͣȡ��================================================
void VideoSource::stopCaptureVideo(void)
{
    //�ر�Ԥ��
    NET_DVR_StopRealPlay(lRealPlayHandle);

    //�ͷŲ��ſ���Դ
    PlayM4_Stop(lPort);
    PlayM4_CloseStream(lPort);
    PlayM4_FreePort(lPort);

    //ע���û�
    NET_DVR_Logout(lUserID);
    NET_DVR_Cleanup();

    is_video_capturing_ = false;
}

//�쳣�ص�����================================================
void CALLBACK VideoSource::ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
{
    UNREFERENCED_PARAMETER(dwType);
    UNREFERENCED_PARAMETER(lUserID);
    UNREFERENCED_PARAMETER(lHandle);
    UNREFERENCED_PARAMETER(pUser);
    //VideoSource *pThis = (VideoSource *)pUser;
    QString code="code:"+QString::number(NET_DVR_GetLastError());
    QMessageBox::warning(NULL,"Error",code,QMessageBox::Yes);
}

//ȡ���ص�����================================================
void CALLBACK VideoSource::RealDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,void* pUser)
{
    UNREFERENCED_PARAMETER(lRealHandle);
    //����thisָ��
    VideoSource *pThis = (VideoSource *)pUser;

    switch (dwDataType)
    {
    case NET_DVR_SYSHEAD: //ϵͳͷ

        if (!PlayM4_GetPort(&(pThis->lPort)))  //��ȡ���ſ�δʹ�õ�ͨ����
        {
            break;
        }
        //m_iPort = lPort; //��һ�λص�����ϵͳͷ������ȡ�Ĳ��ſ�port�Ÿ�ֵ��ȫ��port���´λص�����ʱ��ʹ�ô�port�Ų���
        if (dwBufSize > 0)
        {
            if (!PlayM4_SetStreamOpenMode(pThis->lPort, STREAME_REALTIME))  //����ʵʱ������ģʽ
            {
                break;
            }

            if (!PlayM4_OpenStream(pThis->lPort, pBuffer, dwBufSize, 1024*1024)) //�����ӿ�
            {
                break;
            }

            if (!PlayM4_SetDisplayBuf(pThis->lPort, 15)) //���ò��Ż��������֡��
            {
                break;
            }

            if(!PlayM4_SetDecCallBackMend(pThis->lPort,DecCallBack,(long)pThis))//���ý���ص�����
            {
                break;
            }
            if (!PlayM4_Play(pThis->lPort, pThis->hWndPlay)) //���ſ�ʼ
            {
                break;
            }
        }
        break;
    case NET_DVR_STREAMDATA:   //��������
        if (dwBufSize > 0 && pThis->lPort != -1)
        {
            if (!PlayM4_InputData(pThis->lPort, pBuffer, dwBufSize))
            {
                break;
            }
        }
        break;
    default: //��������
        if (dwBufSize > 0 && pThis->lPort != -1)
        {
            if (!PlayM4_InputData(pThis->lPort, pBuffer, dwBufSize))
            {
                break;
            }
        }
        break;
    }
}

//����ص�����================================================
void CALLBACK VideoSource::DecCallBack(LONG nPort,char* pBuf,LONG nSize,FRAME_INFO *pFrameInfo,LONG nUser,LONG nReserved2)
{
    UNREFERENCED_PARAMETER(nPort);
    UNREFERENCED_PARAMETER(nReserved2);
    LONG lFrameType=pFrameInfo->nType;
    VideoSource *pThis = (VideoSource *)nUser;
    //�ж���Ƶ֡�����ݸ�ʽ�Ƿ�ΪYV12
    if(lFrameType==T_YV12)
    {
        //��������
        int dataLength=(int)nSize;
        QByteArray img;
        img.resize(dataLength);
        memcpy(img.data(),pBuf,dataLength);
        //�����ź�
        FrameRawDataStruct frame;
        frame.imgData = img;
        frame.dataLength = dataLength;
        frame.imgWidth = (int)pFrameInfo->nWidth;
        frame.imgHeigh = (int)pFrameInfo->nHeight;
        frame.frameRate = (int)pFrameInfo->nFrameRate;
        frame.frameNum = (long)pFrameInfo->dwFrameNum;
        frame.frameStamp = (long)pFrameInfo->nStamp;
        emit pThis->frameGenerated(frame);
    }
    else
    {
        //�ر�Ԥ��
        pThis->stopCaptureVideo();
        QMessageBox::warning(NULL,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("IPCͼ�������ʽ����"),QMessageBox::Yes);
    }
}



