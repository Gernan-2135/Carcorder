#include "qcar.h"
#include "QMessageBox"
#include "allwidget.h"

QCar::QCar(const QString &filename,QGraphicsScene *scence):QPixmapItem(filename,scence)
{
    setPos(1000,450);
    this->setScale(qreal(0.15));
}

void QCar::advance(int phase)
{
    if(mapToScene(0,0).x()<=0)
    {
        delete this;
    }
    this->setPos(mapToScene(-60,0));
}

void QCar::docolliding()
{
    //QMessageBox::information(NULL,"提示","行车不规范 亲人两行泪");
    AllWidget::pStarview->close();
    AllWidget::pCarcorderWidget->show();
}

void QCar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-this->pixmap.width()/2,-this->pixmap.height(),this->pixmap);
    if(this->collidingItems().count()>0)
    {
        this->docolliding();
    }
}


