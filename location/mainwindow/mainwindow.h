#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "videosource/videosource.h"
#include "glwidget/glwidget.h"
#include "detector/detector.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void starCameraPreview(void);
    void stopCameraPreview(void);
    void startImageRecognition(void);
    void stopImageRecognition(void);
    void FrameDealWith(void);
protected:
    void resizeEvent(QResizeEvent *event)  Q_DECL_OVERRIDE;
private:
    Ui::MainWindow *ui;
    VideoSource *p_video_source_;
    Detector *p_detector_;
};

#endif // MAINWINDOW_H
