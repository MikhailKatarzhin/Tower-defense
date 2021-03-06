#pragma once
#include <QtWidgets>
#include "tower/ITower.h"

/**
 * This is UI with towers changing.
 */
class TowerUI : public QWidget
{
    Q_OBJECT
public:
    TowerUI(QWidget *parent = nullptr);

public slots:
    void setUi(ITower* tower = nullptr);
    void checkUp();
    void setMoney(int);

private:
    QPushButton * upgrade;
    QPushButton * sell;
    QLabel * power;
    QLabel * radius;
    QLabel * level;
    QLabel * firingRate;
    int levelTower;
    int costUp;
    int money;
};

