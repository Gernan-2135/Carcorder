#include "loginwidget.h"
#include "allwidget.h"
#include <QRegExpValidator>
#include <QMessageBox>
#include <QPainter>
#include <QTime>

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget   (parent)
{
//    QString sql_db_name = "Carcorder.db";
//    pSqlData = SqlData::get_DB(sql_db_name);

    this->setFixedSize(400,300);
    this->setWindowTitle("行车记录仪1.0版本");//设置头标

    QPalette palette;
    //调色板
    palette.setColor(QPalette::Background,Qt::white);
    this->setPalette(palette);
    mask = 1;

    init_control();
    init_connect();
}

void LoginWidget::init_control()
{
    QFont font;
    font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
    font.setPointSize(20);
    QFont font1;//标签控件字体
    font1.setFamily(QString::fromUtf8("\347\255\211\347\272\277"));
    font1.setPointSize(10);
    QFont font2;//编辑框控件字体
    font2.setPointSize(11);

    QString btnStyle;
    btnStyle = "QPushButton{background-color:white ;font-size:15px; border: 2px groove gray; border-style: outset;}"
           "QPushButton:hover{background-color:white; color: black;}"
          "QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }";

    /*QPalette paletet;
    paletet.setColor(QPalette::Background,QColor(0,255,255)); //设置标题背景颜色
    LabelTitle->setAutoFillBackground(true);
    LabelTitle->setPalette(paletet);*/
    LabelTitle = new QLabel();
    LabelTitle->setText("登录");
    LabelTitle->setFont(font);
    LabelTitle->setMinimumWidth(60);
    LabelID = new QLabel();
    LabelID->setText("账号：");
    LabelID->setFont(font1);
    LabelID->setMinimumWidth(45);
    LabelPWD = new QLabel();
    LabelPWD->setText("密码： ");
    LabelPWD->setFont(font1);
    LabelPWD->setMinimumWidth(49);
    LabelCapt = new QLabel();
    LabelCapt->setText("验证码：");
    LabelCapt->setMinimumWidth(45);
    LabelCapt->setFont(font1);
    //LabelCapt->setMaximumWidth(50);

    QRegExpValidator *pRevalidotor = new QRegExpValidator(QRegExp("[a-zA-Z0-9]{25}"), this);
    QRegExpValidator *pRevalidotor1 = new QRegExpValidator(QRegExp("[0-9]{25}"), this);

    EditID = new QLineEdit();
    EditID->setMinimumSize(QSize(100, 30));
    EditID->setMaxLength(16);
    EditID->setValidator(pRevalidotor1);
    EditID->setPlaceholderText(QStringLiteral("请输入账号"));
    EditID->setFont(font2);
    EditID->setEchoMode(QLineEdit::Normal);
    EditPWD = new QLineEdit();
    EditPWD->setMinimumSize(QSize(70, 30));
    EditPWD->setMaxLength(16);
    EditPWD->setValidator(pRevalidotor);
    EditPWD->setPlaceholderText(QStringLiteral("请输入密码"));
    EditPWD->setEchoMode(QLineEdit::Password);
    EditPWD->setFont(font2);
    EditCapt = new QLineEdit();
    EditCapt->setMinimumHeight(30);
    EditCapt->setMaximumWidth(80);
    EditCapt->setMaxLength(4);
    EditCapt->setFont(font2);
    EditCapt->setValidator(pRevalidotor);

    ButtonLogin = new QPushButton();
    ButtonLogin->setText("登录");
    ButtonLogin->setMinimumHeight(40);
    ButtonLogin->setMaximumWidth(80);
    ButtonLogin->setStyleSheet(btnStyle);

    ButtonRegist = new QPushButton();
    ButtonRegist->setText("注册");
    ButtonRegist->setMinimumHeight(40);
    ButtonRegist->setMaximumWidth(80);
    ButtonRegist->setFont(font2);
    ButtonRegist->setStyleSheet(btnStyle);


    ButtonHidePwd = new QPushButton();
    ButtonHidePwd->setMaximumSize(QSize(30, 32));
    ButtonHidePwd->setIcon(QIcon("image/eye.png"));
    ButtonHidePwd->setIconSize(QSize(30,32));
    ButtonHidePwd->setStyleSheet("background-color:rgba(0,0,0,0)");
    ButtonHidePwd->setFocusPolicy(Qt::NoFocus);
    ButtonHidePwd->setToolTip("显示密码");

    HideBox = new QHBoxLayout();
    HideBox->addWidget(ButtonHidePwd);
    HideBox->setSpacing(0);
    HideBox->setContentsMargins(145,0,0,0);
    EditPWD->setLayout(HideBox);

    HBoxLayout = new QHBoxLayout();
    HBoxLayout->addWidget(LabelTitle);
    HBoxLayout->setContentsMargins(170,0,150,0);

    HBoxLayout1 = new QHBoxLayout();
    HBoxLayout1->addWidget(LabelID);
    HBoxLayout1->addWidget(EditID);
    HBoxLayout1->setSpacing(4);
    HBoxLayout1->setContentsMargins(80,0,80,0);

    HBoxLayout2 = new QHBoxLayout();
    HBoxLayout2->addWidget(LabelPWD);
    HBoxLayout2->addWidget(EditPWD);
    //HBoxLayout2->addWidget(ButtonHidePwd);
    HBoxLayout2->setSpacing(0);
    HBoxLayout2->setContentsMargins(80,0,80,0);

    HBoxLayout3 = new QHBoxLayout();
    HBoxLayout3->addWidget(ButtonLogin);
    HBoxLayout3->addWidget(ButtonRegist);
    //HBoxLayout3->setSpacing(20);
    HBoxLayout4 = new QHBoxLayout();
    HBoxLayout4->addWidget(LabelCapt);
    HBoxLayout4->addWidget(EditCapt);
    HBoxLayout4->setSpacing(0);
    HBoxLayout4->setContentsMargins(67,0,165,0);

    VBoxLayout = new QVBoxLayout(this);

    /*垂直布局对象*/
    VBoxLayout->addLayout(HBoxLayout);
    VBoxLayout->addLayout(HBoxLayout1);
    VBoxLayout->addLayout(HBoxLayout2);
    VBoxLayout->addLayout(HBoxLayout4);
    VBoxLayout->addLayout(HBoxLayout3);
    VBoxLayout->setSpacing(20);
    VBoxLayout->setAlignment(Qt::AlignCenter);

    ButtonCapt = new QPushButton(this);
    ButtonCapt->setGeometry(QRect(225, 178, 84, 30));
    ButtonCapt->setStyleSheet("background-color:rgba(0,0,0,0)");
    ButtonCapt->setToolTip("看不清楚，换一张");

    m_captcha = getCaptcha();
    m_color = getColor();
    m_timer = new QTimer;
    m_timer->start(200);
}

void LoginWidget::init_connect()
{
    connect(ButtonLogin,SIGNAL(clicked(bool)),this,SLOT(login_slot()));
    connect(ButtonRegist,SIGNAL(clicked(bool)),this,SLOT(regist_slot()));
    connect(ButtonHidePwd,SIGNAL(clicked(bool)),this,SLOT(hide_slot()));
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
    connect(ButtonCapt, SIGNAL(clicked(bool)), this, SLOT(captClick()));
}

void LoginWidget::clear_edit()
{
    EditID->clear();
    EditPWD->clear();
    EditCapt->clear();
    Sleep(50);
}

LoginWidget::~LoginWidget()
{

}

void LoginWidget::paintEvent(QPaintEvent *event)
{
    QFont font;
    font.setPixelSize(20);
    QPainter painter(this);
    painter.fillRect(225, 178, 84, 30, Qt::black);
    painter.setFont(QFont("Comic Sans MS"));
    for(int i = 0; i < 100; i++)
    {
        painter.setPen(m_color[i % 4]);
        painter.drawPoint(225 + (qrand() % 84), 178 + (qrand() % 30));
    }
    for(int i = 0; i < 4; i++)
    {
        painter.setPen(m_color[i]);
        painter.setFont(font);
        painter.drawText(225 + 20 * i, 178, 20, 30, Qt::AlignCenter, QString(m_captcha[i]));
    }
}

QString LoginWidget::getCaptcha()
{
    QString ret;
    for(int i = 0; i < 4; ++i)
    {
        QChar c;
        int flag = qrand() % 4;
        switch (flag)
        {
            case 0: c='0' + qrand() % 10; break;
            case 1: c='A' + qrand() % 26; break;
            case 2: c='a' + qrand() % 26; break;
            default: c='0' + qrand() % 10; break;
        }
        ret += c;
    }
    return ret;
}

Qt::GlobalColor *LoginWidget::getColor()
{
    static Qt::GlobalColor colors[4];
    for(int i = 0; i < 4; i++)
    {
        colors[i] = static_cast<Qt::GlobalColor>((qrand() % 16) + 2);
    }
    return colors;
}

void LoginWidget::login_slot()
{
    qDebug() << "登录";
    if(EditID->text().isEmpty() || EditPWD->text().isEmpty()) {
        qDebug() << "账号密码不得为空";
        QMessageBox::information(NULL,"提示","账号密码不得为空");
        m_captcha = getCaptcha();
        EditCapt->clear();
    }
    else{
        if(QString::compare(EditCapt->text(),m_captcha) == 0) {
            bool ret = pSqlData->login_check(EditID->text(),EditPWD->text());
            if(ret == true) {
                int ret2 = pSqlData->checkSettingTable(EditID->text());
                if(ret2 == 1) {
                    AllWidget::pCarcorderWidget->updateCamera(AllWidget::pSettingWidget->pSettingPath->pCameraInfo,
                                                             AllWidget::pSettingWidget->pSettingPath->TimeInterval.toInt());
                    clear_edit();
                    this->close();
                    AllWidget::pCarcorderWidget->initCameraSurface();
                    AllWidget::pCarcorderWidget->show();
                }
                if(ret2 == 2) {
                    AllWidget::pSettingWidget->showPath();
                    clear_edit();
                    this->close();
                    AllWidget::pSettingWidget->show();
                }
                if(ret2 == 0) {
                    QMessageBox::information(NULL,"提示","系统问题 请重启");
                    this->close();
                }
            }
            else {
                clear_edit();
                m_captcha = getCaptcha();
            }
        }
        else {
            QMessageBox::information(NULL, "提示", "验证码错误");
            m_captcha = getCaptcha();
            EditCapt->clear();
        }
    }
}

void LoginWidget::regist_slot()
{
    qDebug() << "注册";
    clear_edit();
    this->close();
    AllWidget::pRegistWidget->show();
}

void LoginWidget::hide_slot()
{
    mask = ~mask;
    qDebug() << mask;
    if(mask != 1){
        EditPWD->setEchoMode(QLineEdit::Normal);
        ButtonHidePwd->setIcon(QIcon("image/eye1.png"));
        ButtonHidePwd->setToolTip("隐藏密码");
    }
    else{
        EditPWD->setEchoMode(QLineEdit::Password);
        ButtonHidePwd->setIcon(QIcon("image/eye.png"));
        ButtonHidePwd->setToolTip("显示密码");
    }

}

void LoginWidget::timerTimeout()
{
    m_color = getColor();
    update();
}

void LoginWidget::captClick()
{
    m_captcha = getCaptcha();
}
