#include "game.h"

#include "enemy/IEnemy.h"

Game::Game(QWidget *parent /*difficult */)
{
    // switch difficult
    // emenyFacrory = HardFactory // for example

    //****Background image****//
    QPalette pal;
    pal.setBrush(this->backgroundRole(), QBrush(QImage(":/res/images/Fon.jpg")));
    this->setPalette(pal);
    this->setAutoFillBackground(true);
    //********************//

    adjustSize();
    setWindowTitle("Tower Defense");

    //****Background music****//
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/res/music/back.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    music = new QMediaPlayer(this);
    music->setPlaylist(playlist);
    music->setVolume(25);
    music->play();
    //********************//

    //********Font********//
    int id = QFontDatabase::addApplicationFont(":/res/fonts/CyrilicOld.TTF");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont f(family);
    f.setPixelSize(16);
    setFont(f);
    //********************//

    //****Initialisation****//
    parser = new LevelParser(":/res/maps/map.tmx");
    towerUI = new TowerUI(this);
    hud = new HUD(this);

    road = parser->getRoad();
    level = new Level(parser->getMap(), this);

    waves = {10, 25, 15, 30, 15};

    selectedTower = nullptr;
    wave = 0;
    enemies = waves[0];
    currentEnemy = 0;
    stepTimer = 10;
    money = 120;
    //********************//


    //****SIGNALS****//
    connect(this, SIGNAL(ch_money(int)), &build_ui, SLOT(setPossible(int)));
    connect(this, SIGNAL(ch_money(int)), towerUI, SLOT(setMoney(int)));
    connect(level,SIGNAL(setUI(Tower*)), this, SLOT(selectTower(Tower*)));
    connect(level, SIGNAL(successBuild(int)), this, SLOT(reduceMoney(int)));
    connect(&build_ui, SIGNAL(build()), level, SLOT(createTower()));

    emit ch_enemy(enemies);
    emit ch_stepTimer(stepTimer);
    emit ch_money(money);
    emit ch_wave(wave);
    //********************//

    //****View****//
    QGraphicsView * q = new QGraphicsView(this);
    q->setScene(level);
    q->setMouseTracking(true);
    q->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    q->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    q->setRenderHint(QPainter::Antialiasing, false);
    //********************//

    //****Layout****//
    QVBoxLayout * v_box = new QVBoxLayout();
    QHBoxLayout * h_box = new QHBoxLayout();

    h_box->addLayout(v_box);
    v_box->addWidget(hud);
    v_box->addWidget(towerUI);
    h_box->setSizeConstraint(QLayout::SetFixedSize);
    h_box->addWidget(q);
    h_box->addWidget(&build_ui);
    v_box->setSizeConstraint(QLayout::SetFixedSize);
    this->setLayout(h_box);
    //********************//
}

void Game::gameOver()
{

    QMessageBox * restart = new QMessageBox (QMessageBox::Question,"GameOver(","Do you want to restart level?", QMessageBox::Yes| QMessageBox::No);
    music->stop();
    spawnTimer->stop();
    spawnTimer->disconnect();

    emit stopEnemy();

    int choice = restart->exec();

    if(choice == QMessageBox::Yes)
    {
        Game * game  = new Game();
        this->close();
        game->show();
    }
    else
    {
        close();
    }
}

void Game::win()
{
    QMessageBox * restart = new QMessageBox (QMessageBox::Question, "You are Winner!!!","Do you want to play more?", QMessageBox::Yes| QMessageBox::No);
    music->stop();
    int choice = restart->exec();

    if(choice == QMessageBox::Yes)
    {
        this->close();
        Game * game  = new Game();
        game->show();
    }
    else
    {
        close();
    }
}

void Game::wastestepTimer()
{
    --stepTimer;
    --enemies;

    if(enemies == 0)
    {
        waves.pop_front();

        if (!waves.empty())
        {
            ++wave;
            enemies = waves[0];
            emit ch_wave(wave);
            emit btn_wave(true);
        }
        else win();
    }
    if (stepTimer <= 0  ) gameOver();

    emit ch_stepTimer(stepTimer);
    emit ch_enemy(enemies);

}

void Game::reduceMoney(int cash)
{
    money-=cash;
    emit ch_money(money);
}

void Game::selectTower(Tower * tower)
{
    selectedTower = tower;
    towerUI->setUi(selectedTower);
}

void Game::upgradeTower()
{
    money-=selectedTower->getCost(selectedTower->getLevel());
    selectedTower->upgrade();
    emit ch_money(money);
}

void Game::cellTower()
{
    if(selectedTower)
    {
        money+=selectedTower->getCost(selectedTower->getLevel())/2;
        level->createPlace(selectedTower->scenePos());
        emit ch_money(money);
        level->clearSelection();
        level->removeItem(selectedTower);
        delete selectedTower;
        selectedTower = nullptr;
        towerUI->setUi();
    }
}

void Game::createEnemies()
{
    emit btn_wave(false);
    spawnTimer = new  QTimer();
    connect(spawnTimer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
    spawnTimer->start(800); // todo can set enemy creation duration
}

void Game::spawnEnemy()
{
    // IEnemy

    // random from 1 to 10

    // IEnemy
    // FlyEnemy::IEnemy
    // RunEnemy::IEnemy
    // GlassEnemy::Ibn

    // IEnemy ememy;
    // if 1..5 { enemy = new FlyEnemy} else { RuneEnemy }


    IEnemy *enemy = new Enemy(road, wave); // EnemyFabric

//  IEnemy *enemy = enemyFactory.createEnemy();

    level->addItem(enemy);
    ++currentEnemy;

    connect(this, SIGNAL(stopEnemy()), enemy, SLOT(stop()));
    connect(enemy, SIGNAL(win()), this, SLOT(wastestepTimer()));
    connect(enemy, SIGNAL(dead(int)), this, SLOT(killEnemy(int)));

    if (currentEnemy == waves[0])
    {
        spawnTimer->disconnect();
        currentEnemy = 0;
    }
}

void Game::lootEnemy(int prize)
{
    money += prize;
    --enemies;

    if(enemies == 0)
    {
        waves.pop_front();

        if (!waves.empty())
        {
            ++wave;
            enemies = waves[0];
            emit ch_wave(wave);
            emit btn_wave(true);
        }
        else {
            emit ch_enemy(enemies);
            win();
        }
    }
    emit ch_enemy(enemies);
    emit ch_money(money);

}

void Game::killEnemy(int prize)
{
    delete sender();
    lootEnemy(prize);

}



