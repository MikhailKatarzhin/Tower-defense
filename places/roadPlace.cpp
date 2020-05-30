#include "roadPlace.h"

RoadPlace::RoadPlace()
{
    sprite = new QPixmap(":/res/images/Road.png");
}

void RoadPlace::increaseWeight(int iWeight)
{
    weight += iWeight;
}
void RoadPlace::decreaseWeight(int dWeight)
{
    if(weight > dWeight)
        weight -= dWeight;
    else
        weight = 0;
}
void RoadPlace::initializationWeight()
{
    weight = BASEWEIGHT;
}

QRectF RoadPlace::boundingRect() const
{
    return QRectF(0, 0, sprite->width(), sprite->height());
}

void RoadPlace::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(*sprite));
    painter->setPen(Qt::NoPen);
    painter->drawRect(0, 0, sprite->width(), sprite->height());
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
