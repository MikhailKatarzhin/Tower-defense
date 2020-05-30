#pragma once
#include "road.h"
#include "enemy/IEnemy.h"
#include <QGraphicsScene>

class IEnemyFactory {
public:
    virtual IEnemy* createEnemy(Road _way, int wave, QGraphicsScene * level) = 0;
};
