#pragma once
#include <math.h>
#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>
#include "enemy/IEnemy.h"
#include "places/roadPlace.h"

class Enemy: public IEnemy
{
    Q_OBJECT

public:
    Enemy(QPointF *startCoordinats, int wave, QGraphicsScene * level);
    ~Enemy();
    int getpassedWay();
    int getSpeed();
    int getArmor();
    void damaged(int);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;

public slots:
    void move();
    void stop();
signals:
    void dead(int);
    void win();

private:
    QPixmap * sprite;
    QTimer * steps;

    int passedWay;
    int prize;
    int max_hp;
    int current_hp;
    int speed;
    int armor;

    QGraphicsScene* level;
    RoadPlace *nextRoadPlace;
};
