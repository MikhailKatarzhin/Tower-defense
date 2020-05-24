#include "HardEnemyFactory.h"
#include "enemy/enemyRunner.h"
#include "enemy/enemyArmored.h"
HardEnemyFactory::HardEnemyFactory()
{

}

IEnemy* HardEnemyFactory::createEnemy(Road _way, int wave)
{
    srand(time(0));
    switch (rand() % 10)
    {
    case 1:
    case 3:
    case 2:
    case 4:
        return new EnemyRunner(_way, wave);
    default:
        return new EnemyArmored(_way, wave);
    }
}
