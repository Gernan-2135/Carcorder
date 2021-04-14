#include "showvideowidget.h"
#include <QFileDialog>
#include <QStringList>
#include <QDebug>
#include <QMessageBox>
#include "allwidget.h"

ShowVideoWidget::ShowVideoWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(740,520);
    this->setWindowTitle("行车记录仪1.0版本");//设置头标
    //调色板
    QPalette palette;
    palette.setColor(QPalette::Background,Qt::white);
    this->setPalette(palette);
    init_control();
    set_control();
    init_connect();
}

void ShowVideoWidget::init_control()
{
    LabelTitle = new QLabel(this);
    ButtonBack = new QPushButton(this);
    pDateEdit = new QDateEdit(this);
    pListWidget = new QListWidget(this);
}

void ShowVideoWidget::set_control()
{
    QFont font;
    font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
    font.setPointSize(20);

    LabelTitle->setText("回放列表");
    LabelTitle->setFont(font);
    LabelTitle->setGeometry(QRect(320, 11, 110, 41));

    ButtonBack->setText("返回");
    ButtonBack->setStyleSheet(
                    "QPushButton{background-color:white ;font-size:15px; border: 2px groove gray; border-style: outset;}"
                   "QPushButton:hover{background-color:white; color: black;}"
                  "QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }");
    ButtonBack->setGeometry(QRect(570, 60, 141, 31));

    pDateEdit->setGeometry(QRect(30, 70, 111, 21));
    pDateEdit->setDate(QDate::currentDate());

    pListWidget->setGeometry(QRect(30, 110, 681, 381));
    pListWidget->setResizeMode(QListView::Adjust);
    pListWidget->setViewMode(QListView::IconMode);
    pListWidget->setMovement(QListView::Static);
    pListWidget->setSpacing(10);
    pListWidget->setIconSize(QSize(200,200));
}

void ShowVideoWidget::init_connect()
{
    connect(ButtonBack, SIGNAL(clicked(bool)), this, SLOT(esc_slot()));
    connect(pDateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(update_slot()));
    connect(pListWidget,
            SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this,
            SLOT(listItemClicked(QListWidgetItem *)));
}

void ShowVideoWidget::show_filepath(const QString &filePath)
{
    VideoList.clear();                        //每次进入先清空列表
    pListWidget->clear();                   //每次进入清空listwidget窗口
    FilePath = filePath;
    QDir *dir = new QDir(FilePath);   //设置查询文件的路径
    if(!dir->exists()){                     //若该路径不存在
        qDebug() << "路径不存在";
    }
    QStringList filter;
    filter << "*.mp4" << "*.avi" << "*.mov";           //设置需要的文件类型
    dir->setNameFilters(filter);            //文件过滤、将不是图片文件的过滤掉
    VideoList = dir->entryList(filter);       //将filePath路径下获得的文件赋予QStringList链表
    if(VideoList.count() <= 0){               //如果链表为空
        qDebug() << "无图像";
    }
    for(int i = 0;i < VideoList.count();i++)  //循环生成QListWidgetItem,加入到QListWidget窗口中
    {
        QString imgFile;
        if(QString(VideoList.at(i)).indexOf(".mp4") == -1) {
            if(QString(VideoList.at(i)).indexOf(".avi") == -1) {
                imgFile = FilePath + "/" + QString(VideoList.at(i)).split(".mov").first()+".jpg";   //设置每个链表对应的Item的图片
            }
            else {
                imgFile = FilePath + "/" + QString(VideoList.at(i)).split(".avi").first()+".jpg";   //设置每个链表对应的Item的图片
            }
        }
        else {
            imgFile = FilePath + "/" + QString(VideoList.at(i)).split(".mp4").first()+".jpg";   //设置每个链表对应的Item的图片
        }
        QPixmap pixmap(imgFile);   //设置每个链表对应的Item的图片
        QListWidgetItem *listWidgetItem = new QListWidgetItem(QIcon(pixmap),VideoList.at(i)); //设置Item图片，Item名称); //设置Item图片，Item名称
        listWidgetItem->setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled);
        pListWidget->addItem(listWidgetItem);   //Item加入ListWidget窗口中
    }
}

void ShowVideoWidget::setPlayButton()
{
    pPlayVideoWidget->setPlayButton();
}

ShowVideoWidget::~ShowVideoWidget()
{
    delete this;
}

void ShowVideoWidget::esc_slot()
{
    this->close();    
    AllWidget::pCarcorderWidget->show();
}

void ShowVideoWidget::update_slot()
{
    qDebug() << "日期改变:" << pDateEdit->date().toString("yyyyMMdd");
    VideoList.clear();                        //每次进入先清空列表
    pListWidget->clear();                   //每次进入清空listwidget窗口
    QDir *dir = new QDir(FilePath);   //设置查询文件的路径
    if(!dir->exists()){                     //若该路径不存在
        qDebug() << "路径不存在";
    }
    QStringList filter;
    filter << pDateEdit->date().toString("yyyyMMdd") + "*.mp4" << pDateEdit->date().toString("yyyyMMdd") + "*.avi" << pDateEdit->date().toString("yyyyMMdd") + "*.mov";           //设置需要的文件类型
    dir->setNameFilters(filter);            //文件过滤、将不是图片文件的过滤掉
    VideoList = dir->entryList(filter);       //将filePath路径下获得的文件赋予QStringList链表
    if(VideoList.count() <= 0){               //如果链表为空
        qDebug() << "无图像";
    }
    for(int i = 0;i < VideoList.count();i++)  //循环生成QListWidgetItem,加入到QListWidget窗口中
    {
        QString imgFile;
        if(QString(VideoList.at(i)).indexOf(".mp4") == -1) {
            if(QString(VideoList.at(i)).indexOf(".avi") == -1) {
                imgFile = FilePath + "/" + QString(VideoList.at(i)).split(".mov").first()+".jpg";   //设置每个链表对应的Item的图片
            }
            else {
                imgFile = FilePath + "/" + QString(VideoList.at(i)).split(".avi").first()+".jpg";   //设置每个链表对应的Item的图片
            }
        }
        else {
            imgFile = FilePath + "/" + QString(VideoList.at(i)).split(".mp4").first()+".jpg";   //设置每个链表对应的Item的图片
        }
        QPixmap pixmap(imgFile);   //设置每个链表对应的Item的图片
        QListWidgetItem *listWidgetItem = new QListWidgetItem(QIcon(pixmap),VideoList.at(i)); //设置Item图片，Item名称); //设置Item图片，Item名称
        listWidgetItem->setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled);
        pListWidget->addItem(listWidgetItem);   //Item加入ListWidget窗口中
    }
}

void ShowVideoWidget::listItemClicked(QListWidgetItem *item)
{
    pPlayVideoWidget = new PlayVideoWidget;
    QString filename = FilePath + "/" +item->text();
    pPlayVideoWidget->setVideoName(filename);
    pPlayVideoWidget->show();
}
