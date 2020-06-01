#pragma once
#include <QGraphicsObject>
#include <QPainter>

class DenPlace : public QGraphicsObject
{
    Q_OBJECT
public:
    DenPlace();
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPixmap * sprite;
};
