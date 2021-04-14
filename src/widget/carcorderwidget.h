#ifndef CARCORDERWIDGET_H
#define CARCORDERWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QLCDNumber>
#include <QTimer>
#include <QBrush>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>
#include <QImage>
#include <QCameraInfo>
#include <QCameraImageCapture>
#include <QCameraViewfinder>
#include "sqldata.h"
#include "openglwidget.h"
#include "cameravideosurface.h"

class CarcorderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CarcorderWidget(QWidget *parent = nullptr);
    void init_control();
    void set_control();
    void init_connect();
    void initCameraSurface();
    void updateCamera(QCameraInfo pCameraInfo, int time);
    ~CarcorderWidget();

signals:

private:
    int mask;
    int i = 1;

    SqlData *pSqlData;

    QCamera *pCamera;
    OpenGLWidget *pOpenGLWidget;
//    QCameraViewfinder *pCameraViewfinder;
    CameraVideoSurface *pCameraVideoSurface;
    QCameraImageCapture *pCameraImageCapture; //获取摄像头当前帧

    QLCDNumber *LCDDate;
    QLCDNumber *LCDTime;

    QTimer *Timer;
    QTimer *Timer2;

    QLabel *LabelTitle;

    QGroupBox *GroupBox1;
    QGroupBox *GroupBox2;

    QWidget *VBoxLayoutWidget1;
    QWidget *VBoxLayoutWidget2;

    QPushButton *ButtonHide;
    QPushButton *ButtonCapture;
    QPushButton *ButtonReplay;
    QPushButton *ButtonImage;
    QPushButton *ButtonDecode;
    QPushButton *ButtonSetting;
    QPushButton *ButtonEsc;

    QVBoxLayout *VBoxLayoutButton;
    QVBoxLayout *VBoxLayoutPlay;

public slots:
    void timer_out_slot();//时间跳动信号
    void hide_slot();
    void capture_slot(int index, QImage image);
    void captureClick();
    void replay_slot();
    void image_slot();
    void decode_slot();
    void setting_slot();
    void esc_slot();

};

#endif // CARCORDERWIDGET_H
