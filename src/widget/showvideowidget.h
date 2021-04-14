#ifndef SHOWVIDEOWIDGET_H
#define SHOWVIDEOWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QComboBox>
#include <QDateEdit>
#include "playvideowidget.h"

class ShowVideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShowVideoWidget(QWidget *parent = nullptr);
    void init_control();
    void set_control();
    void init_connect();
    void show_filepath(const QString &filePath);
    void setPlayButton();
    ~ShowVideoWidget();

private:
    QString FilePath;
    QLabel *LabelTitle;
    QPushButton *ButtonBack;
    QDateEdit *pDateEdit;
    QListWidget *pListWidget;
    QStringList VideoList;
    PlayVideoWidget *pPlayVideoWidget;

signals:

public slots:
    void esc_slot();

private slots:
    void update_slot();
    void listItemClicked(QListWidgetItem *item);
};

#endif // SHOWVIDEOWIDGET_H
