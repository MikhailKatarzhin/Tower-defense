#pragma once
#include <QtMultimedia>
#include <QtWidgets>
#include "enemy/IEnemyFactory.h"
#include "hud.h"
#include "level.h"
#include "level/ILevelParser.h"
#include "roadFinder/RoadFinder.h"
#include "tower/buildingui.h"
#include "tower/towerui.h"

class Game : public QWidget
{
    Q_OBJECT
public:
    Game(
            QWidget* parent,
            IEnemyFactory *enemyFactory,
            ILevelParser* levelParser
    );
    void gameOver();
    void win();

signals:
    void stopEnemy();
    void change_lifes(int);
    void change_wave(int);
    void changeMoney(int);
    void change_enemy(int);
    void btn_wave(bool);

public slots:
    void createEnemies();
    void spawnEnemy();
    void wastelifes();
    void reduceMoney(int);
    void sellTower();

    void selectTower(ITower *tower = nullptr);
    void upgradeTower();

private slots:
    void killEnemy(int = 0);

private:
    RoadFinder * roadFinder;
    IEnemyFactory *enemyFactory;
    ITower * selectedTower;
    QMediaPlayer *music;
    ILevelParser*  levelParser;
    QTimer * spawnTimer;
    TowerUI * towerUI;
    Level * level;
    HUD* hud;

    BuildingUI  build_ui;

    QList<DenPlace *> * listDens;
    int enemies;
    int currentEnemy;
    int wave;
    int lifes;
    int money;
};


