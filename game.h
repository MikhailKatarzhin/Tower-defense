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
    void ch_stepTimer(int);
    void ch_wave(int);
    void ch_money(int);
    void ch_enemy(int);
    void btn_wave(bool);

public slots:
    void createEnemies();
    void spawnEnemy();
    void wastestepTimer();
    void reduceMoney(int);
    void cellTower();

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

    QVector<int> waves;

    int enemies;
    int currentEnemy;
    int wave;
    int Lifes;
    int money;
};


