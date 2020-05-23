#pragma once
#include <QGraphicsView>
#include "levelparser.h"
#include "tower.h"
#include "towerplace.h"

class Level : public QGraphicsScene
{
    Q_OBJECT

public:
    Level(Map &_map,QWidget * parent = nullptr );
    void createPlace(QPointF);
signals:
    void successBuild(int);
    void setUI(Tower* tower = nullptr);
public slots:
    void createTower();
private:
    Map map;
    QGraphicsPixmapItem* build_curs;
    bool building;
    int lvl_h;
    int lvl_w;
    void createMap();
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
};

