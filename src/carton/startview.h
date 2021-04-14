#ifndef STARTVIEW_H
#define STARTVIEW_H

#include <QGraphicsView>
#include <QIcon>
#include <QBrush>
#include <QGraphicsScene>//场景类
#include <QResizeEvent>//图元
#include <QMouseEvent>
#include <QTimer>//定时器
#include <QLine>
#include <QLineF>
#include <QDebug>
#include <QPoint>
#include <QLabel>
#include <QVBoxLayout>
#include "sqldata.h"
#include "qwalker.h"
#include "qcar.h"

class StartView:public QGraphicsView
{
public:
    explicit StartView();

private:
    SqlData *pSqlData;
    QGraphicsScene *scence;
    QWalker *walker;
    QCar *car;
    QTimer *timer;

};

#endif // STARTVIEW_H
