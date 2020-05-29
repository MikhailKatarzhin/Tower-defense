#include "denPlace.h"

DenPlace::DenPlace()
{
    sprite = new QPixmap(":/res/images/Spawn.png");
}

QRectF DenPlace::boundingRect() const
{
    return QRectF(0, 0, sprite->width(), sprite->height());
}

void DenPlace::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(*sprite));
    painter->setPen(Qt::NoPen);
    painter->drawRect(0, 0, sprite->width(), sprite->height());
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
