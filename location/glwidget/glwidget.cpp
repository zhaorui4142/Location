//头文件包含区
#include "glwidget.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>
#include <QCoreApplication>
#include <QTimer>
#include <QtGui>
#include <QThread>
#include <QDebug>

//宏定义区
#define ATTRIB_VERTEX 0
#define ATTRIB_TEXTURE 1
#define BUFFER_OFFSET(offset) ((GLvoid *) (reinterpret_cast<void *>(offset)))
#define GAUESS_BLUR_RADIUS 11

//自定义类型
enum stateSwitcher{STATE_ERROR,
                  STATE_PREVIEW,
                  STATE_SCANING,
                  STATE_LOCK_ON};


//=============================================================================================//
//==============================以下为：GlWidget类的实现==========================================//


//GlWidget类构造函数
GlWidget::GlWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      program_texture(0),
      program_yuv(0),
      program_frame_scan(0),
      scanline_coord_x(-1.0f),
      state(STATE_ERROR)
{

    //设置定时器，60fps
    timer = new QTimer(this);
    timer->setTimerType(Qt::PreciseTimer);
    timer->setSingleShot(false);

    //连接信号和槽
    connect(timer,&QTimer::timeout,this,&GlWidget::refreshFrame);
}

//GlWidget类析构函数
GlWidget::~GlWidget()
{
    cleanup();

}

//OpenGl重载函数：初始化
void GlWidget::initializeGL()
{
    const int numVertices = 16;
    //对象销毁后释放opengl资源
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GlWidget::cleanup);

    //初始化OpenGL功能
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1.0);

    //设定opengl function指针
    glFunctions = context()->functions();

    //初始化texture
    textures_no_video = new QOpenGLTexture(QImage(":/novideo.png"));
    textures_no_video->setMagnificationFilter(QOpenGLTexture::Linear);
    textures_no_video->setMinificationFilter(QOpenGLTexture::Linear);
    textures_no_video->setWrapMode(QOpenGLTexture::ClampToBorder);
    texture_y         = new QOpenGLTexture(QOpenGLTexture::Target2D);
    texture_u         = new QOpenGLTexture(QOpenGLTexture::Target2D);
    texture_v         = new QOpenGLTexture(QOpenGLTexture::Target2D);
    texture_edges     = new QOpenGLTexture(QOpenGLTexture::Target2D);

    //初始化顶点数组对象（VAO）
    m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    //装配缓存对象（VBO）
    static const GLfloat vertices[numVertices] = {
        //vertexVertices顶点坐标
        -1.0f, -1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f,  1.0f,
        //textureVertices纹理坐标     
        0.0f,  1.0f,
        1.0f,  1.0f,
        0.0f,  0.0f,
        1.0f,  0.0f
    };
    m_vbo.create();                                            //glGenBuffers
    m_vbo.bind();                                              //glBindBuffer
    m_vbo.allocate(vertices, numVertices * sizeof(GLfloat));   //blBUfferData

    glEnableVertexAttribArray(ATTRIB_VERTEX);
    glEnableVertexAttribArray(ATTRIB_TEXTURE);
    glVertexAttribPointer(ATTRIB_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glVertexAttribPointer(ATTRIB_TEXTURE, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(8 * sizeof(GLfloat)));
    m_vbo.release();

    //创建program对象,(创建、指定源码、编译shader)
    program_texture = new QOpenGLShaderProgram;
    program_texture->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/textureDisplay.vsh");
    program_texture->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/textureDisplay.fsh");
    program_texture->bindAttributeLocation("vertexIn", ATTRIB_VERTEX);
    program_texture->bindAttributeLocation("textureIn", ATTRIB_TEXTURE);
    program_texture->link();

    program_yuv = new QOpenGLShaderProgram;
    program_yuv->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/yv12Display.vsh");
    program_yuv->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/yv12Display.fsh");
    program_yuv->bindAttributeLocation("vertexIn", ATTRIB_VERTEX);
    program_yuv->bindAttributeLocation("textureIn", ATTRIB_TEXTURE);


    program_frame_scan = new QOpenGLShaderProgram;
    program_frame_scan->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/frameDisplayWithScanline.vsh");
    program_frame_scan->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/frameDisplayWithScanline.fsh");
    program_frame_scan->bindAttributeLocation("vertexIn", ATTRIB_VERTEX);
    program_frame_scan->bindAttributeLocation("textureIn", ATTRIB_TEXTURE);
    program_frame_scan->link();

    program_gaussblur_h = new QOpenGLShaderProgram;
    program_gaussblur_h->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/gaussBlur.vsh");
    program_gaussblur_h->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/gaussBlurh.fsh");
    program_gaussblur_h->bindAttributeLocation("vertexIn", ATTRIB_VERTEX);
    program_gaussblur_h->bindAttributeLocation("textureIn", ATTRIB_TEXTURE);
    program_gaussblur_h->link();

    program_gaussblur_v = new QOpenGLShaderProgram;
    program_gaussblur_v->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/gaussBlur.vsh");
    program_gaussblur_v->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/gaussBlurv.fsh");
    program_gaussblur_v->bindAttributeLocation("vertexIn", ATTRIB_VERTEX);
    program_gaussblur_v->bindAttributeLocation("textureIn", ATTRIB_TEXTURE);
    program_gaussblur_v->link();

    //开始定时刷新图像
    timer->start(16);
}

//OpenGl重载函数：绘图
void GlWidget::paintGL()
{
    //qDebug()<<"from last action:"<<getIntervalMillisecond();


    //清除屏幕背景
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    switch(state)
    {
    case STATE_ERROR:
        paintErorr();
        break;
    case STATE_PREVIEW:
        paintFrame();
        break;
    case STATE_SCANING:
        paintFrameWithScanline();
        //GLuint tex_id_gauss = GetGaussBluredTextureID();
        //DrawBlend(tex_id_gauss);
        break;
    }

    //glFinish();

    //qDebug()<<"end paint,consume time:"<<getIntervalMillisecond()<<"\n";
}

//OpenGl重载函数：改变窗口大小
void GlWidget::resizeGL(int w, int h)
{
    Q_UNUSED(w);
    Q_UNUSED(h);
}

//私有函数，清除图像
void GlWidget::cleanup()
{
    makeCurrent();
    m_vbo.destroy();
    program_texture->deleteLater();;
    textures_no_video ->destroy();
    texture_y->destroy();
    texture_u->destroy();
    texture_v->destroy();
    texture_edges->destroy();
    delete textures_no_video;
    delete texture_y;
    delete texture_u;
    delete texture_v;
    delete texture_edges;
    program_yuv->deleteLater();;
    program_frame_scan->deleteLater();;
    program_gaussblur_h->deleteLater();;
    program_gaussblur_v->deleteLater();
    doneCurrent();
}

//公有槽函数，接收新的图像帧，并将图像数据转换为贴图
void GlWidget::receiveFrame(FrameRawDataStruct frame)
{

    //qDebug()<<"from last action:"<<getIntervalMillisecond();

    //计算各个分量的指针
    // yv12数据格式，其中Y分量长度为width * height, U和V分量长度都为width * height / 4
    int nYLen = frame.imgWidth * frame.imgHeigh;
    char* yData = frame.imgData.data();
    char* vData = &yData[nYLen];
    char* uData = &vData[nYLen>>2];
    if(!uData || !vData) return;
    //glFuncs->glFinish();
    makeCurrent();
    //生成纹理，绑定纹理，上传纹理数据
    //y
    if(!texture_y->isStorageAllocated())
    {
        texture_y->setMagnificationFilter(QOpenGLTexture::Linear);
        texture_y->setMinificationFilter(QOpenGLTexture::Linear);
        texture_y->setWrapMode(QOpenGLTexture::ClampToBorder);
        texture_y->setFormat(QOpenGLTexture::R8_UNorm);
        texture_y->setSize(frame.imgWidth, frame.imgHeigh);
        texture_y->allocateStorage();
    }
    texture_y->setData(QOpenGLTexture::Red, QOpenGLTexture::UInt8, reinterpret_cast<void *>(yData));

    //u
    if(!texture_u->isStorageAllocated())
    {
        texture_u->setMagnificationFilter(QOpenGLTexture::Linear);
        texture_u->setMinificationFilter(QOpenGLTexture::Linear);
        texture_u->setWrapMode(QOpenGLTexture::ClampToBorder);
        texture_u->setFormat(QOpenGLTexture::R8_UNorm);
        texture_u->setSize(frame.imgWidth/2, frame.imgHeigh/2);
        texture_u->allocateStorage();
    }
    texture_u->setData(QOpenGLTexture::Red, QOpenGLTexture::UInt8, reinterpret_cast<void *>(uData));
    //v
    if(!texture_v->isStorageAllocated())
    {
        texture_v->setMagnificationFilter(QOpenGLTexture::Linear);
        texture_v->setMinificationFilter(QOpenGLTexture::Linear);
        texture_v->setWrapMode(QOpenGLTexture::ClampToBorder);
        texture_v->setFormat(QOpenGLTexture::R8_UNorm);
        texture_v->setSize(frame.imgWidth/2, frame.imgHeigh/2);
        texture_v->allocateStorage();
    }
    texture_v->setData(QOpenGLTexture::Red, QOpenGLTexture::UInt8, reinterpret_cast<void *>(vData));
    doneCurrent();
    //glFunctions->glFinish();

    //计时函数
    //qDebug()<<"end receive Frame,consume time:"<<getIntervalMillisecond()<<'\n';

    //设定工作状态-显示图像帧
    if(state == STATE_ERROR)
        state = STATE_PREVIEW;
}

//公有槽函数，接收检测结果，并将轮廓转换为贴图
void GlWidget::receiveDetectorResult(DetectResultStruct result)
{


    //计时函数
    //qDebug()<<"from last action:"<<getIntervalMillisecond();
    makeCurrent();
    //生成纹理，绑定纹理，上传纹理数据
    if(!texture_edges->isStorageAllocated())
    {
        texture_edges->create();
        texture_edges->setMagnificationFilter(QOpenGLTexture::Linear);
        texture_edges->setMinificationFilter(QOpenGLTexture::Linear);
        texture_edges->setWrapMode(QOpenGLTexture::ClampToBorder);
        texture_edges->setFormat(QOpenGLTexture::R8_UNorm);
        texture_edges->setSize(result.detectImg_contour.width(), result.detectImg_contour.height());
        texture_edges->allocateStorage();
    }
    texture_edges->setData(QOpenGLTexture::Red, QOpenGLTexture::UInt8, reinterpret_cast<void *>(result.detectImg_contour.bits()));
    //计时函数
    //qDebug()<<"end receive edges,consume time:"<<getIntervalMillisecond()<<'\n';

    //对轮廓图进行高斯模糊，注意释放资源
    //if(glFunctions->glIsTexture(texture_edges_blued))
        //glFunctions->glDeleteTextures(1,&texture_edges_blued);
    //gaussBlurEdgeTexture();
    doneCurrent();

    //设定工作状态-显示图像帧
    if(state == STATE_PREVIEW)
        state = STATE_SCANING;
}

//公有槽函数，显示错误标志图片
void GlWidget::showErrorPicture()
{
    state = STATE_ERROR;
}


//绘制图像帧
void GlWidget::paintFrame()
{
    //绑定vao
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    //绑定program
    program_yuv->bind();//相当于glUseProgram
    program_yuv->setUniformValue("tex_y", 1);
    program_yuv->setUniformValue("tex_u", 2);
    program_yuv->setUniformValue("tex_v", 3);

    //绑定贴图
    texture_y->bind(1);
    texture_u->bind(2);
    texture_v->bind(3);

    //绘制图像
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    program_yuv->release();
}

//绘制图像帧，带扫描线
void GlWidget::paintFrameWithScanline(void)
{
    //绑定vao
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    //绑定program 
    program_frame_scan->bind();//相当于glUseProgram
    program_frame_scan->setUniformValue("tex_y", 1);
    program_frame_scan->setUniformValue("tex_u", 2);
    program_frame_scan->setUniformValue("tex_v", 3);
    program_frame_scan->setUniformValue("tex_edge", 4);
    program_frame_scan->setUniformValue("scanline_x", scanline_coord_x);

    //绑定贴图
    texture_y->bind(1);
    texture_u->bind(2);
    texture_v->bind(3);
    texture_edges->bind(4);
    //glFunctions->glActiveTexture(GL_TEXTURE4);
    //glFunctions->glBindTexture(GL_TEXTURE_2D, texture_edges_blued);

    //绘制图像
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    program_frame_scan->release();
}

//私有函数，对轮廓贴图进行高斯模糊
void GlWidget::gaussBlurEdgeTexture(void)
{
    //计算得到一张和当前窗口一样大的贴图，而不是全尺寸的，节省渲染资源
    int fbo_width = width();
    int fbo_heigh = height();

    //创建FBO
    QOpenGLFramebufferObject *fbo = new QOpenGLFramebufferObject(fbo_width, fbo_heigh, QOpenGLFramebufferObject::CombinedDepthStencil);

    //绑定vao
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    //高斯模糊(x轴)
    fbo->bind();
    texture_edges->bind(1);
    int radius = 2;
    program_gaussblur_h->bind();
    program_gaussblur_h->setUniformValue("tex", 1);
    program_gaussblur_h->setUniformValue("radius", radius);
    program_gaussblur_h->setUniformValue("pixelWidth", fbo_width);
    glFunctions->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    program_gaussblur_h->release();

    //高斯模糊(y轴)
    GLuint tex_gauss_x = fbo->takeTexture();
    fbo->bind();
    glFunctions->glActiveTexture(GL_TEXTURE1);
    glFunctions->glBindTexture(GL_TEXTURE_2D, tex_gauss_x);
    program_gaussblur_v->bind();
    program_gaussblur_v->setUniformValue("tex", 1);
    program_gaussblur_v->setUniformValue("radius", radius);
    program_gaussblur_v->setUniformValue("pixelHeight", fbo_heigh);
    glFunctions->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    program_gaussblur_v->release();
    glFunctions->glDeleteTextures(1,&tex_gauss_x);
/**/
    //返回纹理id
    texture_edges_blued = fbo->takeTexture();
    fbo->release();
    delete fbo;

    //切换回默认的framebuffer来渲染
    QOpenGLFramebufferObject::bindDefault();

}

//私有函数，计算耗时
qreal GlWidget::getIntervalMillisecond()
{
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t2);
    qreal retval;

    retval = (t2.QuadPart - t1.QuadPart)*1000.0/tc.QuadPart;
    t1 = t2;
    return retval;
}

//私有槽函数，更新图像，由定时器控制
void GlWidget::refreshFrame()
{
    //scanline_coord_x不断地从0.0增加到+3.0
    if(scanline_coord_x < 3.0)
        scanline_coord_x += 0.015f;
    else
        scanline_coord_x = 0.0;

    this->update();
}


//绘制错误标志
void GlWidget::paintErorr()
{
    //绑定vao
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    //绑定program
    program_texture->bind();//相当于glUseProgram
    program_texture->setUniformValue("texture", 0);

    //绑定贴图
    textures_no_video->bind();

    //绘制图像
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    program_texture->release();
}




//鼠标事件
void GlWidget::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();
    qDebug()<<"mouse pos:"<<m_lastPos;
}

//鼠标事件
void GlWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - m_lastPos.x();
    int dy = event->y() - m_lastPos.y();

    if (event->buttons() & Qt::LeftButton) {

    } else if (event->buttons() & Qt::RightButton) {

    }
    m_lastPos = event->pos();

    qDebug()<<"mouse move:"<<dx<<dy<<m_lastPos;
}

//推荐最小尺寸
QSize GlWidget::minimumSizeHint() const
{
    return QSize(80, 45);
}

//推荐尺寸
QSize GlWidget::sizeHint() const
{
    return QSize(640, 360);
}














