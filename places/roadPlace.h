#pragma once
#include <QGraphicsObject>
#include <QPainter>

class RoadPlace : public QGraphicsObject
{
    Q_OBJECT

public:
    const float BASEWEIGHT = 1;

    RoadPlace();
    void increaseWeight(int);
    void decreaseWeight(int);
    void initializationWeight();
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPixmap * sprite;
    float weight = BASEWEIGHT;
};
