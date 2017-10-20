#ifndef STRUCTDATA
#define STRUCTDATA

#include <QtCore>
#include <QtGui>
#include <QtDebug>


#define MAX_LOCK_COUNT 5
#define MAX_LOST_COUNT 15
//������˲��ṹ(��û����)
struct DetectorStatStruct
{
    //�洢״̬
    bool isTargetLocked;//Ŀ�걻���ҵ�
    int targetLockCount;//Ŀ���������ڼ���
    int targetLostCount;//Ŀ����ʧ����

    float filted_x;//Ŀ��ƽ���˲����x����
    float filted_y;//Ŀ��ƽ���˲����y����
    float filted_r;
    float filted_Strength;
};

//����������ṹ
struct DetectParamStruct//������
{
    //������
    double dp;            //���Ų���
    double min_dist;      //Բ�ļ���С����
    int canny_threshold;  //canny��ֵ
    int acc_threshold;    //�ۼ�����ֵ
    int minRadius;        //������СԲ�뾶
    int maxRadius;        //�������Բ�뾶
    //��������޶�����
    int ROI_CenterLine;   //�������������
    int ROI_Heigh;        //�������߶�
    int ROI_CenterRange;  //�޿�������������ֵķ�Χ
    int maxCentBrightness;//�������������
    bool settingMode;   //�����趨ģʽ
};

//���������ṹ
struct DetectResultStruct//�����
{
    //�޿���Ϣ
    bool isCircleDetected;
    QPointF circleCenter;
    float circleRadius;
    float raw_strength;
    int accum_count;
    int brightness;
    int satisfie_Circles;

    //ͼ����Ϣ
    QImage histogramImg;
    QImage detectImg_contour;
    QImage detectImg_contour_mask;
    QImage detectImg_hough;
};

//����ͷ�����ṹ
struct IPCameraParamStruct//cameraͨ�����ò����ṹ�嶨��
{
    QString IpAddress;//IPC IP
    QString UserName;//IPC �û���
    QString Password;//IPC ����

    bool    channalNameEN;//Ԥ����ͼ�����Ƿ���ʾͨ�����ƣ�0-����ʾ��1-��ʾ�������С704*576��
    QString channalName;//ͨ������
    int     channalNameX;//ͨ��������ʾλ�õ�x����
    int     channalNameY;//ͨ��������ʾλ�õ�y����

    bool    OSD_EN;//Ԥ����ͼ�����Ƿ���ʾOSD��0-����ʾ��1-��ʾ�������С704*576��
    int     OSD_X;//OSD��x����
    int     OSD_Y;//OSD��y����
    int     OSD_Type;//OSD����(�����ո�ʽ)��
                     //0��XXXX-XX-XX ������
                     //1��XX-XX-XXXX ������
                     //2��XXXX��XX��XX��
                     //3��XX��XX��XXXX��
                     //4��XX-XX-XXXX ������
                     //5��XX��XX��XXXX��
                     //6��xx/xx/xxxx ��/��/��
                     //7��xxxx/xx/xx ��/��/��
                     //8��xx/xx/xxxx ��/��/��
    bool    OSD_DispWeekEN;//�Ƿ���ʾ���ڣ�0-����ʾ��1-��ʾ
    int     OSD_HourOSDType;//Сʱ�ƣ�0��ʾ24Сʱ�ƣ�1��ʾ12Сʱ�ƻ�am/pm
    int     OSD_FontSize;//�����С��0- 16*16(��)/8*16(Ӣ)��1- 32*32(��)/16*32(Ӣ)��2- 64*64(��)/32*64(Ӣ)��3- 48*48(��)/24*48(Ӣ)��0xff-����Ӧ(adaptive)
    long    OSD_Color;//������ɫ
};

//ԭʼ֡�ṹ
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

