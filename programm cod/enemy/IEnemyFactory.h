#pragma once
#include <QGraphicsScene>
#include <QList>
#include "enemy/IEnemy.h"
#include "places/denPlace.h"

class IEnemyFactory {
public:
    virtual IEnemy* createEnemy(DenPlace * den, int wave, QGraphicsScene * level) = 0;
    virtual QList<IEnemy*>* createEnemies(QList<DenPlace *> *listDens, int wave, QGraphicsScene * level) = 0;
};
