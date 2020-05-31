#pragma once
#include <QObject>
#include <QtWidgets>
#include "enemy/IEnemyFactory.h"

class Menu : public QWidget
{
    Q_OBJECT

public:
    Menu(QWidget * parent  = nullptr);
public slots:
    void chooseEasy();
    void chooseBase();
    void chooseHard();
private:
    void chooseLvl(IEnemyFactory *enemyFactory);
    QPushButton  easyGame;
    QPushButton  baseGame;
    QPushButton  hardGame;
    QPushButton  quit;

};


