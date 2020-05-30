#include "BaseEnemyFactory.h"
#include "enemy/enemy.h"
#include "enemy/enemyRunner.h"
#include "enemy/enemyArmored.h"
BaseEnemyFactory::BaseEnemyFactory()
{

}

IEnemy* BaseEnemyFactory::createEnemy(Road _way, int wave, QGraphicsScene * level)
{
    srand(time(0));
    switch (rand() % 3)
    {
    case 0:
        return new Enemy(_way, wave, level);
    case 1:
        return new EnemyRunner(_way, wave, level);
    case 2:
        return new EnemyArmored(_way, wave, level);
    }
}
