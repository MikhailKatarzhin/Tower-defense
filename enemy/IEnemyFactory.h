#pragma once
#include "road.h"
#include "enemy/IEnemy.h"

class IEnemyFactory {
public:
    virtual IEnemy* createEnemy(Road _way, int wave) = 0;
};
