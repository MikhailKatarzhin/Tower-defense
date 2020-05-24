#pragma once
#include "IEnemyFactory.h"

class EasyEnemyFactory : public IEnemyFactory
{
public:
    EasyEnemyFactory();
    IEnemy* createEnemy(Road _way, int wave) override;
private:
    int counter = 0;
};
