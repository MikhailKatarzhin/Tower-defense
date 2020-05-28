#include <QDebug>
#include <QGraphicsItem>
#include <QList>
#include <QPointF>
#include "RoadFinder.h"
#include "../towerplace.h"
#include "../tower/ITower.h"

RoadFinder::RoadFinder(
        QGraphicsScene* level,
        int cellHeight,
        int cellWidth
) {
    this->level = level;
    this->cellWidth = cellWidth;
    this->cellHeight = cellHeight;
}

void RoadFinder::test() {
    if (nullptr == level) {
        qDebug() << "RF: level is nil.";
        return;
    }
    QList<QGraphicsItem*> listOfItems = level->items();
    int towerPlaceCounter = 0;
    int towerCounter = 0;
    for (QGraphicsItem* item : listOfItems) {
        TowerPlace* towerPlace = dynamic_cast<TowerPlace*>(item);
        if (towerPlace != nullptr) {
            towerPlaceCounter++;
        }
        ITower* iTower = dynamic_cast<ITower*>(item);
        if (iTower != nullptr) {
            QPointF position = iTower->pos();
            qDebug() << "\n" << "iTower[x] = " << position.x() / cellHeight
                     << "\n" << "iTower[y] = " << position.y() / cellWidth;
            towerCounter++;
        }
    }
    qDebug() << "towerPlaceCounter == " << towerPlaceCounter
             << "\ntowerCounter == " << towerCounter;
}
