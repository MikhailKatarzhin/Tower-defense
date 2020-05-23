#pragma once
#include <QtWidgets>
#include "tower.h"

/**
 * This is UI with towers changing.
 */
class TowerUI : public QWidget
{
    Q_OBJECT
public:
    TowerUI(QWidget *parent = nullptr);

public slots:
    void setUi(Tower* tower = nullptr);
    void checkUp();
    void setMoney(int);

private:
    QPushButton * upgrade;
    QPushButton * sell;
    QLabel * power;
    QLabel * radius;
    QLabel * level;
    int levelTower;
    int costUp;
    int money;
    int pow;
    int rad;
    int nextPow;
    int nextRad;
    int nextCost;
};

