#include "videosource.h"
#include <QMessageBox>

//构造函数================================================
VideoSource::VideoSource(QSettings &config, QObject *parent) : QObject(parent)
{
    //从文件读取IPC参数
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

//析构函数================================================
VideoSource::~VideoSource()
{
    stopCaptureVideo();
}

//开始取流================================================
bool VideoSource::starCaptureVideo(void)
{
    if(is_video_capturing_ == true)
        return true;

    //SDK初始化
    if(!NET_DVR_Init())
        return false;

    //设置重连时间
    NET_DVR_SetConnectTime(1000,1);
    NET_DVR_SetReconnect(10000,true);

    //设置注册信息
    QByteArray IpAddress = camera_param_.IpAddress.toLatin1();
    QByteArray UserName = camera_param_.UserName.toLatin1();
    QByteArray Password = camera_param_.Password.toLatin1();

    //注册设备
    lUserID = NET_DVR_Login_V30(IpAddress.data(),8000,UserName.data(),Password.data(),&struDeviceInfo);
    if(lUserID<0)
    {
        QMessageBox::warning(NULL,QString::fromLocal8Bit("错误："),QString::fromLocal8Bit("摄像机连接失败！"), QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
        NET_DVR_Cleanup();
        return false;
    }

    //读取通道参数设置信息
    DWORD dwReturnLen;
    NET_DVR_PICCFG_V40 channalParams = {0};
    int iRet = NET_DVR_GetDVRConfig(lUserID, NET_DVR_GET_PICCFG_V40, struDeviceInfo.byStartChan,&channalParams, sizeof(NET_DVR_PICCFG_V40), &dwReturnLen);
    if (!iRet)
    {
        NET_DVR_Logout(lUserID);
        NET_DVR_Cleanup();
        return false;
    }

    //修改通道参数设置信息
    for(int i=0; (i<camera_param_.channalName.size())&&(i<NAME_LEN); i++)
    {
        QByteArray nameByte = camera_param_.channalName.toLatin1();
        channalParams.sChanName[i] = (BYTE)nameByte.at(i);//通道名称
    }
    channalParams.dwShowChanName = (DWORD)(camera_param_.channalNameEN);//预览的图象上是否显示通道名称：0-不显示，1-显示（区域大小704*576）
    channalParams.wShowNameTopLeftX = (WORD)camera_param_.channalNameX;//通道名称显示位置的x坐标
    channalParams.wShowNameTopLeftY = (WORD)camera_param_.channalNameY;//通道名称显示位置的y坐标
    channalParams.dwShowOsd = (DWORD)(camera_param_.OSD_EN);//预览的图象上是否显示OSD：0-不显示，1-显示（区域大小704*576）
    channalParams.wOSDTopLeftX = (WORD)camera_param_.OSD_X;//OSD的x坐标
    channalParams.wOSDTopLeftY = (WORD)camera_param_.OSD_Y;//OSD的y坐标
    channalParams.byOSDType = (BYTE)camera_param_.OSD_Type;//OSD类型(年月日格式)：
    channalParams.byDispWeek = (BYTE)camera_param_.OSD_DispWeekEN;//是否显示星期：0-不显示，1-显示
    channalParams.byHourOSDType = (BYTE)camera_param_.OSD_HourOSDType;//小时制：0表示24小时制，1表示12小时制或am/pm
    channalParams.byFontSize = (BYTE)camera_param_.OSD_FontSize;//字体大小：0- 16*16(中)/8*16(英)，1- 32*32(中)/16*32(英)，2- 64*64(中)/32*64(英)，3- 48*48(中)/24*48(英)，0xff-自适应(adaptive)

    //写入通道参数设置信息
    iRet = NET_DVR_SetDVRConfig(lUserID, NET_DVR_SET_PICCFG_V40, struDeviceInfo.byStartChan,&channalParams, sizeof(NET_DVR_PICCFG_V40));
    if (!iRet)
    {
        NET_DVR_Logout(lUserID);
        NET_DVR_Cleanup();
        return false;
    }

    //注册异常消息回调函数
    NET_DVR_SetExceptionCallBack_V30(0, NULL, ExceptionCallBack, this);

    //启动预览并设置回调数据流
    struPlayInfo.hPlayWnd     = NULL;    //需要SDK解码时句柄设为有效值，仅取流不解码时可设为空
    struPlayInfo.lChannel     = 1;       //预览通道号
    struPlayInfo.dwStreamType = 0;       //0-主码流，1-子码流，2-码流3，3-码流4，以此类推
    struPlayInfo.dwLinkMode   = 0;       //0- TCP方式，1- UDP方式，2- 多播方式，3- RTP方式，4-RTP/RTSP，5-RSTP/HTTP
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

//停止取流================================================
void VideoSource::stopCaptureVideo(void)
{
    //关闭预览
    NET_DVR_StopRealPlay(lRealPlayHandle);

    //释放播放库资源
    PlayM4_Stop(lPort);
    PlayM4_CloseStream(lPort);
    PlayM4_FreePort(lPort);

    //注销用户
    NET_DVR_Logout(lUserID);
    NET_DVR_Cleanup();

    is_video_capturing_ = false;
}

//异常回调函数================================================
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

//取流回调函数================================================
void CALLBACK VideoSource::RealDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,void* pUser)
{
    UNREFERENCED_PARAMETER(lRealHandle);
    //设置this指针
    VideoSource *pThis = (VideoSource *)pUser;

    switch (dwDataType)
    {
    case NET_DVR_SYSHEAD: //系统头

        if (!PlayM4_GetPort(&(pThis->lPort)))  //获取播放库未使用的通道号
        {
            break;
        }
        //m_iPort = lPort; //第一次回调的是系统头，将获取的播放库port号赋值给全局port，下次回调数据时即使用此port号播放
        if (dwBufSize > 0)
        {
            if (!PlayM4_SetStreamOpenMode(pThis->lPort, STREAME_REALTIME))  //设置实时流播放模式
            {
                break;
            }

            if (!PlayM4_OpenStream(pThis->lPort, pBuffer, dwBufSize, 1024*1024)) //打开流接口
            {
                break;
            }

            if (!PlayM4_SetDisplayBuf(pThis->lPort, 15)) //设置播放缓冲区最大帧数
            {
                break;
            }

            if(!PlayM4_SetDecCallBackMend(pThis->lPort,DecCallBack,(long)pThis))//设置解码回调函数
            {
                break;
            }
            if (!PlayM4_Play(pThis->lPort, pThis->hWndPlay)) //播放开始
            {
                break;
            }
        }
        break;
    case NET_DVR_STREAMDATA:   //码流数据
        if (dwBufSize > 0 && pThis->lPort != -1)
        {
            if (!PlayM4_InputData(pThis->lPort, pBuffer, dwBufSize))
            {
                break;
            }
        }
        break;
    default: //其他数据
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

//解码回调函数================================================
void CALLBACK VideoSource::DecCallBack(LONG nPort,char* pBuf,LONG nSize,FRAME_INFO *pFrameInfo,LONG nUser,LONG nReserved2)
{
    UNREFERENCED_PARAMETER(nPort);
    UNREFERENCED_PARAMETER(nReserved2);
    LONG lFrameType=pFrameInfo->nType;
    VideoSource *pThis = (VideoSource *)nUser;
    //判断视频帧的数据格式是否为YV12
    if(lFrameType==T_YV12)
    {
        //创建数组
        int dataLength=(int)nSize;
        QByteArray img;
        img.resize(dataLength);
        memcpy(img.data(),pBuf,dataLength);
        //发送信号
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
        //关闭预览
        pThis->stopCaptureVideo();
        QMessageBox::warning(NULL,QString::fromLocal8Bit("错误"),QString::fromLocal8Bit("IPC图像输出格式错误！"),QMessageBox::Yes);
    }
}



