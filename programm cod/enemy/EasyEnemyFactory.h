#pragma once
#include "IEnemyFactory.h"

class EasyEnemyFactory : public IEnemyFactory
{
public:
    EasyEnemyFactory();
    IEnemy* createEnemy(DenPlace * den, int wave, QGraphicsScene* level) override;
    QList<IEnemy*>* createEnemies(QList<DenPlace *> *listDens, int wave, QGraphicsScene * level) override;
private:
    int counter = 0;
};
