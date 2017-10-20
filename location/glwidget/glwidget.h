#ifndef GLWIDGET_H
#define GLWIDGET_H
//头文件包含区
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include "struct-data.h"

//前置声明
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
QT_FORWARD_DECLARE_CLASS(QOpenGLFramebufferObject)
QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)
QT_FORWARD_DECLARE_CLASS(QTimer)
QT_FORWARD_DECLARE_CLASS(QThread)
//struct FrameRawDataStruct;
enum stateSwitcher;


//类声明区

//显示图像的widget
class GlWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit GlWidget(QWidget *parent = 0);
    ~GlWidget();

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

public slots:
    void cleanup();
    void receiveFrame(FrameRawDataStruct frame);//接收新的图像帧
    void receiveDetectorResult(DetectResultStruct result);//接收新的检测结果
    void showErrorPicture(void);//显示错误提示

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    //void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

signals:


private slots:
    void refreshFrame(void);

private:
    void paintFrame(void);
    void paintErorr(void);//显示错误图像
    void paintFrameWithScanline(void);//显示帧图像，带扫描线

    void gaussBlurEdgeTexture(void);//高斯模糊

    qreal getIntervalMillisecond(void);//计算间隔时间
    qreal getAndResetIntervalMillisecond(void);//计算并复位间隔时间

    stateSwitcher state;
    QPoint m_lastPos;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;
    QOpenGLShaderProgram *program_texture;
    QOpenGLShaderProgram *program_yuv;
    QOpenGLShaderProgram *program_frame_scan;
    QOpenGLShaderProgram *program_gaussblur_h, *program_gaussblur_v;
    QOpenGLTexture *textures_no_video;
    QOpenGLTexture *texture_y, *texture_u, *texture_v;
    QOpenGLTexture *texture_edges;
    GLuint texture_edges_blued;
    QTimer *timer;
    float scanline_coord_x;
    QOpenGLFunctions *glFunctions;

    LARGE_INTEGER t1,t2,tc;
};





#endif // GLWIDGET_H
