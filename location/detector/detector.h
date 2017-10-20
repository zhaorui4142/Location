#ifndef HOLEDETECTOR_H
#define HOLEDETECTOR_H

//----------------ģ�鹦��˵��--------------------
//Detector�ฺ�����ⲿ���ӣ�����ͼ�񣬷��ͽ��
//Detector��ÿ����һ��ͼ�������һ��Worker��Ķ��󣬲�����һ���߳�
//�������Ժ󽫽�����źŷ���ȥ�����Զ�����Worker����
//-----------------------------------------------

//ͷ�ļ�������
#include <windows.h>
#include <QObject>
#include <QList>
#include <QThread>
#include <windows.h>
#include "opencv2/opencv.hpp"
#include "struct-data.h"


//��������������ͼ�����ö��̼߳��㣬���ͽ��
class Detector : public QObject
{
    Q_OBJECT

public:
    explicit Detector(QSettings &settings,  QObject *parent = 0);
    ~Detector(void);

signals:
    //�������ź�
    void resultReady(DetectResultStruct result);

public slots:
    //����ͼ��ۺ���
    void receiveFrame(FrameRawDataStruct frame);

private:
    //˽�г�Ա����
    void readParamFromFile(QSettings &settings);
    //˽�б���
    DetectParamStruct param;
    QThreadPool *thread_pool;

};

//���㵥Ԫ
class Worker : public QObject, public QRunnable
{
    Q_OBJECT

signals:
    void resultReady(DetectResultStruct result);

public:
    Worker(DetectParamStruct param, FrameRawDataStruct frame, QObject *parent = 0);
    ~Worker(void);
    void run();

private:
    void findBestCircle(DetectParamStruct &param, cv::Mat &img, DetectResultStruct &result);
    void icvHoughSortDescent32s(int *array, size_t total, const int* aux);
    void icvHoughSortDescent32f(int *array, size_t total, const float* aux);
    QImage MatCopy2QImage(const cv::Mat &mat);
    QImage MatScaled2QImage(const cv::Mat &mat,double dp);
    cv::MatND getHistogram(const cv::Mat &image);
    QImage Histogram2QImage(const cv::Mat &hist);
    int thresholdOtsu(cv::Mat &img,cv::MatND &histogram);
    qreal getIntervalMillisecond();
    //˽�г�Ա
    DetectParamStruct param;
    FrameRawDataStruct frame;
    LARGE_INTEGER t1,t2,tc;
};


#endif // HOLEDETECTOR_H
