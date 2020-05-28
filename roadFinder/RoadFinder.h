#ifndef ROADFINDER_H
#define ROADFINDER_H
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

#endif // ROADFINDER_H
