#include "qwalker.h"

QWalker::QWalker(const QString &filename,QGraphicsScene *scence):QPixmapItem(filename,scence)
{
    setPos(400,250);
    this->setScale(qreal(0.2));
}

void QWalker::advance(int phase)
{
    if(mapToScene(0,0).y()<=0)
    {
        delete this;
    }
    this->setPos(mapToScene(0,30));
}
