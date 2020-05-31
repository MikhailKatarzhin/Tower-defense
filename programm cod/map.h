#pragma once
#include <QVector>

class Map
{
public:
    Map(int = 0 , int = 0, int = 0 , int = 0);
    int getTileW() const;
    int getTileH() const;
    QVector<QVector<int> > &getlvlID();
    ~Map();
    int mapH() const;
    int mapW() const;

private:
    QVector<QVector<int>>* lvlID;
    int tile_w;
    int tile_h;
    int map_w;
    int map_h;


};

