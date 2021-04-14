#ifndef SHOWIMAGEWIDGET_H
#define SHOWIMAGEWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QComboBox>
#include <QDateEdit>

class ShowImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShowImageWidget(QWidget *parent = nullptr);
    void init_control();
    void set_control();
    void init_connect();
    void show_filepath(const QString &filePath);
    ~ShowImageWidget();

private:

    QStringList ImgList;
    QString FilePath;
    QLabel *LabelTitle;
    QPushButton *ButtonBack;
    QDateEdit *pDateEdit;
    QListWidget *pListWidget;

signals:

public slots:
    void esc_slot();

private slots:
    void update_slot();

private slots:
    void listItemClicked(QListWidgetItem *item);
};

#endif // SHOWIMAGEWIDGET_H
