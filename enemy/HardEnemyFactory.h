#pragma once
#include "IEnemyFactory.h"
#include <QGraphicsScene>

class HardEnemyFactory : public IEnemyFactory
{
public:
    HardEnemyFactory();
    IEnemy* createEnemy(Road _way, int wave, QGraphicsScene* level) override;
private:
    int counter = 0;
};
