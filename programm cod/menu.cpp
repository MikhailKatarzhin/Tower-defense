#include "enemy/BaseEnemyFactory.h"
#include "enemy/EasyEnemyFactory.h"
#include "enemy/HardEnemyFactory.h"
#include "game.h"
#include "level/TextFileLevelParser.h"
#include "level/XmlLevelParser.h"
#include "menu.h"

Menu::Menu(QWidget *parent)
{
    QVBoxLayout * v_box = new QVBoxLayout ();
    this->setLayout(v_box);
    setWindowTitle("Tower Defense");
    setFixedSize(300,300);
    easyGame.setText("&Easy game");
    baseGame.setText("&Base game");
    hardGame.setText("&Hard game");
    quit.setText("&Exit");
    v_box->addWidget(&easyGame);
    v_box->addWidget(&baseGame);
    v_box->addWidget(&hardGame);
    v_box->addWidget(&quit);
    connect(&easyGame, SIGNAL(clicked()), this, SLOT(chooseEasy()));
    connect(&baseGame, SIGNAL(clicked()), this, SLOT(chooseBase()));
    connect(&hardGame, SIGNAL(clicked()), this, SLOT(chooseHard()));
    connect(&quit, SIGNAL(clicked()), this, SLOT(close()));
    Q_UNUSED(parent);
}

void Menu::chooseLvl(IEnemyFactory *enemyFactory)
{
    Game * game  = new Game(nullptr, enemyFactory, new TextFileLevelParser(":/res/maps/map"));
    this->close();
    game->show();
}
void Menu::chooseEasy()
{
    this->chooseLvl(new EasyEnemyFactory());
}
void Menu::chooseBase()
{
    this->chooseLvl(new BaseEnemyFactory());
}
void Menu::chooseHard()
{
    this->chooseLvl(new HardEnemyFactory());
}
