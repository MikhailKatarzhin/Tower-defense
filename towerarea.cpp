#include "towerarea.h"

TowerArea::TowerArea( QGraphicsObject *parent)
{
    visible = false;
}

void TowerArea::setRadius(int r)
{
    radius = r;
}

void TowerArea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::darkGreen, 3, Qt::SolidLine));
    painter->drawEllipse(0, 0, radius, radius);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF TowerArea::boundingRect() const
{
    return QRectF(0, 0, radius, radius);
}
QPainterPath TowerArea::shape() const
 {
     QPainterPath path;
     path.addEllipse(boundingRect());
     return path;
 }
