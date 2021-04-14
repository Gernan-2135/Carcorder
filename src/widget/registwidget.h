#ifndef REGISTWIDGET_H
#define REGISTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QBrush>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>
#include "sqldata.h"

class RegistWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RegistWidget(QWidget *parent = nullptr);
    void init_control(); //控件初始化
    void init_connect(); //槽初始化
    void clear_edit();
private:
    int mask;

    SqlData *pSqlData;

    QLabel *LabelTitle;
    QLabel *LabelID;
    QLabel *LabelName;
    QLabel *LabelPwd;
    QLabel *LabelCPwd;
    QLineEdit *EditID;
    QLineEdit *EditName;
    QLineEdit *EditPwd;
    QLineEdit *EditCPwd;
    QPushButton *ButtonEnter;
    QPushButton *ButtonEsc;
    QPushButton *ButtonHidePwd;

    QHBoxLayout *HideBox;
    QHBoxLayout *HBoxLayout;
    QHBoxLayout *HBoxLayout1;
    QHBoxLayout *HBoxLayout2;
    QHBoxLayout *HBoxLayout3;
    QHBoxLayout *HBoxLayout4;
    QHBoxLayout *HBoxLayout5;

    QVBoxLayout *VBoxLayout;

signals:

public slots:
    void regist_slot();
    void hide_slot();
    void esc_slot();
};

#endif // REGISTWIDGET_H
