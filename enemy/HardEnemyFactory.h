#pragma once
#include "IEnemyFactory.h"

class HardEnemyFactory : public IEnemyFactory
{
public:
    HardEnemyFactory();
    IEnemy* createEnemy(Road _way, int wave) override;
private:
    int counter = 0;
};
