#pragma once

#include <QtWidgets>
#include <QPainter>
#include "towerarea.h"
#include "enemy/enemy.h"
#include "bullet.h"

class Tower : public QGraphicsObject
{
    Q_OBJECT

public:

    const float MULTIPLIERRADIUS  = 1.25;
    const float MULTIPLIERPOWER   = 1.9;
    const float MULTIPLIERCOST    = 2.1;

    Tower(QGraphicsObject * parent = nullptr);

    void setArea();
    void fire();

    int getLevel();
    int getPower();
    int getRadius();
    int getCost();
    int getSalePrice();

    ~Tower();

signals:
    void up(Tower*);

public slots:
    void chooseEnemy();
    void upgrade();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);

private:
    QPixmap * sprite;
    TowerArea* area;
    QPointF enemyPlace;
    QTimer * detecter;
    IEnemy * target;

    double centerX;
    double centerY;
    double l_centerX;
    double l_centerY;

    int point;
    int radius = 200;
    int power = 20;
    int cost = 50;
    int level = 0;
    int salePrice = 0;
};

