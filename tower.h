#pragma once

#include <QtWidgets>
#include <QPainter>
#include "towerarea.h"
#include "bullet.h"
#include "tower/ITower.h"

class Tower : public ITower
{
    Q_OBJECT

public:

    const float MULTIPLIERRADIUS    = 1.25;
    const float MULTIPLIERPOWER     = 1.9;
    const float MULTIPLIERCOST      = 2.1;
    const int   BASECOST            = 50;
    const int   BASERADIUS          = 200;
    const int   BASEPOWER           = 30;

    float   getMULTIPLIERRADIUS();
    float   getMULTIPLIERPOWER();
    float   getMULTIPLIERCOST();
    int     getBASECOST();

    Tower(QGraphicsObject * parent = nullptr);

    void setArea();
    void fire();

    QPixmap* getSprite();
    int getLevel();
    int getPower();
    int getRadius();
    int getCost();
    int getSalePrice();

    ~Tower();

signals:
    void updateTower(ITower*);

public slots:
    void chooseEnemy();
    void upgrade();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);

private:
    QPixmap * sprite = new QPixmap(":/res/images/Tower.png");
    TowerArea* area;
    QPointF enemyPlace;
    QTimer * detecter;
    IEnemy * target;

    double centerX;
    double centerY;
    double l_centerX;
    double l_centerY;

    int point;
    int radius  = BASERADIUS;
    int power   = BASEPOWER;
    int cost    = BASECOST;
    int level   = 0;
    int salePrice = 0;
};

