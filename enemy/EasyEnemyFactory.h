#pragma once
#include "IEnemyFactory.h"
#include <QGraphicsScene>

class EasyEnemyFactory : public IEnemyFactory
{
public:
    EasyEnemyFactory();
    IEnemy* createEnemy(Road _way, int wave, QGraphicsScene* level) override;
private:
    int counter = 0;
};
