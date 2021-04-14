#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QFileDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QCameraInfo>
#include <QBrush>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>
#include "sqldata.h"

struct SettingPath
{
    QString VideoPath;
    QString ImagePath;
    QCameraInfo pCameraInfo;
    QString TimeInterval;
};

class SettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingWidget(QWidget *parent = nullptr);
    void init_control();
    void set_control();
    void init_connect();
    void clear_edit();
    void check_path();
    void showPath();
    bool createPath(QString filepath);
    SettingPath *pSettingPath;

private:
    SqlData *pSqlData;

    QLabel *LabelTitle;
    QLabel *LabelVideoLocal;
    QLabel *LabelImageLocal;
    QLabel *LabelTimeInterval;
    QLabel *LabelCamera;

    QLineEdit *EditVideoLocal;
    QLineEdit *EditImageLocal;
    QLineEdit *EditTimeInterval;

    QComboBox *BoxCamera;
    QList <QCameraInfo> pCameraInfo;

    QPushButton *ButtonVideoLocal;
    QPushButton *ButtonImageLocal;

    QPushButton *ButtonEnter;
    QPushButton *ButtonEsc;

    QHBoxLayout *HBoxLayout;
    QHBoxLayout *HBoxLayout1;
    QHBoxLayout *HBoxLayout2;
    QHBoxLayout *HBoxLayout3;
    QHBoxLayout *HBoxLayout4;
    QHBoxLayout *HBoxLayout5;

    QVBoxLayout *VBoxLayout;

signals:

public slots:
    void video_local_slot();
    void image_local_slot();
    void enter_slot();
    void esc_slot();
};

#endif // SETTINGWIDGET_H
