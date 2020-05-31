#pragma once
#include "enemy/IEnemy.h"
#include "places/denPlace.h"
#include <QGraphicsScene>
#include <QList>

class IEnemyFactory {
public:
    virtual IEnemy* createEnemy(DenPlace * den, int wave, QGraphicsScene * level) = 0;
    virtual QList<IEnemy*>* createEnemies(QList<DenPlace *> *listDens, int wave, QGraphicsScene * level) = 0;
};
