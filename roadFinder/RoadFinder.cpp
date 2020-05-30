#include <QDebug>
#include <QGraphicsItem>
#include <QList>
#include <QPointF>
#include "RoadFinder.h"
#include "places/castlePlace.h"
#include "places/roadPlace.h"
#include "towerplace.h"
#include "tower/ITower.h"

RoadFinder::RoadFinder(
        QGraphicsScene* level,
        int cellHeight,
        int cellWidth
) {
    this->level = level;
    this->cellWidth = cellWidth;
    this->cellHeight = cellHeight;
}

void RoadFinder::calculationMap()
{
    calculationPlacesWithTowers();
    calculationWaysFromCastle();
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
    int towerPlaceCounter = 0;
    int towerCounter = 0;
    for (QGraphicsItem* item : listOfItems)
    {
        TowerPlace* towerPlace = dynamic_cast<TowerPlace*>(item);
        if (towerPlace != nullptr)
            towerPlaceCounter++;
        ITower* iTower = dynamic_cast<ITower*>(item);
        if (iTower != nullptr)
        {
            QPointF position = iTower->pos();
            qDebug() << "\n" << "iTower[x] = " << position.x() / cellHeight
                     << "\n" << "iTower[y] = " << position.y() / cellWidth;
            towerCounter++;
            if(iTower->getTowerArea() == nullptr)
                break;
            QList<QGraphicsItem *> colliding_items = iTower->getTowerArea()->collidingItems(Qt::IntersectsItemShape);
            for (int i = 0, n = colliding_items.size(); i < n; ++i)
            {
                RoadPlace *roadPlace = dynamic_cast<RoadPlace *>(colliding_items[i]);
                if(roadPlace != nullptr)
                    roadPlace->increaseDamageWeight(iTower->getPower() * iTower->getFiringRate());
            }

        }
        CastlePlace * castlePlace = dynamic_cast<CastlePlace*>(item);
        if(castlePlace != nullptr)
        {
            castle = castlePlace->pos();
        }
    }
    qDebug() << "towerPlaceCounter == " << towerPlaceCounter
             << "\ntowerCounter == " << towerCounter;
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
        if(!calculationPoints.contains(roadPlace->getWeight()))
            calculationPoints.insert(roadPlace->getWeight(), new QList<RoadPlace *>());
        calculationPoints[roadPlace->getWeight()]->push_back(roadPlace);
    }
    while( !calculationPoints.isEmpty() )
    {
        RoadPlace *currentRoadPlace = calculationPoints.first()->first();

        upperItem = level->itemAt(currentRoadPlace->pos().x(), currentRoadPlace->pos().y() + cellHeight, *qtransform);
        if(upperItem != nullptr)
        {
            listItems = upperItem->collidingItems();
            for(QGraphicsItem * item : listItems)
            {
                roadPlace =  dynamic_cast<RoadPlace *>(item);
                if(roadPlace != nullptr)
                    break;
            }
            if( roadPlace != nullptr)
            compareAndCalculationWeightWithCurrent(roadPlace, currentRoadPlace, &calculationPoints);
        }

        upperItem = (level->itemAt(currentRoadPlace->pos().x(), currentRoadPlace->pos().y() - cellHeight, *qtransform));
        if(upperItem != nullptr)
        {
            listItems = upperItem->collidingItems();
            for(QGraphicsItem * item : listItems)
            {
                roadPlace =  dynamic_cast<RoadPlace *>(item);
                if(roadPlace != nullptr)
                    break;
            }
            if( roadPlace != nullptr)
            compareAndCalculationWeightWithCurrent(roadPlace, currentRoadPlace, &calculationPoints);
        }

        upperItem = (level->itemAt(currentRoadPlace->pos().x() + cellWidth, currentRoadPlace->pos().y(), *qtransform));
        if(upperItem != nullptr)
        {
            listItems = upperItem->collidingItems();
            for(QGraphicsItem * item : listItems)
            {
                roadPlace =  dynamic_cast<RoadPlace *>(item);
                if(roadPlace != nullptr)
                    break;
            }
            if( roadPlace != nullptr)
            compareAndCalculationWeightWithCurrent(roadPlace, currentRoadPlace, &calculationPoints);
        }

        upperItem = (level->itemAt(currentRoadPlace->pos().x() - cellWidth, currentRoadPlace->pos().y(), *qtransform));
        if(upperItem != nullptr)
        {
            listItems = upperItem->collidingItems();
            for(QGraphicsItem * item : listItems)
            {
                roadPlace =  dynamic_cast<RoadPlace *>(item);
                if(roadPlace != nullptr)
                    break;
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
        if(roadPlace->getWeight() == roadPlace->BASEWEIGHT + roadPlace->getDamageWeight())
        {
            roadPlace->increaseWeight(currentRoadPlace->getWeight());
            if(!calculationPoints->contains(roadPlace->getWeight()))
                calculationPoints->insert(roadPlace->getWeight(), new QList<RoadPlace *>());
            (*calculationPoints)[roadPlace->getWeight()]->push_back(roadPlace);
        }else
        if(roadPlace->getWeight() - roadPlace->getDamageWeight() > currentRoadPlace->getWeight())
        {
            roadPlace->initializationWeight();
            roadPlace->increaseWeight(currentRoadPlace->getWeight());
            if(!calculationPoints->contains(roadPlace->getWeight()))
                calculationPoints->insert(roadPlace->getWeight(), new QList<RoadPlace *>());
            (*calculationPoints)[roadPlace->getWeight()]->push_back(roadPlace);
        }
    }
}

//void RoadFinder::calculationWay()
