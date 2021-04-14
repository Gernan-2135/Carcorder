#ifndef QCAR_H
#define QCAR_H

#include "qpixmapitem.h"
#include <QGraphicsScene>

class QCar:public QPixmapItem
{
public:
    QCar(const QString &filename,QGraphicsScene *scence);
    void advance(int phase);
    void docolliding();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // QCAR_H
