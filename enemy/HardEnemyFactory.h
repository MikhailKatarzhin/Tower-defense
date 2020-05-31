#pragma once
#include "IEnemyFactory.h"

class HardEnemyFactory : public IEnemyFactory
{
public:
    HardEnemyFactory();
    IEnemy* createEnemy(DenPlace * den, int wave, QGraphicsScene* level) override;
    QList<IEnemy*>* createEnemies(QList<DenPlace *> *listDens, int wave, QGraphicsScene * level) override;
private:
    int counter = 0;
};
