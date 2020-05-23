#ifndef ILEVELPARSER_H
#define ILEVELPARSER_H

#include "map.h"
#include "road.h"

class ILevelParser {
public:
    virtual Map& getMap() = 0;
    virtual Road& getRoad() = 0;
};

#endif // ILEVELPARSER_H
