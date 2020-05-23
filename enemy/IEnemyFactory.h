#pragma once
#include <memory>

#include "IEnemy.h"

class IEnemyFactory {
public:
    virtual std::shared_ptr<IEnemy> createEnemy();
};
