#ifndef PLAYVIDEOWIDGET_H
#define PLAYVIDEOWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QIcon>
#include <QImage>
#include "playlocalvideo.h"
#include "sqldata.h"

class PlayVideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayVideoWidget(QWidget *parent = nullptr);
    //QString &video_path,QString &image_path,QCameraInfo &camera_info,int time_interval
    void paintEvent(QPaintEvent *event);
    void init_control();
    void set_control();
    void init_connect();
    void setVideoName(QString &filename);
    void threadTerminate();
    void setPlayButton();
    ~PlayVideoWidget();

private:
    int i = 1;
    int mask;

    SqlData *pSqlData;

    QImage m_image;
    PlayLocalVideo *pPlayVideo;
    QString fileName;

    QLabel *LabelTitle;
    QLabel *LabelPlayVideo;
    QPushButton *ButtonBack;
    QPushButton *ButtonExport;
    QWidget *HBoxLayoutWidget;
    QHBoxLayout *pHBoxLayout;
    QPushButton *ButtonSpeedDown;
    QPushButton *ButtonSpeedUp;
    QPushButton *ButtonStart;
    QPushButton *ButtonCapture;

signals:

public slots:
    void backClick();
    void exportClick();
    void startClick();
    void downClick();
    void upClick();
    void getOneFrame_slot(QImage img);
    void clickCapture();
    void getCapture(QImage img);
};
#endif // PLAYVIDEOWIDGET_H
