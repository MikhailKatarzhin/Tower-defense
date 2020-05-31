#pragma once
#include <QGraphicsObject>
#include <QPainter>

class CastlePlace : public QGraphicsObject
{
public:
    CastlePlace();
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPixmap * sprite;
};
