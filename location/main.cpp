#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    //QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);//�������д���ʹ����ͬ������

    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    //format.setVersion(3, 2);
    //format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSamples(4);                                  //���ö��ز���
    //format.setSwapBehavior(QSurfaceFormat::TripleBuffer);  //���ػ���
    //format.setSwapInterval(1);                             //������ֱͬ��
    format.setSwapBehavior(QSurfaceFormat::DefaultSwapBehavior);  //ϵͳĬ�ϻ���
    format.setSwapInterval(0);                             //�رմ�ֱͬ��
    QSurfaceFormat::setDefaultFormat(format);

    MainWindow w;
    w.show();

    return a.exec();
}
