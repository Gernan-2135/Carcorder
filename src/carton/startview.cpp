#include "startview.h"
#include "allwidget.h"

StartView::StartView()
{
    QString sql_db_name = "Carcorder.db";
    pSqlData = SqlData::get_DB(sql_db_name);

    this->resize(1000,500);
    this->setWindowTitle("行车记录仪1.0版本");//设置头标

    //this->setBackgroundBrush(QBrush(QPixmap("image/back.png")));

    //AllWidget::pStarview = this;
    AllWidget::pSettingWidget = new SettingWidget;
    AllWidget::pLoginWidget = new LoginWidget;
    AllWidget::pRegistWidget = new RegistWidget;
    AllWidget::pDecodeWidget = new DecodeWidget;
    AllWidget::pShowImageWidget = new ShowImageWidget;
    AllWidget::pShowVideoWidget = new ShowVideoWidget;
    AllWidget::pCarcorderWidget = new CarcorderWidget;


    QPalette palette;
    //调色板
    palette.setColor(QPalette::Background,Qt::white);
    this->setPalette(palette);

    this->scence = new QGraphicsScene;//设置场景
    this->scence->setSceneRect(0,0,this->width()-2,this->height()-2);//设置场景坐标 起始 长度 宽度
    this->setScene(this->scence);


    QFont font;
    font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
    font.setPointSize(20);

    QLabel *LabelTitle = new QLabel(this);
    LabelTitle->setText("LOGO");
    LabelTitle->setFont(font);
    LabelTitle->setGeometry(QRect(470, 10, 80, 21));
    QLabel *LabelName = new QLabel(this);
    LabelName->setText("郭健楠作品");
    LabelName->setFont(font);
    LabelName->setGeometry(QRect(430, 40, 160, 41));

    walker = new QWalker("image/man.png",scence);
    car = new QCar("image/car.png",scence);

    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),scence,SLOT(advance()));
    timer->start(100);

}
