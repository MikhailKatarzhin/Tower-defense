#pragma once
#include "map.h"
#include "road.h"

/**
 * @brief The ILevelParser class
 * This is the interface for providing map and main road after parsing level.
 */
class ILevelParser {
public:
    // The method for provide map.
    virtual Map& getMap() = 0;
    // The method for provide main road.
    virtual Road& getRoad() = 0;
};
