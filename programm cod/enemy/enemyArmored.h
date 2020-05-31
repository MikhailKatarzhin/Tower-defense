#pragma once
#include <math.h>
#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>
#include "enemy/IEnemy.h"
#include "places/roadPlace.h"

class EnemyArmored: public IEnemy
{
    Q_OBJECT

public:
    EnemyArmored(QPointF *startCoordinats, int wave, QGraphicsScene * level);
    ~EnemyArmored();
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
    int point;
    int max_hp;
    int current_hp;
    int speed;
    int armor;

    QGraphicsScene* level;
    RoadPlace *nextRoadPlace;
};

