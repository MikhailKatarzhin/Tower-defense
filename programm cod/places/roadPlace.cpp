#include "roadPlace.h"

RoadPlace::RoadPlace()
{
    sprite = new QPixmap(":/res/images/Road.png");
}

void RoadPlace::increaseWeight(int iWeight)
{
    weight += iWeight;
}
void RoadPlace::increaseDamageWeight(int idWeight)
{
    damageWeight += idWeight;
    increaseWeight(idWeight);
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
    weight = BASEWEIGHT + damageWeight;
}
void RoadPlace::initializationDamageWeight()
{
    decreaseWeight(damageWeight);
    damageWeight = 0;
}
void RoadPlace::initializationAllWeight()
{
    weight = BASEWEIGHT;
    damageWeight = 0;
}
float RoadPlace::getWeight()
{
    return weight;
}
float RoadPlace::getDamageWeight()
{
    return damageWeight;
}
QPixmap* RoadPlace::getSprite()
{
    return sprite;
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
