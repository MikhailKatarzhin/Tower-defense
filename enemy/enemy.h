#pragma once
#include <QGraphicsObject>
#include <QPainter>
#include <QTimer>
#include <math.h>
#include "road.h"
#include "enemy/IEnemy.h"

class Enemy: public IEnemy
{
    Q_OBJECT

public:
    Enemy(Road, int wave);
    ~Enemy();
    int getPoint() override;
    int getpassedWay()override;
    void damaged(int)override;

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const override;

public slots:
    void move() override;
    void stop() override;
signals:
    void dead(int) override;
    void win() override;

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
    double dy;
    double dx;
};

