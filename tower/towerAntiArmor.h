#pragma once

#include <QtWidgets>
#include <QPainter>
#include "tower/towerarea.h"
#include "bullet.h"
#include "tower/ITower.h"

class TowerAntiArmor : public ITower
{
    Q_OBJECT

public:

    const float MULTIPLIERRADIUS    = 1.2;
    const float MULTIPLIERPOWER     = 2.1;
    const float MULTIPLIERCOST      = 2.2;
    const float MULTIPLIERFIRINGRATE= 1.05;
    const float BASEFIRINGRATE      = 0.2;
    const int   BASECOST            = 200;
    const int   BASERADIUS          = 350;
    const int   BASEPOWER           = 150;

    float   getMULTIPLIERRADIUS();
    float   getMULTIPLIERPOWER();
    float   getMULTIPLIERCOST();
    float   getMULTIPLIERFIRINGRATE();

    float   getBASEFIRINGRATE();
    int     getBASECOST();
    int     getBASEPOWER();
    int     getBASERADIUS();

    TowerAntiArmor(QGraphicsObject * parent = nullptr);

    void setArea();
    void fire();
    ITower * copyTower();

    QPixmap* getSprite();
    int getLevel();
    int getPower();
    int getRadius();
    int getCost();
    int getSalePrice();
    float getFiringRate();
    TowerArea* getTowerArea();

    ~TowerAntiArmor();

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
    QPixmap * sprite = new QPixmap(":/res/images/Tower3.png");
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
    float firingRate = BASEFIRINGRATE;
};

