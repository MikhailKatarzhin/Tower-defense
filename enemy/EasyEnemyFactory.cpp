#include "EasyEnemyFactory.h"
#include "enemy/enemy.h"
#include "enemy/enemyRunner.h"
#include "enemy/enemyArmored.h"
EasyEnemyFactory::EasyEnemyFactory()
{

}

IEnemy* EasyEnemyFactory::createEnemy(DenPlace * den,
                                      int wave,
                                      QGraphicsScene * level
                                      )
{
    QPointF startPos = den->pos();
    srand(time(0));
    switch (rand() % 15)
    {
    case 1:
    case 3:
           return new EnemyRunner(&startPos, wave, level);
    case 2:
    case 4:
        return new EnemyArmored(&startPos, wave, level);
    default:
        return new Enemy(&startPos, wave, level);
    }
}

QList<IEnemy*>* EasyEnemyFactory::createEnemies(QList<DenPlace *> *listDens,
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
