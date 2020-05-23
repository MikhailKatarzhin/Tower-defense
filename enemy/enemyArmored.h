#pragma once
#include <QGraphicsObject>
#include <QPainter>
#include <QTimer>
#include <math.h>
#include "road.h"
#include "enemy/IEnemy.h"

class EnemyArmored: public IEnemy
{
    Q_OBJECT

public:
    EnemyArmored(Road, int wave);
    ~EnemyArmored();
    int getPoint();
    int getpassedWay();
    void damaged(int);

protected:
    QRectF boundingRect() const;
    void paintHealthBar(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;

public slots:
    void move();
    void stop();
signals:
    void dead(int);
    void win();

private:
    QPixmap * sprite;
    QTimer * stepTimer;
    Road way;

    int passedWay;
    int prize;
    int point;
    int max_hp;
    int current_hp;
    int speed;
    double dy;
    double dx;
};

