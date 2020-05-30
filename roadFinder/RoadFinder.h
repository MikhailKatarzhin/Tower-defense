#pragma once
#include <QGraphicsScene>
#include "places/roadPlace.h"

class RoadFinder {
public:
    RoadFinder(
            QGraphicsScene* level,
            int cellHeight,
            int cellWidth
    );
public slots:
    void calculationMap();

private:
    int cellWidth;
    int cellHeight;
    QGraphicsScene* level;
    QPointF castle;

    void calculationPlacesWithTowers();
    void calculationWaysFromCastle();
    void compareAndCalculationWeightWithCurrent(
            RoadPlace *roadPlace,
            RoadPlace *currentRoadPlace,
            QMap<float, QList<RoadPlace *>*> *calculationPoints
    );
};
