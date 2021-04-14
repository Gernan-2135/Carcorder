#include "registwidget.h"
#include "allwidget.h"
#include <QRegExpValidator>
#include <QMessageBox>

RegistWidget::RegistWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(400,400);
    this->setWindowTitle("行车记录仪1.0版本");//设置头标

    mask = 1;

    QPalette palette;
    //调色板
    palette.setColor(QPalette::Background,Qt::white);
    this->setPalette(palette);

    init_control();
    init_connect();
}

void RegistWidget::init_control()
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
    btnStyle = "QPushButton{background-color:white; font-size:15px; border: 2px groove gray; border-style: outset;}"
           "QPushButton:hover{background-color:white; color: black;}"
          "QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }";

    LabelTitle = new QLabel();
    LabelTitle->setText("注册");
    LabelTitle->setFont(font);
    LabelTitle->setMinimumWidth(60);
    LabelID = new QLabel();
    LabelID ->setText("账号:");
    LabelID->setFont(font1);
    LabelID->setMinimumWidth(42);
    LabelName = new QLabel();
    LabelName ->setText("用户名:");
    LabelName->setFont(font1);
    LabelName->setMinimumWidth(54);
    LabelPwd = new QLabel();
    LabelPwd->setText("密码: ");
    LabelPwd->setFont(font1);
    LabelPwd->setMinimumWidth(45);
    LabelCPwd = new QLabel();
    LabelCPwd->setText("确认密码:");
    LabelCPwd->setFont(font1);
    LabelCPwd->setMinimumWidth(67);

    QRegExpValidator *pRevalidotor = new QRegExpValidator(QRegExp("[a-zA-Z0-9]{25}"), this);
    QRegExpValidator *pRevalidotor1 = new QRegExpValidator(QRegExp("[0-9]{25}"), this);
    EditID = new QLineEdit();
    EditID->setFont(font2);
    EditID->setMinimumSize(QSize(70, 30));
    EditID->setMaxLength(8);
    EditID->setValidator(pRevalidotor1);
    EditName = new QLineEdit();
    EditName->setFont(font2);
    EditName->setMinimumSize(QSize(70, 30));
    EditName->setMaxLength(16);
    EditPwd = new QLineEdit();
    EditPwd->setFont(font2);
    EditPwd->setMinimumSize(QSize(70, 30));
    EditPwd->setMaxLength(20);
    EditPwd->setValidator(pRevalidotor);
    EditPwd->setEchoMode(QLineEdit::Password);
    EditPwd->setPlaceholderText(QStringLiteral("密码不得少于8位"));
    EditCPwd = new QLineEdit();
    EditCPwd->setFont(font2);
    EditCPwd->setMinimumSize(QSize(70, 30));
    EditCPwd->setMaxLength(20);
    EditCPwd->setValidator(pRevalidotor);
    EditCPwd->setEchoMode(QLineEdit::Password);
    EditCPwd->setPlaceholderText(QStringLiteral("两次输入密码保持一致"));

    ButtonEnter = new QPushButton();
    ButtonEnter->setText("确定");
    ButtonEnter->setStyleSheet(btnStyle);
    ButtonEnter->setMinimumHeight(40);
    ButtonEnter->setMaximumWidth(80);
    ButtonEsc = new QPushButton();
    ButtonEsc->setText("取消");
    ButtonEsc->setStyleSheet(btnStyle);
    ButtonEsc->setMinimumHeight(40);
    ButtonEsc->setMaximumWidth(80);
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
    HideBox->setContentsMargins(155,0,0,0);
    EditPwd->setLayout(HideBox);

    HBoxLayout = new QHBoxLayout();
    HBoxLayout->addWidget(LabelTitle);
    HBoxLayout->setContentsMargins(170,0,150,0);

    HBoxLayout1 = new QHBoxLayout();
    HBoxLayout1->addWidget(LabelID);
    HBoxLayout1->addWidget(EditID);
    HBoxLayout1->setSpacing(4);
    HBoxLayout1->setContentsMargins(80,0,80,0);

    HBoxLayout2 = new QHBoxLayout();
    HBoxLayout2->addWidget(LabelName);
    HBoxLayout2->addWidget(EditName);
    HBoxLayout2->setSpacing(4);
    HBoxLayout2->setContentsMargins(67,0,80,0);

    HBoxLayout3 = new QHBoxLayout();
    HBoxLayout3->addWidget(LabelPwd);
    HBoxLayout3->addWidget(EditPwd);
    //HBoxLayout3->addWidget(ButtonHidePwd);
    HBoxLayout3->setSpacing(0);
    HBoxLayout3->setContentsMargins(80,0,80,0);

    HBoxLayout4 = new QHBoxLayout();
    HBoxLayout4->addWidget(LabelCPwd);
    HBoxLayout4->addWidget(EditCPwd);
    HBoxLayout4->setSpacing(4);
    HBoxLayout4->setContentsMargins(54,0,80,0);

    HBoxLayout5 = new QHBoxLayout();
    HBoxLayout5->addWidget(ButtonEnter);
    HBoxLayout5->addWidget(ButtonEsc);

    VBoxLayout = new QVBoxLayout(this);

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

void RegistWidget::init_connect()
{
    connect(ButtonEnter,SIGNAL(clicked(bool)),this,SLOT(regist_slot()));
    connect(ButtonEsc,SIGNAL(clicked(bool)),this,SLOT(esc_slot()));
    connect(ButtonHidePwd,SIGNAL(clicked(bool)),this,SLOT(hide_slot()));

}

void RegistWidget::clear_edit()
{
    EditID->clear();
    EditName->clear();
    EditPwd->clear();
    EditCPwd->clear();
}

void RegistWidget::regist_slot()
{
    if(EditID->text().isEmpty() || EditName->text().isEmpty() || EditPwd->text().isEmpty() || EditCPwd->text().isEmpty()){
        QMessageBox::information(NULL,"提示","输入框不得为空");
        qDebug() << "输入框不得为空";
    }
    else{
        if(EditPwd->text().length() < 8) {
            QMessageBox::information(NULL, "提示" ,"密码不得少于8位数");
        }
        else {
            if(QString::compare(EditPwd->text(),EditCPwd->text()) == 0){
                bool ret = pSqlData->regist_check(EditID->text(),EditName->text(),EditPwd->text());
                if(ret == true){
                    pSqlData->insertSettingTable(EditID->text(),NULL,NULL,NULL);
                    clear_edit();
                    this->close();
                    AllWidget::pLoginWidget->show();
                }
            }
            else{
                QMessageBox::information(NULL,"提示","密码不一致 请重新输入");
                qDebug() << "密码不一致 请重新输入";
            }
        }
    }
}

void RegistWidget::hide_slot()
{
    mask = ~mask;
    qDebug() << mask;
    if(mask != 1){
        EditPwd->setEchoMode(QLineEdit::Normal);
        EditCPwd->setEchoMode(QLineEdit::Normal);
        ButtonHidePwd->setIcon(QIcon("image/eye1.png"));
        ButtonHidePwd->setToolTip("隐藏密码");
    }
    else{
        EditPwd->setEchoMode(QLineEdit::Password);
        EditCPwd->setEchoMode(QLineEdit::Password);
        ButtonHidePwd->setIcon(QIcon("image/eye.png"));
        ButtonHidePwd->setToolTip("显示密码");
    }
}

void RegistWidget::esc_slot()
{
    this->close();
    AllWidget::pLoginWidget->show();
}
