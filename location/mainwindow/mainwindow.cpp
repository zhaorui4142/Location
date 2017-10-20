
//头文件包含区
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QApplication>
#include <QFile>
#include <QSettings>
#include <QMessageBox>
#include <QPoint>
#include <QDebug>

//宏定义区
#define CHINESE_CODEC QString::fromLocal8Bit

//MainWindows类的构造函数
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //以下为IPC初始化
    //这里需要注意，在win10下默认路径不再是当前运行文件的路径，而是c:/user/zhaorui/，所以要先获取当前可执行文件的路径
    QString file = QCoreApplication::applicationDirPath()+"/config.ini";
    if(QFile::exists(file))
    {
        //读取参数
        QSettings config(file,QSettings::IniFormat);
        p_video_source_ = new VideoSource(config, this);
        p_detector_ = new Detector(config,this);
    }
    else
    {
        QMessageBox::warning(this,CHINESE_CODEC("错误："),CHINESE_CODEC("找不到配置文件：config.ini"), QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
        QTimer::singleShot(0, qApp, SLOT(quit()));
    }
}

//MainWindows类的析构函数
MainWindow::~MainWindow()
{
    delete ui;
}

//resize事件
void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    int w1 = ui->openGLWidget->size().width();
    int h1 = ui->openGLWidget->size().height();
    QPoint point;

    //维持高宽比
    if(w1*9 > h1*16)
    {
        if(h1*16/9 >= ui->openGLWidget->minimumSizeHint().width())
        {
            //调整宽度
            ui->openGLWidget->resize(h1*16/9,h1);
            //调整位置
            point.setX(ui->openGLWidget->x() + (w1-(h1*16/9))/2);
            point.setY(ui->openGLWidget->y());
            ui->openGLWidget->move(point);
        }
    }
    else
    {
        if(w1*9/16 >= ui->openGLWidget->minimumSizeHint().height())
        {
            //调整宽度
            ui->openGLWidget->resize(w1,w1*9/16);
            //调整位置
            point.setX(ui->openGLWidget->x());
            point.setY(ui->openGLWidget->y() + (h1-(w1*9/16))/2);
            ui->openGLWidget->move(point);
        }
    }
}

//测试按钮
void MainWindow::on_pushButton_clicked()
{
    starCameraPreview();
}

//私有槽函数，开始预览
void MainWindow::starCameraPreview()
{
    //连接信号和槽
    qRegisterMetaType<FrameRawDataStruct>("FrameRawDataStruct");
    qRegisterMetaType<DetectResultStruct>("DetectResultStruct");
    //图像帧Frame发送到OpenGL窗口显示
    connect(p_video_source_,SIGNAL(frameGenerated(FrameRawDataStruct)),ui->openGLWidget,SLOT(receiveFrame(FrameRawDataStruct)));
    //图像帧Frame发送到Detector用来分析图像
    connect(p_video_source_,SIGNAL(frameGenerated(FrameRawDataStruct)),p_detector_,SLOT(receiveFrame(FrameRawDataStruct)));
    //检测结果Result发送到OpenGL窗口显示
    connect(p_detector_,SIGNAL(resultReady(DetectResultStruct)),ui->openGLWidget,SLOT(receiveDetectorResult(DetectResultStruct)),Qt::QueuedConnection);
    //摄像机模块开始取流
    p_video_source_->starCaptureVideo();

}

//私有槽函数，关闭预览
void MainWindow::stopCameraPreview()
{
    //摄像机模块停止取流
    p_video_source_->stopCaptureVideo();
    //断开信号和槽
}

//私有槽函数，开始图像识别
void MainWindow::startImageRecognition()
{
    //摄像机模块开始取流
    p_video_source_->starCaptureVideo();
}

//私有槽函数，关闭图像识别
void MainWindow::stopImageRecognition()
{

}

void MainWindow::FrameDealWith()
{

}






