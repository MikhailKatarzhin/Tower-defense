#pragma once
#include <QGraphicsScene>

class RoadFinder {
public:
    RoadFinder(
            QGraphicsScene* level,
            int cellHeight,
            int cellWidth
    );
    void test();
private:
    int cellWidth;
    int cellHeight;
    QGraphicsScene* level;
};
