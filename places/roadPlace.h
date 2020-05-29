#pragma once
#include <QGraphicsObject>
#include <QPainter>

class RoadPlace : public QGraphicsObject
{
    Q_OBJECT

public:
    RoadPlace();
    void increaseWeight(int);
    void decreaseWeight(int);
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPixmap * sprite;
    int weight = 1;
};
