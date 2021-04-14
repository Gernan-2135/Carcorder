#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QBrush>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>
#include <QTimer>
#include "sqldata.h"

class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    LoginWidget(QWidget *parent = 0);
    void init_control();
    void init_connect();
    void clear_edit();
    QString CurUser;
    ~LoginWidget();

protected:
    void paintEvent(QPaintEvent *event);
    QString getCaptcha();   //获取新一串验证码
    Qt::GlobalColor* getColor();    //获取新颜色

private:
    int mask;

    SqlData *pSqlData;

    QLabel *LabelTitle;
    QLabel *LabelID;
    QLabel *LabelPWD;
    QLabel *LabelCapt;
    QLineEdit *EditID;
    QLineEdit *EditPWD;
    QLineEdit *EditCapt;
    QPushButton *ButtonLogin;
    QPushButton *ButtonRegist;
    QPushButton *ButtonHidePwd;
    QPushButton *ButtonCapt;

    QHBoxLayout *HideBox;
    QHBoxLayout *HBoxLayout;
    QHBoxLayout *HBoxLayout1;
    QHBoxLayout *HBoxLayout2;
    QHBoxLayout *HBoxLayout3;
    QHBoxLayout *HBoxLayout4;
    QVBoxLayout *VBoxLayout;

    QString m_captcha;
    Qt::GlobalColor* m_color;
    QTimer *m_timer;

signals:
private slots:
    void login_slot();
    void regist_slot();
    void hide_slot();
    void timerTimeout();
    void captClick();
};

#endif // WIDGET_H
