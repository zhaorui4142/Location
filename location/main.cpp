#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    //QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);//设置所有窗口使用相同上下文

    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    //format.setVersion(3, 2);
    //format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSamples(4);                                  //设置多重采样
    //format.setSwapBehavior(QSurfaceFormat::TripleBuffer);  //三重缓冲
    //format.setSwapInterval(1);                             //开启垂直同步
    format.setSwapBehavior(QSurfaceFormat::DefaultSwapBehavior);  //系统默认缓冲
    format.setSwapInterval(0);                             //关闭垂直同步
    QSurfaceFormat::setDefaultFormat(format);

    MainWindow w;
    w.show();

    return a.exec();
}
