#pragma once
#include "IEnemyFactory.h"

class BaseEnemyFactory : public IEnemyFactory
{
public:
    BaseEnemyFactory();
    IEnemy* createEnemy(Road _way, int wave) override;
private:
    int counter = 0;
};
