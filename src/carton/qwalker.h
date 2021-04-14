#ifndef QWALKER_H
#define QWALKER_H

#include "qpixmapitem.h"
#include <QGraphicsScene>

class QWalker:public QPixmapItem
{
public:
    QWalker(const QString &filename,QGraphicsScene *scence);
    void advance(int phase);

};

#endif // QWALKER_H
