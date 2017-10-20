#ifndef STRUCTDATA
#define STRUCTDATA

#include <QtCore>
#include <QtGui>
#include <QtDebug>


#define MAX_LOCK_COUNT 5
#define MAX_LOST_COUNT 15
//检测结果滤波结构(还没有做)
struct DetectorStatStruct
{
    //存储状态
    bool isTargetLocked;//目标被查找到
    int targetLockCount;//目标连续存在计数
    int targetLostCount;//目标消失计数

    float filted_x;//目标平均滤波后的x坐标
    float filted_y;//目标平均滤波后的y坐标
    float filted_r;
    float filted_Strength;
};

//检测器参数结构
struct DetectParamStruct//检测参数
{
    //检测参数
    double dp;            //缩放参数
    double min_dist;      //圆心间最小距离
    int canny_threshold;  //canny阈值
    int acc_threshold;    //累加量阈值
    int minRadius;        //检测的最小圆半径
    int maxRadius;        //检测的最大圆半径
    //检测区域限定参数
    int ROI_CenterLine;   //检测区域中心线
    int ROI_Heigh;        //检测区域高度
    int ROI_CenterRange;  //罐口在中心区域出现的范围
    int maxCentBrightness;//罐中心最高亮度
    bool settingMode;   //参数设定模式
};

//检测器结果结构
struct DetectResultStruct//检测结果
{
    //罐口信息
    bool isCircleDetected;
    QPointF circleCenter;
    float circleRadius;
    float raw_strength;
    int accum_count;
    int brightness;
    int satisfie_Circles;

    //图像信息
    QImage histogramImg;
    QImage detectImg_contour;
    QImage detectImg_contour_mask;
    QImage detectImg_hough;
};

//摄像头参数结构
struct IPCameraParamStruct//camera通道设置参数结构体定义
{
    QString IpAddress;//IPC IP
    QString UserName;//IPC 用户名
    QString Password;//IPC 密码

    bool    channalNameEN;//预览的图象上是否显示通道名称：0-不显示，1-显示（区域大小704*576）
    QString channalName;//通道名称
    int     channalNameX;//通道名称显示位置的x坐标
    int     channalNameY;//通道名称显示位置的y坐标

    bool    OSD_EN;//预览的图象上是否显示OSD：0-不显示，1-显示（区域大小704*576）
    int     OSD_X;//OSD的x坐标
    int     OSD_Y;//OSD的y坐标
    int     OSD_Type;//OSD类型(年月日格式)：
                     //0－XXXX-XX-XX 年月日
                     //1－XX-XX-XXXX 月日年
                     //2－XXXX年XX月XX日
                     //3－XX月XX日XXXX年
                     //4－XX-XX-XXXX 日月年
                     //5－XX日XX月XXXX年
                     //6－xx/xx/xxxx 月/日/年
                     //7－xxxx/xx/xx 年/月/日
                     //8－xx/xx/xxxx 日/月/年
    bool    OSD_DispWeekEN;//是否显示星期：0-不显示，1-显示
    int     OSD_HourOSDType;//小时制：0表示24小时制，1表示12小时制或am/pm
    int     OSD_FontSize;//字体大小：0- 16*16(中)/8*16(英)，1- 32*32(中)/16*32(英)，2- 64*64(中)/32*64(英)，3- 48*48(中)/24*48(英)，0xff-自适应(adaptive)
    long    OSD_Color;//字体颜色
};

//原始帧结构
struct FrameRawDataStruct
{
    QByteArray imgData;
    int dataLength;
    int imgWidth;
    int imgHeigh;
    int frameRate;
    long frameNum;
    long frameStamp;
};


#endif // STRUCTDATA

