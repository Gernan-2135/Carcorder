#ifndef QPIXMAPITEM_H
#define QPIXMAPITEM_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsScene>

class QPixmapItem:public QGraphicsItem
{
public:
    QPixmapItem(const QString &filename,QGraphicsScene *scence);
    virtual QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
protected:
    QPixmap pixmap;
};

#endif // QPIXMAPITEM_H
