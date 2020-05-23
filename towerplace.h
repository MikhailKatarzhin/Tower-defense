#pragma once
#include <QGraphicsObject>
#include <QPainter>

class TowerPlace : public QGraphicsObject
{
    Q_OBJECT

public:
    TowerPlace();
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPixmap * sprite;
};
