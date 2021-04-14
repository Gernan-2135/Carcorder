#include "decodewidget.h"
#include "allwidget.h"
#include <QMessageBox>

DecodeWidget::DecodeWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(600,350);
    QPalette palette;
    //调色板
    palette.setColor(QPalette::Background,Qt::white);
    this->setPalette(palette);
    this->setWindowTitle("行车记录仪1.0版本");//设置头标

    init_control();
    set_control();
    init_connect();
}

void DecodeWidget::init_control()
{
    pListWidget = new QListWidget(this);
    pDateEdit = new QDateEdit(this);
    HLayoutWidget = new QWidget(this);
    HLayout = new QHBoxLayout(HLayoutWidget);
    LabelIn = new QLabel(HLayoutWidget);
    EditIn = new QLineEdit(HLayoutWidget);
    HLayoutWidget1 = new QWidget(this);
    HLayout1 = new QHBoxLayout(HLayoutWidget1);
    LabelFormat = new QLabel(HLayoutWidget1);
    BoxFormat = new QComboBox(HLayoutWidget1);
    HLayoutWidget2 = new QWidget(this);
    HLayout2 = new QHBoxLayout(HLayoutWidget2);
    EditPath = new QLineEdit(HLayoutWidget2);
    ButtonPath = new QPushButton(HLayoutWidget2);
    pProgressBar = new QProgressBar(this);
    ButtonEnter = new QPushButton(this);
    ButtonEsc = new QPushButton(this);

    pVideoDecode = new VideoDecode;
}

void DecodeWidget::set_control()
{
    QString btnStyle;
    btnStyle = "QPushButton{background-color:white ; border: 2px groove gray; border-style: outset;}"
           "QPushButton:hover{background-color:white; color: black;}"
          "QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }";

    pDateEdit->setGeometry(QRect(20, 20, 110, 22));
    pDateEdit->setDate(QDate::currentDate());

    pListWidget->setGeometry(QRect(10, 50, 581, 161));
    pListWidget->setResizeMode(QListView::Adjust);
    pListWidget->setViewMode(QListView::IconMode);
    pListWidget->setMovement(QListView::Static);
    pListWidget->setSpacing(10);
    pListWidget->setIconSize(QSize(165,165));

    HLayoutWidget1->setGeometry(QRect(20, 220, 111, 21));
    HLayout1->setSpacing(0);
    HLayout1->setContentsMargins(0, 0, 0, 0);
    LabelFormat->setText("转码格式:");
    BoxFormat->addItem("MP4");
    BoxFormat->addItem("AVI");
    BoxFormat->addItem("MOV");
    HLayout1->addWidget(LabelFormat);
    HLayout1->addWidget(BoxFormat);

    HLayoutWidget->setGeometry(QRect(20, 250, 381, 25));
    HLayout->setSpacing(6);
    HLayout->setContentsMargins(0, 0, 0, 0);
    LabelIn->setText("选择文件");
    LabelIn->setMinimumWidth(60);
    EditIn->setFocusPolicy(Qt::NoFocus);
    HLayout->addWidget(EditIn);
    HLayout->addWidget(LabelIn);

    HLayoutWidget2->setGeometry(QRect(20, 290, 381, 25));
    HLayout2->setSpacing(6);
    HLayout2->setContentsMargins(0, 0, 0, 0);
    ButtonPath->setMaximumSize(QSize(60,20));
    ButtonPath->setText("保存路径");
    ButtonPath->setStyleSheet(btnStyle);
    HLayout2->addWidget(EditPath);
    HLayout2->addWidget(ButtonPath);

    pProgressBar->setGeometry(QRect(20, 320, 411, 20));
    pProgressBar->setValue(0);

    ButtonEnter->setText("开始");
    ButtonEnter->setGeometry(QRect(480, 250, 101, 31));
    ButtonEnter->setStyleSheet(btnStyle);
    ButtonEsc->setText("返回");
    ButtonEsc->setGeometry(QRect(480, 310, 101, 31));
    ButtonEsc->setStyleSheet(btnStyle);
}

void DecodeWidget::show_filepath(const QString &filePath)
{
    VideoList.clear();                        //每次进入先清空列表
    pListWidget->clear();                   //每次进入清空listwidget窗口
    FilePath = filePath;
    QDir *dir = new QDir(FilePath);   //设置查询文件的路径
    if(!dir->exists()){                     //若该路径不存在
        qDebug() << "路径不存在";
    }
    QStringList filter;
    filter << "*.jpg";           //设置需要的文件类型
    dir->setNameFilters(filter);            //文件过滤、将不是图片文件的过滤掉
    VideoList = dir->entryList(filter);       //将filePath路径下获得的文件赋予QStringList链表
    if(VideoList.count() <= 0){               //如果链表为空
        qDebug() << "无图像";
    }
    for(int i = 0;i < VideoList.count();i++)  //循环生成QListWidgetItem,加入到QListWidget窗口中
    {
        QPixmap pixmap(FilePath + "/" + VideoList.at(i));   //设置每个链表对应的Item的图片
//        QListWidgetItem *listWidgetItem = new QListWidgetItem(QIcon(pixmap),VideoList.at(i)); //设置Item图片，Item名称
        QListWidgetItem *listWidgetItem = new QListWidgetItem(QIcon(pixmap),
                                                              QString(VideoList.at(i)).replace(QString(VideoList.at(i)).indexOf(".jpg"),
                                                                                               4,".h264")); //设置Item图片，Item名称
        listWidgetItem->setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled);
        pListWidget->addItem(listWidgetItem);   //Item加入ListWidget窗口中
    }
}

void DecodeWidget::init_connect()
{
    connect(ButtonEnter, SIGNAL(clicked(bool)), this, SLOT(enterSlot()));
    connect(ButtonEsc, SIGNAL(clicked(bool)), this, SLOT(escSlot()));
    connect(ButtonPath, SIGNAL(clicked(bool)), this, SLOT(choosePathSlot()));
    connect(pDateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(updateSlot()));
    connect(pListWidget,
            SIGNAL(itemClicked(QListWidgetItem*)),
            this,
            SLOT(listItemClicked(QListWidgetItem *)));
    connect(pVideoDecode, SIGNAL(sig(int)), this, SLOT(rcvSig(int)));
}

DecodeWidget::~DecodeWidget()
{
    delete this;
}

void DecodeWidget::choosePathSlot()
{
    QFileDialog *FileDialog=new QFileDialog;

    FileDialog->setAcceptMode(QFileDialog::AcceptSave);
    FileDialog->setModal(QFileDialog::ExistingFile);
    FileDialog->setFileMode(QFileDialog::ExistingFile);
    FileDialog->setOption(QFileDialog::ReadOnly, true);
    FileDialog->setWindowTitle(QString("保存路径"));
    FileDialog->setDirectory(QString(""));
    FileDialog->setNameFilter(QString("*.mp4;;*.avi;;*.mov"));
    FileDialog->setDefaultSuffix(QString("mp4"));

    if (FileDialog->exec())
    {
        QString fileName=FileDialog->selectedFiles().at(0);
        EditPath->setText(fileName);
        QString format=FileDialog->selectedNameFilter();
        if(format=="*.mp4")
            BoxFormat->setCurrentIndex(FORMAT_MP4);
        else if(format=="*.avi")
            BoxFormat->setCurrentIndex(FORMAT_AVI);
        else if(format=="*.mov")
            BoxFormat->setCurrentIndex(FORMAT_MOV);
    }
}

void DecodeWidget::enterSlot()
{
    InFileName = EditIn->text();
    if(InFileName.isEmpty()) return;

    OutFileName = EditPath->text();
    if(OutFileName.isEmpty()){
        OutFileName = EditIn->text().split('/').last();
        int index = BoxFormat->currentIndex();
        switch(index)
        {
            case FORMAT_MP4: OutFileName = InFileName.split(".h264").first()+".mp4";break;
            case FORMAT_AVI: OutFileName = InFileName.split(".h264").first()+".avi";break;
            case FORMAT_MOV: OutFileName = InFileName.split(".h264").first()+".mov";break;
            default: OutFileName = InFileName.split(".h264").first()+".mp4";break;
        }
    }
    qDebug()<<"InFile:"<<InFileName;
    qDebug()<<"OutFile:"<<OutFileName;

    ButtonEnter->setEnabled(false);
    if(pVideoDecode->CreateVideoDecode(InFileName) != true){
        QMessageBox::information(NULL,"提示","视频打开失败");
        ButtonEnter->setEnabled(true);
        return;
    }
    if(pVideoDecode->checkFileData() == false) {
        QMessageBox::information(NULL,"警告","文件破损");
        ButtonEnter->setEnabled(true);
        return;
    }
    pVideoDecode->setFileName(OutFileName);
    pVideoDecode->start();
}

void DecodeWidget::updateSlot()
{
    qDebug() << "日期改变:" << pDateEdit->date().toString("yyyyMMdd");
    VideoList.clear();                        //每次进入先清空列表
    pListWidget->clear();                   //每次进入清空listwidget窗口
    QDir *dir = new QDir(FilePath);   //设置查询文件的路径
    if(!dir->exists()){                     //若该路径不存在
        qDebug() << "路径不存在";
    }
    QStringList filter;
    filter << pDateEdit->date().toString("yyyyMMdd") + "*.jpg";           //设置需要的文件类型
    dir->setNameFilters(filter);            //文件过滤、将不是图片文件的过滤掉
    VideoList = dir->entryList(filter);       //将filePath路径下获得的文件赋予QStringList链表
    if(VideoList.count() <= 0){               //如果链表为空
        qDebug() << "无图像";
    }
    for(int i = 0;i < VideoList.count();i++)  //循环生成QListWidgetItem,加入到QListWidget窗口中
    {
        QPixmap pixmap(FilePath + "/" + VideoList.at(i));   //设置每个链表对应的Item的图片
        QListWidgetItem *listWidgetItem = new QListWidgetItem(QIcon(pixmap),
                                                              QString(VideoList.at(i)).replace(QString(VideoList.at(i)).indexOf(".jpg"),
                                                                                               4,".h264")); //设置Item图片，Item名称
        pListWidget->addItem(listWidgetItem);   //Item加入ListWidget窗口中
    }
}

void DecodeWidget::escSlot()
{
    EditIn->clear();
    EditPath->clear();
    this->close();
    AllWidget::pCarcorderWidget->show();
}

void DecodeWidget::listItemClicked(QListWidgetItem *item)
{
    QString filename = QString("%1/%2").arg(FilePath).arg(item->text());
    EditIn->setText(filename);
    qDebug() << filename;
}

void DecodeWidget::rcvSig(int value)
{
    pProgressBar->setValue(value);
    if(value >= 100){
        ButtonEnter->setEnabled(true);  //解码完成后 开始按键恢复
    }
}
