#pragma once
#include <QGraphicsObject>
#include <QPainter>
#include <QTimer>
#include "road.h"
#include "enemy/IEnemy.h"

class EnemyRunner: public IEnemy
{
    Q_OBJECT

public:
    EnemyRunner(Road, int wave);
    ~EnemyRunner();
    int getPoint();
    int getDistance();
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
    QTimer * life;
    Road way;

    int distance;
    int prize;
    int point;
    int max_hp;
    int current_hp;
    int speed;
    double dy;
    double dx;
};

