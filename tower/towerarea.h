#pragma once
#include <QGraphicsObject>
#include <QPainter>

class TowerArea : public QGraphicsObject
{
    Q_OBJECT
public:
    TowerArea(QGraphicsObject *parent = nullptr);
    void setRadius(int);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    QRectF boundingRect() const;
    QPainterPath shape() const;
private:
    int radius;
    bool visible;
};
