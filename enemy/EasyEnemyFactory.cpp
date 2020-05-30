#include "EasyEnemyFactory.h"
#include "enemy/enemy.h"
#include "enemy/enemyRunner.h"
#include "enemy/enemyArmored.h"
EasyEnemyFactory::EasyEnemyFactory()
{

}

IEnemy* EasyEnemyFactory::createEnemy(Road _way, int wave, QGraphicsScene * level)
{
    srand(time(0));
    switch (rand() % 15)
    {
    case 1:
    case 3:
           return new EnemyRunner(_way, wave, level);
    case 2:
    case 4:
        return new EnemyArmored(_way, wave, level);
    default:
        return new Enemy(_way, wave, level);
    }
}
