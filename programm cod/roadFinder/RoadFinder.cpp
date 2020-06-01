#include <QDebug>
#include <QGraphicsItem>
#include <QList>
#include <QPointF>
#include "RoadFinder.h"
#include "places/castlePlace.h"
#include "places/roadPlace.h"
#include "places/towerplace.h"
#include "tower/ITower.h"
#include <QTime>

RoadFinder::RoadFinder(
        QGraphicsScene* level,
        int cellHeight,
        int cellWidth
)
{
    this->level = level;
    this->cellWidth = cellWidth;
    this->cellHeight = cellHeight;
}

void RoadFinder::calculationMap()
{
    QTime time = QTime().currentTime();
    calculationPlacesWithTowers();
    calculationWaysFromCastle();
    qDebug()<<"msec for calculation map: "<< time.msecsTo(QTime().currentTime());
}

void RoadFinder::calculationPlacesWithTowers()
{
    if (nullptr == level) {
        qDebug() << "RF: level is nil.";
        return;
    }
    QList<QGraphicsItem*> listOfItems = level->items();
    for (QGraphicsItem* item : listOfItems)
    {
        RoadPlace * roadPlace = dynamic_cast<RoadPlace*>(item);
        if(roadPlace != nullptr)
        {
            roadPlace->initializationAllWeight();
        }
    }
    listOfItems = level->items();
    for (QGraphicsItem* item : listOfItems)
    {
        ITower* iTower = dynamic_cast<ITower*>(item);
        if (iTower != nullptr)
        {
            if(iTower->getTowerArea() == nullptr)
                break;
            QList<QGraphicsItem *> colliding_items = iTower->getTowerArea()->collidingItems(Qt::IntersectsItemShape);
            for (int i = 0, n = colliding_items.size(); i < n; ++i)
            {
                RoadPlace *roadPlace = dynamic_cast<RoadPlace *>(colliding_items[i]);
                if(roadPlace != nullptr)
                {
                    roadPlace->increaseDamageWeight(iTower->getPower() * iTower->getFiringRate());
                    //qDebug()<< "newweight: "<< roadPlace->getWeight();
                }
            }

        }
        CastlePlace * castlePlace = dynamic_cast<CastlePlace*>(item);
        if(castlePlace != nullptr)
        {
            castle = castlePlace->pos();
        }
    }
}

void RoadFinder::calculationWaysFromCastle()
{
    QTransform * qtransform = new QTransform();
    QMap<float, QList<RoadPlace *>*> calculationPoints;
    RoadPlace *roadPlace;
    QGraphicsItem * upperItem = level->itemAt(castle.x(), castle.y(), *qtransform);
    QList<QGraphicsItem *> listItems = upperItem->collidingItems();
    for(QGraphicsItem * item : listItems)
    {
        roadPlace =  dynamic_cast<RoadPlace *>(item);
        if(roadPlace != nullptr)
            break;
    }
    if( roadPlace != nullptr)
    {
        roadPlace->increaseWeight(1);
        if(!calculationPoints.contains(roadPlace->getWeight()))
            calculationPoints.insert(roadPlace->getWeight(), new QList<RoadPlace *>());
        calculationPoints[roadPlace->getWeight()]->push_back(roadPlace);
    }
    while( !calculationPoints.isEmpty() )
    {
        RoadPlace *currentRoadPlace = calculationPoints.first()->first();

        //qDebug()<<"xcp: "<<currentRoadPlace->x()<<"\tycp: "<<currentRoadPlace->y();

        upperItem = level->itemAt(currentRoadPlace->pos().x(), currentRoadPlace->pos().y() + cellHeight, *qtransform);
        if(upperItem != nullptr)
        {
            roadPlace = nullptr;
            roadPlace = dynamic_cast<RoadPlace *>(upperItem);
            if(nullptr == roadPlace)
            {
                listItems = upperItem->collidingItems();
                for(QGraphicsItem * item : listItems)
                {
                    roadPlace =  dynamic_cast<RoadPlace *>(item);
                    if(roadPlace != nullptr)
                        break;
                }
            }
            if( roadPlace != nullptr)
            compareAndCalculationWeightWithCurrent(roadPlace, currentRoadPlace, &calculationPoints);
        }

        upperItem = (level->itemAt(currentRoadPlace->pos().x(), currentRoadPlace->pos().y() - cellHeight, *qtransform));
        if(upperItem != nullptr)
        {
            roadPlace = nullptr;
            roadPlace = dynamic_cast<RoadPlace *>(upperItem);
            if(nullptr == roadPlace)
            {
                listItems = upperItem->collidingItems();
                for(QGraphicsItem * item : listItems)
                {
                    roadPlace =  dynamic_cast<RoadPlace *>(item);
                    if(roadPlace != nullptr)
                        break;
                }
            }
            if( roadPlace != nullptr)
            compareAndCalculationWeightWithCurrent(roadPlace, currentRoadPlace, &calculationPoints);
        }

        upperItem = (level->itemAt(currentRoadPlace->pos().x() + cellWidth, currentRoadPlace->pos().y(), *qtransform));
        if(upperItem != nullptr)
        {
            roadPlace = nullptr;
            roadPlace = dynamic_cast<RoadPlace *>(upperItem);
            if(nullptr == roadPlace)
            {
                listItems = upperItem->collidingItems();
                for(QGraphicsItem * item : listItems)
                {
                    roadPlace =  dynamic_cast<RoadPlace *>(item);
                    if(roadPlace != nullptr)
                        break;
                }
            }
            if( roadPlace != nullptr)
            compareAndCalculationWeightWithCurrent(roadPlace, currentRoadPlace, &calculationPoints);
        }

        upperItem = (level->itemAt(currentRoadPlace->pos().x() - cellWidth, currentRoadPlace->pos().y(), *qtransform));
        if(upperItem != nullptr)
        {
            roadPlace = nullptr;
            roadPlace = dynamic_cast<RoadPlace *>(upperItem);
            if(nullptr == roadPlace)
            {
                listItems = upperItem->collidingItems();
                for(QGraphicsItem * item : listItems)
                {
                    roadPlace =  dynamic_cast<RoadPlace *>(item);
                    if(roadPlace != nullptr)
                        break;
                }
            }
            if( roadPlace != nullptr)
            compareAndCalculationWeightWithCurrent(roadPlace, currentRoadPlace, &calculationPoints);
        }

        calculationPoints.first()->removeFirst();
        if(calculationPoints.first()->isEmpty())
            calculationPoints.remove(calculationPoints.firstKey());
    }
}

void RoadFinder::compareAndCalculationWeightWithCurrent(
        RoadPlace *roadPlace,
        RoadPlace *currentRoadPlace,
        QMap<float, QList<RoadPlace *>*> *calculationPoints
)
{
    if( roadPlace != nullptr)
    {
   //         qDebug()<<"xrp: "<<roadPlace->x()<<"\tyrp: "<<roadPlace->y();

            if(roadPlace->getWeight() == roadPlace->BASEWEIGHT + roadPlace->getDamageWeight())
            {
                roadPlace->increaseWeight(currentRoadPlace->getWeight());
                if(!calculationPoints->contains(roadPlace->getWeight()))
                    calculationPoints->insert(roadPlace->getWeight(), new QList<RoadPlace *>());
                (*calculationPoints)[roadPlace->getWeight()]->push_back(roadPlace);
            }else
            if(roadPlace->getWeight() - roadPlace->getDamageWeight() - roadPlace->BASEWEIGHT > currentRoadPlace->getWeight())
            {
                roadPlace->initializationWeight();
                roadPlace->increaseWeight(currentRoadPlace->getWeight() + roadPlace->getDamageWeight());
                if(!calculationPoints->contains(roadPlace->getWeight()))
                    calculationPoints->insert(roadPlace->getWeight(), new QList<RoadPlace *>());
                (*calculationPoints)[roadPlace->getWeight()]->push_back(roadPlace);
            }
    }
}

void RoadFinder::printAllMap() {
    qDebug() << "RoadFinder::printAllMap() START";
    QList<QGraphicsItem*> listOfAllItems = level->items();
    for (QGraphicsItem* item: listOfAllItems) {
        int x = item->pos().x() / cellHeight;
        int y = item->pos().y() / cellWidth;
        RoadPlace* itemAsRoadPlace = dynamic_cast<RoadPlace*>(item);
        if (nullptr == itemAsRoadPlace) {
            qDebug() << "[" << x << ", " << y << "] is not RoadPlace.";
            continue;
        }
        qDebug() << "[" << x << ", " << y << "] is RoadPlace and weight is "
                 << itemAsRoadPlace->getWeight();
    }
    qDebug() << "RoadFinder::printAllMap() END";
}
