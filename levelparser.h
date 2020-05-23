#pragma once
#include <QtWidgets>
#include "map.h"
#include "road.h"

class LevelParser
{
public:
    LevelParser(QString);
    ~LevelParser();
    Map &getMap();
    Road &getRoad();
private:
    QFile* f_XML;
    Map* map;
    Road* road;
    QPoint start;
    QPolygon& parseRoad(QString);
    void parseTile(QString);
};
