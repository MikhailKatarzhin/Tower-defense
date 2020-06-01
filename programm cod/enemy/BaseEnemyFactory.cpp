#include "BaseEnemyFactory.h"
#include "enemy/enemy.h"
#include "enemy/enemyArmored.h"
#include "enemy/enemyRunner.h"
BaseEnemyFactory::BaseEnemyFactory()
{

}

IEnemy* BaseEnemyFactory::createEnemy(DenPlace * den,
                                      int wave,
                                      QGraphicsScene * level
                                      )
{
    QPointF startPos = den->pos();
    srand(time(0));
    switch (rand() % 3)
    {
    case 1:
        return new EnemyRunner(&startPos, wave, level);
    case 2:
        return new EnemyArmored(&startPos, wave, level);
    default:
        return new Enemy(&startPos, wave, level);
    }
}

QList<IEnemy*>* BaseEnemyFactory::createEnemies(QList<DenPlace *> *listDens,
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
