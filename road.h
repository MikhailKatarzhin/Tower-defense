#pragma once

#include <QPoint>
#include <QPolygon>

class Road
{
public:
    Road(QPoint = QPoint() , QPolygon = QPolygon());
    QPoint getStart();
    QPolygon getPoints();

private:
    QPoint start;
    QPolygon w_points;
};

