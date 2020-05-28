#pragma once

#include <QGraphicsObject>

class IEnemy : public QGraphicsObject {
    Q_OBJECT
public:
    virtual int getPoint() = 0;
    virtual int getpassedWay() = 0;
    virtual int getSpeed() = 0;
    virtual void damaged(int) = 0;

public slots:
    virtual void move() = 0;
    virtual void stop() = 0;
signals:
    virtual void dead(int) = 0;
    virtual void win() = 0;
};

