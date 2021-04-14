#include "allwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AllWidget::pStarview = new StartView;
    AllWidget::pStarview->show();
//    QString filename = "屌丝男士.mov";
//    PlayVideoWidget *w = new PlayVideoWidget;
//    w->setVideoName(filename);
//    w->show();

    return a.exec();
}
