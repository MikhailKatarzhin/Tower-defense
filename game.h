#pragma once

#include <QtWidgets>
#include <QtMultimedia>
#include "level.h"
#include "buildingui.h"
#include "towerui.h"
#include "hud.h"
#include "enemy/IEnemyFactory.h"
#include "level/ILevelParser.h"

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

    void selectTower(Tower *tower = nullptr);
    void upgradeTower();

private slots:
    void killEnemy(int = 0);
    void lootEnemy(int);

private:
    IEnemyFactory *enemyFactory;
    Tower * selectedTower;
    QMediaPlayer *music;
    ILevelParser*  levelParser;
    QTimer * spawnTimer;
    TowerUI * towerUI;
    Level * level;
    HUD* hud;

    BuildingUI  build_ui;
    Road road;

    int enemies;
    int currentEnemy;
    int wave;
    int lifes;
    int money;
};


