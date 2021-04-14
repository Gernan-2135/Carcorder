#include "playvideowidget.h"
#include "allwidget.h"
#include <QDebug>
#include <QDateTime>
#include <QMessageBox>
#include <QFile>

PlayVideoWidget::PlayVideoWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(750,540);
    this->setWindowTitle("行车记录仪1.0版本");//设置头标
    //调色板
    QPalette palette;
    palette.setColor(QPalette::Background,Qt::white);
    this->setPalette(palette);

    mask = 1;

    init_control();
    set_control();
    init_connect();
}

void PlayVideoWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(m_image.isNull())
    {
        return ;
    }
    if(m_image.size().width()<=0) return;
    QImage img=m_image.scaled(this->size(),Qt::KeepAspectRatio);
    painter.drawImage(QRect(20, 70, 711, 441), img);
}


void PlayVideoWidget::init_control()
{
    pPlayVideo = new PlayLocalVideo;
    LabelTitle = new QLabel(this);
    LabelPlayVideo = new QLabel(this);
    ButtonBack = new QPushButton(this);
    ButtonExport = new QPushButton(this);
    HBoxLayoutWidget = new QWidget(this);
    pHBoxLayout = new QHBoxLayout(HBoxLayoutWidget);
    ButtonSpeedDown = new QPushButton(HBoxLayoutWidget);
    ButtonSpeedUp = new QPushButton(HBoxLayoutWidget);
    ButtonStart = new QPushButton(HBoxLayoutWidget);
    ButtonCapture = new QPushButton(this);
}

void PlayVideoWidget::set_control()
{
    QFont font;
    font.setPointSize(20);

    LabelTitle->setText("录屏播放");
    LabelTitle->setGeometry(QRect(320, 20, 111, 31));
    LabelTitle->setFont(font);
    LabelPlayVideo->setGeometry(QRect(20, 70, 711, 451));
    LabelPlayVideo->setAutoFillBackground(true);
    LabelPlayVideo->setPalette(QColor(0,0,0));

    ButtonBack->setText("返回");
    ButtonBack->setGeometry(QRect(40, 20, 111, 31));
    ButtonBack->setStyleSheet(
                    "QPushButton{background-color:white ;font-size:15px; border: 2px groove gray; border-style: outset;}"
                   "QPushButton:hover{background-color:white; color: black;}"
                  "QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }");
    ButtonExport->setText("导出");
    ButtonExport->setGeometry(QRect(600, 20, 111, 31));
    ButtonExport->setStyleSheet(
                "QPushButton{background-color:white ;font-size:15px; border: 2px groove gray; border-style: outset;}"
               "QPushButton:hover{background-color:white; color: black;}"
              "QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }");

    HBoxLayoutWidget->setGeometry(QRect(300, 450, 161, 52));
    pHBoxLayout->setSpacing(0);
    pHBoxLayout->setContentsMargins(0, 0, 0, 0);
    ButtonStart->setIcon(QIcon("image/stop_button.png"));
    ButtonStart->setMinimumSize(QSize(50, 52));
    ButtonStart->setIconSize(QSize(50, 52));
    ButtonStart->setStyleSheet("QPushButton{background-color:rgba(0,0,0,0); border:none;}");
    ButtonStart->setFocusPolicy(Qt::NoFocus);
    ButtonStart->setToolTip("暂停");
    ButtonSpeedDown->setIcon(QIcon("image/down_button.png"));
    ButtonSpeedDown->setMinimumSize(QSize(50, 52));
    ButtonSpeedDown->setIconSize(QSize(50, 52));
    ButtonSpeedDown->setStyleSheet("QPushButton{background-color:rgba(0,0,0,0); border:none;}");
    ButtonSpeedDown->setFocusPolicy(Qt::NoFocus);
    ButtonSpeedDown->setToolTip("减速");
    ButtonSpeedUp->setIcon(QIcon("image/up_button.png"));
    ButtonSpeedUp->setMinimumSize(QSize(50, 52));
    ButtonSpeedUp->setIconSize(QSize(50, 52));
    ButtonSpeedUp->setStyleSheet("QPushButton{background-color:rgba(0,0,0,0); border:none;}");
    ButtonSpeedUp->setFocusPolicy(Qt::NoFocus);
    ButtonSpeedUp->setToolTip("加速");
    pHBoxLayout->addWidget(ButtonSpeedDown);
    pHBoxLayout->addWidget(ButtonStart);
    pHBoxLayout->addWidget(ButtonSpeedUp);

    ButtonCapture->setGeometry(QRect(640, 90, 71, 71));
    ButtonCapture->setToolTip("截图");
    ButtonCapture->setIcon(QIcon("image/capture.png"));
    ButtonCapture->setIconSize(QSize(71, 71));
    ButtonCapture->setFlat(true);
    //ButtonCapture->setStyleSheet("background-color:rgba(0,0,0,0)");
    //ButtonHidePwd->setFocusPolicy(Qt::NoFocus);
}

void PlayVideoWidget::init_connect()
{
    connect(ButtonBack, SIGNAL(clicked(bool)), this, SLOT(backClick()));
    connect(ButtonExport, SIGNAL(clicked(bool)), this, SLOT(exportClick()));
    connect(ButtonSpeedDown, SIGNAL(clicked(bool)), this, SLOT(downClick()));
    connect(ButtonStart, SIGNAL(clicked(bool)), pPlayVideo, SLOT(psSlot()));
    connect(ButtonStart, SIGNAL(clicked(bool)), this, SLOT(startClick()));
    connect(ButtonCapture, SIGNAL(clicked(bool)), this, SLOT(clickCapture()));
    connect(ButtonSpeedUp, SIGNAL(clicked(bool)), this, SLOT(upClick()));
    connect(pPlayVideo, SIGNAL(sigGetOneFrame(QImage)), this, SLOT(getOneFrame_slot(QImage)));
}

void PlayVideoWidget::setVideoName(QString &filename)
{   
    if(pPlayVideo->CreatePlayState(filename) == false) {
        QMessageBox::information(NULL,"警告","文件损坏");
        return;
    }
    fileName = filename;
    LabelPlayVideo->hide();
    pPlayVideo->start();
}

void PlayVideoWidget::threadTerminate()
{
    pPlayVideo->terminate();
}

void PlayVideoWidget::setPlayButton()
{
    ButtonStart->setIcon(QIcon("image/end_button.png"));
}

PlayVideoWidget::~PlayVideoWidget()
{
    delete this;
}

void PlayVideoWidget::backClick()
{
    pPlayVideo->terminate();
    AllWidget::pShowVideoWidget->show_filepath(AllWidget::pSettingWidget->pSettingPath->VideoPath);
    AllWidget::pShowVideoWidget->show();
    this->close();
}

void PlayVideoWidget::exportClick()
{
    qDebug() << "export";
    QString path;
//    path = QDir::currentPath() + fileName;
    path = fileName;
    QString filename = QFileDialog::getSaveFileName(this, tr("另存为路径"), path, tr("Video Files (*.mp4)"));
    if(filename.isNull()) {
        return;
    }
    else {
        //一些处理工作，复制
        QFile::copy(path , filename);
        QMessageBox::information(NULL, "提示", "导出成功");
    }
}

void PlayVideoWidget::startClick()
{
    mask = ~mask;
    if(mask != 1) {
        ButtonStart->setIcon(QIcon("image/play_button.png"));
        ButtonStart->setToolTip("播放");
    }
    else {
        ButtonStart->setIcon(QIcon("image/stop_button.png"));
        ButtonStart->setToolTip("暂停");
    }
}

void PlayVideoWidget::downClick()
{
    pPlayVideo->downSpeed();
}

void PlayVideoWidget::upClick()
{
    pPlayVideo->upSpeed();
}



void PlayVideoWidget::getOneFrame_slot(QImage img)
{
    qDebug()<<"收到一帧数据" ;
    m_image=img;
    update();
}

void PlayVideoWidget::clickCapture()
{
    i = 0;
    connect(pPlayVideo, SIGNAL(sigGetOneFrame(QImage)), this, SLOT(getCapture(QImage)));
}

void PlayVideoWidget::getCapture(QImage img)
{
    if(i == 0) {
        qDebug() << "获取当前帧";
        QString CurDate = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
        qDebug() << CurDate;
        QString filename = QString("%1/%2.jpg").arg(AllWidget::pSettingWidget->pSettingPath->ImagePath).arg(CurDate);
        qDebug() << filename;
        img.save(filename);
        pSqlData->insert_sourcetable(
                    AllWidget::pLoginWidget->CurUser,
                    CurDate,
                    "capture",
                    AllWidget::pSettingWidget->pSettingPath->ImagePath);
        i = 1;
    }

}

