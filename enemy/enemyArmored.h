#pragma once
#include <QGraphicsObject>
#include <QPainter>
#include <QTimer>
#include <math.h>
#include "road.h"
#include "enemy/IEnemy.h"
#include "places/roadPlace.h"
#include <QGraphicsScene>

class EnemyArmored: public IEnemy
{
    Q_OBJECT

public:
    EnemyArmored(Road, int wave, QGraphicsScene * level);
    ~EnemyArmored();
    int getPoint();
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
    QTimer * lifes;
    Road way;

    int passedWay;
    int prize;
    int point;
    int max_hp;
    int current_hp;
    int speed;
    int armor;
    double dy;
    double dx;
    QGraphicsScene* level;
    RoadPlace *nextRoadPlace;
};

