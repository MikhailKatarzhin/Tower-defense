#include "EasyEnemyFactory.h"
#include "enemy/enemy.h"
#include "enemy/enemyRunner.h"
#include "enemy/enemyArmored.h"
EasyEnemyFactory::EasyEnemyFactory()
{

}

IEnemy* EasyEnemyFactory::createEnemy(Road _way, int wave)
{
    srand(time(0));
    switch (rand() % 10)
    {
    case 1:
    case 3:
           return new EnemyRunner(_way, wave);
    case 2:
    case 4:
        return new EnemyArmored(_way, wave);
    default:
        return new Enemy(_way, wave);
    }
}
