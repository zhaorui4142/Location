
//ͷ�ļ�������
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QApplication>
#include <QFile>
#include <QSettings>
#include <QMessageBox>
#include <QPoint>
#include <QDebug>

//�궨����
#define CHINESE_CODEC QString::fromLocal8Bit

//MainWindows��Ĺ��캯��
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //����ΪIPC��ʼ��
    //������Ҫע�⣬��win10��Ĭ��·�������ǵ�ǰ�����ļ���·��������c:/user/zhaorui/������Ҫ�Ȼ�ȡ��ǰ��ִ���ļ���·��
    QString file = QCoreApplication::applicationDirPath()+"/config.ini";
    if(QFile::exists(file))
    {
        //��ȡ����
        QSettings config(file,QSettings::IniFormat);
        p_video_source_ = new VideoSource(config, this);
        p_detector_ = new Detector(config,this);
    }
    else
    {
        QMessageBox::warning(this,CHINESE_CODEC("����"),CHINESE_CODEC("�Ҳ��������ļ���config.ini"), QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
        QTimer::singleShot(0, qApp, SLOT(quit()));
    }
}

//MainWindows�����������
MainWindow::~MainWindow()
{
    delete ui;
}

//resize�¼�
void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    int w1 = ui->openGLWidget->size().width();
    int h1 = ui->openGLWidget->size().height();
    QPoint point;

    //ά�ָ߿��
    if(w1*9 > h1*16)
    {
        if(h1*16/9 >= ui->openGLWidget->minimumSizeHint().width())
        {
            //�������
            ui->openGLWidget->resize(h1*16/9,h1);
            //����λ��
            point.setX(ui->openGLWidget->x() + (w1-(h1*16/9))/2);
            point.setY(ui->openGLWidget->y());
            ui->openGLWidget->move(point);
        }
    }
    else
    {
        if(w1*9/16 >= ui->openGLWidget->minimumSizeHint().height())
        {
            //�������
            ui->openGLWidget->resize(w1,w1*9/16);
            //����λ��
            point.setX(ui->openGLWidget->x());
            point.setY(ui->openGLWidget->y() + (h1-(w1*9/16))/2);
            ui->openGLWidget->move(point);
        }
    }
}

//���԰�ť
void MainWindow::on_pushButton_clicked()
{
    starCameraPreview();
}

//˽�вۺ�������ʼԤ��
void MainWindow::starCameraPreview()
{
    //�����źźͲ�
    qRegisterMetaType<FrameRawDataStruct>("FrameRawDataStruct");
    qRegisterMetaType<DetectResultStruct>("DetectResultStruct");
    //ͼ��֡Frame���͵�OpenGL������ʾ
    connect(p_video_source_,SIGNAL(frameGenerated(FrameRawDataStruct)),ui->openGLWidget,SLOT(receiveFrame(FrameRawDataStruct)));
    //ͼ��֡Frame���͵�Detector��������ͼ��
    connect(p_video_source_,SIGNAL(frameGenerated(FrameRawDataStruct)),p_detector_,SLOT(receiveFrame(FrameRawDataStruct)));
    //�����Result���͵�OpenGL������ʾ
    connect(p_detector_,SIGNAL(resultReady(DetectResultStruct)),ui->openGLWidget,SLOT(receiveDetectorResult(DetectResultStruct)),Qt::QueuedConnection);
    //�����ģ�鿪ʼȡ��
    p_video_source_->starCaptureVideo();

}

//˽�вۺ������ر�Ԥ��
void MainWindow::stopCameraPreview()
{
    //�����ģ��ֹͣȡ��
    p_video_source_->stopCaptureVideo();
    //�Ͽ��źźͲ�
}

//˽�вۺ�������ʼͼ��ʶ��
void MainWindow::startImageRecognition()
{
    //�����ģ�鿪ʼȡ��
    p_video_source_->starCaptureVideo();
}

//˽�вۺ������ر�ͼ��ʶ��
void MainWindow::stopImageRecognition()
{

}

void MainWindow::FrameDealWith()
{

}






