#include "HardEnemyFactory.h"
#include "enemy/enemyRunner.h"
#include "enemy/enemyArmored.h"
HardEnemyFactory::HardEnemyFactory()
{

}

IEnemy* HardEnemyFactory::createEnemy(DenPlace * den,
                                      int wave,
                                      QGraphicsScene * level
                                      )
{
    QPointF startPos = den->pos();
    srand(time(0));
    switch (rand() % 10)
    {
    case 1:
    case 3:
    case 2:
    case 4:
        return new EnemyRunner(&startPos, wave, level);
    default:
        return new EnemyArmored(&startPos, wave, level);
    }
}

QList<IEnemy*>* HardEnemyFactory::createEnemies(QList<DenPlace *> *listDens,
                                                int wave,
                                                QGraphicsScene * level
                                                )
{
    QList<IEnemy*> * listEmenies = new QList<IEnemy*>();
    for(DenPlace * currentDen : *listDens)
    {
        listEmenies->push_back(createEnemy(currentDen, wave, level));
    }
    return listEmenies;
}
