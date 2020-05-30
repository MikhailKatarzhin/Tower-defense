#pragma once
#include "IEnemyFactory.h"
#include <QGraphicsScene>

class BaseEnemyFactory : public IEnemyFactory
{
public:
    BaseEnemyFactory();
    IEnemy* createEnemy(Road _way, int wave, QGraphicsScene * level) override;
private:
    int counter = 0;
};
