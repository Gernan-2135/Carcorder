#ifndef DECODEWIDGET_H
#define DECODEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QProgressBar>
#include <QPushButton>
#include <QDateEdit>
#include <QHBoxLayout>
#include <QComboBox>
#include "videodecode.h"

class DecodeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DecodeWidget(QWidget *parent = nullptr);
    void init_control();
    void set_control();
    void show_filepath(const QString &filePath);
    void init_connect();
    ~DecodeWidget();

private:
    QStringList VideoList;

    QString FilePath;
    QString InFileName;
    QString OutFileName;

    QListWidget *pListWidget;
    QDateEdit *pDateEdit;
    QWidget *HLayoutWidget;
    QHBoxLayout *HLayout;
    QLabel *LabelIn;
    QLineEdit *EditIn;
    QWidget *HLayoutWidget1;
    QHBoxLayout *HLayout1;
    QLabel *LabelFormat;
    QComboBox *BoxFormat;
    QWidget *HLayoutWidget2;
    QHBoxLayout *HLayout2;
    QLineEdit *EditPath;
    QPushButton *ButtonPath;
    QProgressBar *pProgressBar;
    QPushButton *ButtonEnter;
    QPushButton *ButtonEsc;

    VideoDecode *pVideoDecode;

    enum VIDEO_FORMAT
    {
        FORMAT_MP4=0X00,
        FORMAT_AVI,
        FORMAT_MOV
    };

signals:

public slots:
    void choosePathSlot();
    void enterSlot();    
    void escSlot();

private slots:
    void listItemClicked(QListWidgetItem *item);
    void rcvSig(int value);
    void updateSlot();
};

#endif // DECODEWIDGET_H
