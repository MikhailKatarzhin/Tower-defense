#include "map.h"

Map::Map(int w, int h, int w_t, int h_t)
{
    map_w = w;
    map_h = h;
    tile_w = w_t;
    tile_h = h_t;
    lvlID = new QVector<QVector<int>>();
}

int Map::mapH() const
{
    return map_h;
}

int Map::mapW() const
{
    return map_w;
}

int Map::getTileW() const
{
    return tile_w;
}

int Map::getTileH() const
{
    return tile_h;
}

QVector<QVector<int> > &Map::getlvlID()
{
    return *lvlID;
}

Map::~Map()
{
    delete lvlID;
}


