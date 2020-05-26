#pragma once
#include <QGraphicsView>
#include "map.h"
#include "tower/ITower.h"
#include "towerplace.h"

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
    void createTower();
private:
    Map map;
    QGraphicsPixmapItem* build_curs;
    bool building;
    int lvl_h;
    int lvl_w;
    void renderMap();
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
};

