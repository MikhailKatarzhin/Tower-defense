#pragma once

#include <QGraphicsObject>
#include <QTimer>
#include <QPainter>
#include "enemy/IEnemy.h"

class Bullet: public QGraphicsObject
{
    Q_OBJECT

public:
    Bullet(QGraphicsObject * parent);
    ~Bullet();

public slots:
    void move();
private:
    QPixmap * sprite;
    QTimer * move_timer;
    int STEP_SIZE;
    double theta;
    double dy;
    double dx;
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;

};
