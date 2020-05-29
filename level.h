#pragma once
#include <QGraphicsView>
#include "map.h"
#include "tower/ITower.h"
#include "towerplace.h"
#include "places/castlePlace.h"
#include "places/denPlace.h"
#include "places/roadPlace.h"
#include "roadFinder/RoadFinder.h"

class Level : public QGraphicsScene
{
    Q_OBJECT

public:
    Level(Map &_map,QWidget * parent = nullptr );
    void createPlace(QPointF);
signals:
    void successBuild(int);
    void setUI(ITower* tower = nullptr);
public slots:
    void createTower(ITower * tower);
private:
    RoadFinder* roadFinder;
    Map map;
    QGraphicsPixmapItem* build_curs;
    bool building;
    int lvl_h;
    int lvl_w;
    ITower * tower;
    void renderMap();
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
};

