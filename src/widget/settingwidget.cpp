#include "settingwidget.h"
#include "allwidget.h"
#include <QMessageBox>
#include <QDir>

SettingWidget::SettingWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(700,400);
    this->setWindowTitle("行车记录仪1.0版本");//设置头标

    QPalette palette;
    //调色板
    palette.setColor(QPalette::Background,Qt::white);
    this->setPalette(palette);

    pSettingPath = new SettingPath;

    init_control();
    set_control();
    init_connect();
}

void SettingWidget::init_control()
{
    LabelTitle = new QLabel();
    LabelVideoLocal = new QLabel();
    LabelImageLocal = new QLabel();
    LabelTimeInterval = new QLabel();
    LabelCamera = new QLabel();
    EditVideoLocal = new QLineEdit();
    EditImageLocal = new QLineEdit();
    EditTimeInterval = new QLineEdit();
    BoxCamera = new QComboBox();
    ButtonVideoLocal = new QPushButton();
    ButtonImageLocal = new QPushButton();
    ButtonEnter = new QPushButton();
    ButtonEsc = new QPushButton();
    HBoxLayout = new QHBoxLayout();
    HBoxLayout1 = new QHBoxLayout();
    HBoxLayout2 = new QHBoxLayout();
    HBoxLayout3 = new QHBoxLayout();
    HBoxLayout4 = new QHBoxLayout();
    HBoxLayout5 = new QHBoxLayout();
    VBoxLayout = new QVBoxLayout(this);   
}

void SettingWidget::set_control()
{
    QFont font;
    font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
    font.setPointSize(20);
    QFont font1;//标签控件字体
    font1.setFamily(QString::fromUtf8("\347\255\211\347\272\277"));
    font1.setPointSize(12);
    QFont font2;//编辑框控件字体
    font2.setPointSize(10);

    QString btnStyle;
    btnStyle = "QPushButton{background-color:white; font-size:15px; border: 2px groove gray; border-style: outset;}"
           "QPushButton:hover{background-color:white; color: black;}"
          "QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }";

    LabelTitle->setText("设置");
    LabelTitle->setFont(font);
    LabelVideoLocal ->setText("视频存储位置：");
    LabelVideoLocal->setFont(font1);
    LabelImageLocal ->setText("图片存储位置：");
    LabelImageLocal->setFont(font1);
    LabelTimeInterval->setText("采集间隔时间：");
    LabelTimeInterval->setFont(font1);
    LabelCamera->setText("摄像头配置：");
    LabelCamera->setMaximumWidth(110);
    LabelCamera->setFont(font1);

    QRegExpValidator *pRevalidotor = new QRegExpValidator(QRegExp("[a-zA-Z0-9/.:]{25}"), this);
    QRegExpValidator *pRevalidotor1 = new QRegExpValidator(QRegExp("[0-9]{25}"), this);
    EditVideoLocal->setFont(font2);
    EditVideoLocal->setMinimumSize(QSize(70, 30));
    EditVideoLocal->setValidator(pRevalidotor);
    EditVideoLocal->setFocusPolicy(Qt::NoFocus);
    EditImageLocal->setFont(font2);
    EditImageLocal->setMinimumSize(QSize(70, 30));
    EditImageLocal->setFocusPolicy(Qt::NoFocus);
    EditTimeInterval->setFont(font2);
    EditTimeInterval->setMinimumSize(QSize(70, 30));
    EditTimeInterval->setMaxLength(3);
    EditTimeInterval->setValidator(pRevalidotor1);
    EditTimeInterval->setPlaceholderText("最低时长60s");

    pCameraInfo = QCameraInfo::availableCameras();
    if(pCameraInfo.isEmpty()){
        qDebug() << "No Camera";
    }
    foreach (QCameraInfo info, pCameraInfo) {
        //后面的传至前面
        BoxCamera->addItem(info.description());
    }

    ButtonVideoLocal->setMinimumSize(QSize(30, 32));
    ButtonVideoLocal->setStyleSheet(btnStyle);
    ButtonVideoLocal->setText("..");
    ButtonVideoLocal->setToolTip("选择视频路径");
    ButtonImageLocal->setMinimumSize(QSize(30, 32));
    ButtonImageLocal->setStyleSheet(btnStyle);
    ButtonImageLocal->setText("..");
    ButtonImageLocal->setToolTip("选择图片路径");
    ButtonEnter->setText("确定");
    ButtonEnter->setStyleSheet(btnStyle);
    ButtonEnter->setMinimumHeight(40);
    ButtonEnter->setMaximumWidth(80);
    ButtonEsc->setText("取消");
    ButtonEsc->setStyleSheet(btnStyle);
    ButtonEsc->setMinimumHeight(40);
    ButtonEsc->setMaximumWidth(80);

    HBoxLayout->addWidget(LabelTitle);
    HBoxLayout->setContentsMargins(310,0,0,0);

    HBoxLayout1->addWidget(LabelVideoLocal);
    HBoxLayout1->addWidget(EditVideoLocal);
    HBoxLayout1->addWidget(ButtonVideoLocal);
    HBoxLayout1->setSpacing(0);
    HBoxLayout1->setContentsMargins(80,0,80,0);

    HBoxLayout2->addWidget(LabelImageLocal);
    HBoxLayout2->addWidget(EditImageLocal);
    HBoxLayout2->addWidget(ButtonImageLocal);
    HBoxLayout2->setSpacing(0);
    HBoxLayout2->setContentsMargins(80,0,80,0);

    HBoxLayout3->addWidget(LabelTimeInterval);
    HBoxLayout3->addWidget(EditTimeInterval);
    HBoxLayout3->setSpacing(0);
    HBoxLayout3->setContentsMargins(80,0,110,0);

    HBoxLayout4->addWidget(LabelCamera);
    HBoxLayout4->addWidget(BoxCamera);
    HBoxLayout4->setSpacing(0);
    HBoxLayout4->setContentsMargins(97,0,110,0);

    HBoxLayout5->addWidget(ButtonEnter);
    HBoxLayout5->addWidget(ButtonEsc);

    /*垂直布局对象*/
    VBoxLayout->addLayout(HBoxLayout);
    VBoxLayout->addLayout(HBoxLayout1);
    VBoxLayout->addLayout(HBoxLayout2);
    VBoxLayout->addLayout(HBoxLayout3);
    VBoxLayout->addLayout(HBoxLayout4);
    VBoxLayout->addLayout(HBoxLayout5);
    VBoxLayout->setSpacing(25);
    VBoxLayout->setAlignment(Qt::AlignCenter);
}

void SettingWidget::init_connect()
{
    connect(ButtonEnter,SIGNAL(clicked(bool)),this,SLOT(enter_slot()));
    connect(ButtonEsc,SIGNAL(clicked(bool)),this,SLOT(esc_slot()));
    connect(ButtonVideoLocal,SIGNAL(clicked(bool)),this,SLOT(video_local_slot()));
    connect(ButtonImageLocal,SIGNAL(clicked(bool)),this,SLOT(image_local_slot()));
}

void SettingWidget::clear_edit()
{
    EditVideoLocal->clear();
    EditImageLocal->clear();
    EditTimeInterval->clear();
}

void SettingWidget::check_path()
{   
    pSettingPath->VideoPath = EditVideoLocal->text();
    pSettingPath->ImagePath = EditImageLocal->text();
    pSettingPath->TimeInterval = EditTimeInterval->text();
    int index = BoxCamera->currentIndex();
    pSettingPath->pCameraInfo = pCameraInfo[index];
    if(pSettingPath->VideoPath.isEmpty()){
        pSettingPath->VideoPath = QString("C:/Program Files/Carcorder/usr/%1/video").arg(AllWidget::pLoginWidget->CurUser);
    }
    if(pSettingPath->ImagePath.isEmpty()){
        pSettingPath->ImagePath = QString("C:/Program Files/Carcorder/usr/%1/capture").arg(AllWidget::pLoginWidget->CurUser);
    }
    if(pSettingPath->TimeInterval.isEmpty() || pSettingPath->TimeInterval.toInt() < 60){
        pSettingPath->TimeInterval = "60";
    }
    if(pSettingPath->pCameraInfo.isNull())
    {
        QMessageBox::information(NULL,"提示","未查询到摄像头设备");
    }
    EditVideoLocal->setPlaceholderText(pSettingPath->VideoPath);
    EditImageLocal->setPlaceholderText(pSettingPath->ImagePath);
    EditTimeInterval->setPlaceholderText(pSettingPath->TimeInterval + "s");
}

void SettingWidget::showPath()
{     
    EditVideoLocal->setText(pSettingPath->VideoPath);
    EditImageLocal->setText(pSettingPath->ImagePath);
    EditTimeInterval->setText(pSettingPath->TimeInterval);
    int index = BoxCamera->currentIndex();
    pSettingPath->pCameraInfo = pCameraInfo[index];
    if(pSettingPath->VideoPath.isEmpty()){
        pSettingPath->VideoPath = QString("C:/Program Files/Carcorder/usr/%1/video").arg(AllWidget::pLoginWidget->CurUser);
    }
    if(pSettingPath->ImagePath.isEmpty()){
        pSettingPath->ImagePath = QString("C:/Program Files/Carcorder/usr/%1/capture").arg(AllWidget::pLoginWidget->CurUser);
    }
    if(pSettingPath->TimeInterval.isEmpty() || pSettingPath->TimeInterval.toInt() < 60){
        pSettingPath->TimeInterval = "60";
    }
    if(pSettingPath->pCameraInfo.isNull())
    {
        QMessageBox::information(NULL,"提示","未查询到摄像头设备");
    }
    EditVideoLocal->setPlaceholderText(pSettingPath->VideoPath);
    EditImageLocal->setPlaceholderText(pSettingPath->ImagePath);
    EditTimeInterval->setPlaceholderText(pSettingPath->TimeInterval + "s");
}

bool SettingWidget::createPath(QString filepath)
{
    QDir dir(filepath);
    if(dir.exists()) {
        return true;
    }
    else {
        bool ok = dir.mkpath(filepath);  //创建多级目录
        return ok;
    }
}

void SettingWidget::video_local_slot()
{
    QString filePath = QFileDialog::getExistingDirectory(this, "录像保存路径", "./");
    EditVideoLocal->setText(filePath);
}

void SettingWidget::image_local_slot()
{
    QString filePath = QFileDialog::getExistingDirectory(this, "照片保存路径", "./");
    EditImageLocal->setText(filePath);
}

void SettingWidget::enter_slot()
{    
    check_path();
    bool ret1 = createPath(pSettingPath->ImagePath);
    bool ret2 = createPath(pSettingPath->VideoPath);
    if(ret1 == true && ret2 == true) {
        pSqlData->updateSettingTable(AllWidget::pLoginWidget->CurUser, pSettingPath->ImagePath, pSettingPath->VideoPath, pSettingPath->TimeInterval);
        AllWidget::pCarcorderWidget->updateCamera(pSettingPath->pCameraInfo, pSettingPath->TimeInterval.toInt());
        this->close();
        AllWidget::pCarcorderWidget->initCameraSurface();
        AllWidget::pCarcorderWidget->show();
    }
    else {
        QMessageBox::information(NULL,"提示","文件路径错误 请重新设置");
        EditImageLocal->clear();
        EditVideoLocal->clear();
        EditTimeInterval->clear();
    }

}

void SettingWidget::esc_slot()
{
    int check = -1;

    check = pSqlData->checkSettingTable(AllWidget::pLoginWidget->CurUser);
    if(check == 1) {
        showPath();
        bool ret1 = createPath(pSettingPath->ImagePath);
        bool ret2 = createPath(pSettingPath->VideoPath);
        if(ret1 == true && ret2 == true) {
            AllWidget::pCarcorderWidget->updateCamera(pSettingPath->pCameraInfo, pSettingPath->TimeInterval.toInt());
            this->close();
            AllWidget::pCarcorderWidget->initCameraSurface();
            AllWidget::pCarcorderWidget->show();
        }
        else {
            QMessageBox::information(NULL,"提示","文件路径错误 请重新设置");
        }
    }
    else {
        QMessageBox::information(NULL,"提示","请设置文件路径");
    }
}
