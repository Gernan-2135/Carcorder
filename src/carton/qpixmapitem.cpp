#include "qpixmapitem.h"

QPixmapItem::QPixmapItem(const QString &filename,QGraphicsScene *scence)
{
    pixmap.load(filename);
    scence->addItem(this);
}

QRectF QPixmapItem::boundingRect() const
{
    return QRectF(-this->pixmap.width()/2,-this->pixmap.height(),this->pixmap.width(),this->pixmap.height());
}

void QPixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-this->pixmap.width()/2,-this->pixmap.height(),this->pixmap);
}
