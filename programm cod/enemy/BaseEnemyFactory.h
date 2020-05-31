#pragma once
#include "IEnemyFactory.h"

class BaseEnemyFactory : public IEnemyFactory
{
public:
    BaseEnemyFactory();
    IEnemy* createEnemy(DenPlace * den, int wave, QGraphicsScene * level) override;
    QList<IEnemy*>* createEnemies(QList<DenPlace *> *listDens, int wave, QGraphicsScene * level) override;
private:
    int counter = 0;
};
