#ifndef GLWIDGET_H
#define GLWIDGET_H
//ͷ�ļ�������
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include "struct-data.h"

//ǰ������
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
QT_FORWARD_DECLARE_CLASS(QOpenGLFramebufferObject)
QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)
QT_FORWARD_DECLARE_CLASS(QTimer)
QT_FORWARD_DECLARE_CLASS(QThread)
//struct FrameRawDataStruct;
enum stateSwitcher;


//��������

//��ʾͼ���widget
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
    void receiveFrame(FrameRawDataStruct frame);//�����µ�ͼ��֡
    void receiveDetectorResult(DetectResultStruct result);//�����µļ����
    void showErrorPicture(void);//��ʾ������ʾ

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
    void paintErorr(void);//��ʾ����ͼ��
    void paintFrameWithScanline(void);//��ʾ֡ͼ�񣬴�ɨ����

    void gaussBlurEdgeTexture(void);//��˹ģ��

    qreal getIntervalMillisecond(void);//������ʱ��
    qreal getAndResetIntervalMillisecond(void);//���㲢��λ���ʱ��

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
