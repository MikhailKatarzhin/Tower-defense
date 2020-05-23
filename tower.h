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
    Tower(QGraphicsObject * parent = nullptr);

    void setArea();
    void fire();

    int getLevel();
    int getPower(int);
    int getRadius(int);
    int getCost(int);

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
    Enemy * target;

    double centerX;
    double centerY;
    double l_centerX;
    double l_centerY;

    int point;
    int radius[3];
    int power[3];
    int cost[3];
    int level;
};

