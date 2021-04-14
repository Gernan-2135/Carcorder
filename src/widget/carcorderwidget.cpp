#include "carcorderwidget.h"
#include "allwidget.h"
#include <QPainter>
#include <QDateTime>
#include <QMessageBox>

CarcorderWidget::CarcorderWidget(QWidget *parent) : QWidget(parent)
{
    mask = 1;
    this->setFixedSize(750,500);
    this->setWindowTitle("行车记录仪1.0版本");//设置头标
    //调色板
    QPalette palette;
    palette.setColor(QPalette::Background,Qt::white);
    this->setPalette(palette);

    init_control();
    set_control();
    init_connect();
}

void CarcorderWidget::init_control()
{
    LabelTitle = new QLabel(this);
    ButtonHide = new QPushButton(this);
    LCDDate = new QLCDNumber(this);
    LCDTime = new QLCDNumber(this);
    GroupBox1 = new QGroupBox(this);
    VBoxLayoutWidget1 = new QWidget(GroupBox1);
    VBoxLayoutPlay = new QVBoxLayout(VBoxLayoutWidget1);
    GroupBox2 = new QGroupBox(GroupBox1);
    VBoxLayoutWidget2 = new QWidget(GroupBox2);
    VBoxLayoutButton = new QVBoxLayout(VBoxLayoutWidget2);
    ButtonCapture = new QPushButton(VBoxLayoutWidget2);
    ButtonReplay = new QPushButton(VBoxLayoutWidget2);
    ButtonImage = new QPushButton(VBoxLayoutWidget2);
    ButtonDecode = new QPushButton(VBoxLayoutWidget2);
    ButtonSetting = new QPushButton(VBoxLayoutWidget2);
    ButtonEsc = new QPushButton(VBoxLayoutWidget2);
    pOpenGLWidget = new OpenGLWidget();
    pCameraVideoSurface = new CameraVideoSurface();
    pCamera = new QCamera(this);
    pCameraImageCapture = new QCameraImageCapture(pCamera);
    Timer2 = new QTimer();
    Timer = new QTimer();
}

void CarcorderWidget::set_control()
{
    QString btnStyle;
    btnStyle = "QPushButton{background-color:white ;font-size:14px; border-radius: 10px; border: 2px groove gray; border-style: outset;}"
          "QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }";

    QFont font;
    font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
    font.setPointSize(20);

    LabelTitle->setText("行车记录仪");
    LabelTitle->setFont(font);
    LabelTitle->setGeometry(QRect(310, 10, 141, 41));

    ButtonHide->setGeometry(QRect(690, 70, 31, 25));
    ButtonHide->setStyleSheet("QPushButton{background-color:white;border: 2px groove gray; border-style: outset;}"
                              "QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }");
    ButtonHide->setFocusPolicy(Qt::NoFocus);
    ButtonHide->setText(">>");
    ButtonHide->setToolTip("隐藏菜单");

    //设置晶体管控件能显示的位数
    LCDDate->setDigitCount(10);
    //设置显示的模式为十进制
    LCDDate->setMode(QLCDNumber::Dec);
    //设置显示方式
    LCDDate->setSegmentStyle(QLCDNumber::Flat);
    LCDDate->setGeometry(QRect(30, 55, 150, 40));
    //设置晶体管控件能显示的位数
    LCDTime->setDigitCount(10);
    //设置显示的模式为十进制
    LCDTime->setMode(QLCDNumber::Dec);
    //设置显示方式
    LCDTime->setSegmentStyle(QLCDNumber::Flat);
    LCDTime->setGeometry(QRect(200, 55, 150, 40));

    /*QPalette paletet;
    paletet.setColor(QPalette::Background,QColor(255,255,255)); //设置标签控件背景颜色
    //QColor(int r, int g, int b); //三原色 红、绿、蓝
    */

    GroupBox1->setGeometry(QRect(20, 100, 711, 381));
    VBoxLayoutWidget1->setGeometry(QRect(38, 20, 635, 341));
    VBoxLayoutPlay->setContentsMargins(0, 0, 0, 0);
    GroupBox2->setGeometry(QRect(550, 30, 121, 321));
    VBoxLayoutWidget2->setGeometry(QRect(10, 10, 101, 311));
    VBoxLayoutButton->setSpacing(6);
    VBoxLayoutButton->setContentsMargins(0, 0, 0, 0);

    ButtonCapture->setMinimumSize(QSize(0, 40));
    ButtonCapture->setText("拍照");
    ButtonCapture->setStyleSheet(btnStyle);
    ButtonReplay->setMinimumSize(QSize(0, 40));
    ButtonReplay->setText("回放");
    ButtonReplay->setStyleSheet(btnStyle);
    ButtonImage->setMinimumSize(QSize(0, 40));
    ButtonImage->setText("照片");
    ButtonImage->setStyleSheet(btnStyle);
    ButtonDecode->setMinimumSize(QSize(0, 40));
    ButtonDecode->setText("转码");
    ButtonDecode->setStyleSheet(btnStyle);
    ButtonSetting->setMinimumSize(QSize(0, 40));
    ButtonSetting->setText("设置");
    ButtonSetting->setStyleSheet(btnStyle);
    ButtonEsc->setMinimumSize(QSize(0, 40));
    ButtonEsc->setText("退出");
    ButtonEsc->setStyleSheet(btnStyle);

    VBoxLayoutButton->addWidget(ButtonCapture);
    VBoxLayoutButton->addWidget(ButtonReplay);
    VBoxLayoutButton->addWidget(ButtonImage);
    VBoxLayoutButton->addWidget(ButtonDecode);
    VBoxLayoutButton->addWidget(ButtonSetting);
    VBoxLayoutButton->addWidget(ButtonEsc);

//    pCameraViewfinder = new QCameraViewfinder();
    pCamera->setViewfinder(pCameraVideoSurface);
    VBoxLayoutPlay->addWidget(pOpenGLWidget);

    //设置定时器每个多少毫秒发送一个timeout()信号
    Timer->setInterval(1000);
    //定时器启动
    Timer->start();
}

void CarcorderWidget::init_connect()
{
    connect(Timer, SIGNAL(timeout()), this, SLOT(timer_out_slot()));
    connect(ButtonHide, SIGNAL(clicked(bool)), this, SLOT(hide_slot()));
    connect(ButtonCapture, SIGNAL(clicked(bool)), this, SLOT(captureClick()));
    connect(pCameraVideoSurface, SIGNAL(showFrame(QImage)), pOpenGLWidget, SLOT(showCameraFrameSlot(QImage)));    
    connect(ButtonReplay, SIGNAL(clicked(bool)), this, SLOT(replay_slot()));
    connect(ButtonImage, SIGNAL(clicked(bool)), this, SLOT(image_slot()));
    connect(ButtonDecode, SIGNAL(clicked(bool)), this, SLOT(decode_slot()));
    connect(ButtonSetting, SIGNAL(clicked(bool)), this, SLOT(setting_slot()));
    connect(ButtonEsc, SIGNAL(clicked(bool)), this, SLOT(esc_slot()));
    connect(Timer2, SIGNAL(timeout()), pCameraVideoSurface, SLOT(cameraStopSlot()));
}

void CarcorderWidget::initCameraSurface()
{
    pCameraVideoSurface->InitEncoder();
}

void CarcorderWidget::updateCamera(QCameraInfo pCameraInfo, int time)
{
    if(!pCameraInfo.isNull()) {
        pCamera = new QCamera(pCameraInfo);
        pCameraImageCapture = new QCameraImageCapture(pCamera);
        pCamera->setViewfinder(pCameraVideoSurface);
    }
    if(time != 0) {
        Timer2->setInterval(time*1000);
    }
    pCamera->start();
    Timer2->start();
}

CarcorderWidget::~CarcorderWidget()
{

}

void CarcorderWidget::timer_out_slot()
{
    //获取系统当前时间
    QDateTime DateTime = QDateTime::currentDateTime();
    //晶体管控件上显示的内容
    LCDDate->display(DateTime.toString("yyyy-MM-dd"));
    LCDTime->display(DateTime.toString("hh:mm:ss "));
}

void CarcorderWidget::hide_slot()
{
    mask = ~mask;
    qDebug() << mask;
    if(mask != 1){
        ButtonHide->setText("<<");
        GroupBox2->hide();
        ButtonHide->setToolTip("显示菜单");
    }
    else{
        ButtonHide->setText(">>");
        GroupBox2->show();
        ButtonHide->setToolTip("隐藏菜单");
    }
}

void CarcorderWidget::capture_slot(int index, QImage image)
{
    if(i == 0) {
        qDebug() << "获取当前帧";
        QString CurDate = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
        qDebug() << CurDate;
        QString filename = QString("%1/%2.jpg").arg(AllWidget::pSettingWidget->pSettingPath->ImagePath).arg(CurDate);
        qDebug() << filename;
        image.save(filename);
        pSqlData->insert_sourcetable(
                    AllWidget::pLoginWidget->CurUser,
                    CurDate,
                    "photo",
                    AllWidget::pSettingWidget->pSettingPath->ImagePath);
        QMessageBox::information(NULL, "提示", "拍照成功");
        i = 1;
    }
}

void CarcorderWidget::captureClick()
{
    if(AllWidget::pLoginWidget->CurUser.isEmpty()){
        QMessageBox::information(NULL,"提示","请先登录账号");
        this->close();
        AllWidget::pLoginWidget->show();
    }
    else{
       pCameraImageCapture->capture();
       qDebug() << "获取信号";
       i = 0;
       connect(pCameraImageCapture, SIGNAL(imageCaptured(int,QImage)), this, SLOT(capture_slot(int,QImage)));
    }
}

void CarcorderWidget::replay_slot()
{
    if(AllWidget::pLoginWidget->CurUser.isEmpty()){
        QMessageBox::information(NULL,"提示","请先登录账号");
        this->close();
        AllWidget::pLoginWidget->show();
    }
    else{
        AllWidget::pShowVideoWidget->show_filepath(AllWidget::pSettingWidget->pSettingPath->VideoPath);
        AllWidget::pShowVideoWidget->show();
        this->close();
    }
}

void CarcorderWidget::image_slot()
{
    if(AllWidget::pLoginWidget->CurUser.isEmpty()){
        QMessageBox::information(NULL,"提示","请先登录账号");
        this->close();
        AllWidget::pLoginWidget->show();
    }
    else{        

        AllWidget::pShowImageWidget->show_filepath(AllWidget::pSettingWidget->pSettingPath->ImagePath);
        AllWidget::pShowImageWidget->show();
        this->close();
    }
}

void CarcorderWidget::decode_slot()
{
    if(AllWidget::pLoginWidget->CurUser.isEmpty()){
        QMessageBox::information(NULL,"提示","请先登录账号");
        this->close();
        AllWidget::pLoginWidget->show();
    }
    else{        
        AllWidget::pDecodeWidget->show_filepath(AllWidget::pSettingWidget->pSettingPath->VideoPath);
        AllWidget::pDecodeWidget->show();
        this->close();
    }
}

void CarcorderWidget::setting_slot()
{
    if(AllWidget::pLoginWidget->CurUser.isEmpty()){
        QMessageBox::information(NULL,"提示","请先登录账号");
        this->close();
        AllWidget::pLoginWidget->show();
    }
    else{
        pCamera->stop();
        Timer2->stop();
        AllWidget::pSettingWidget->showPath();
        pCameraVideoSurface->escEvent();
        this->close();
        AllWidget::pSettingWidget->show();
    }
}

void CarcorderWidget::esc_slot()
{
    this->close();
}
