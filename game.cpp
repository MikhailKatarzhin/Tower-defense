#include "game.h"
#include "enemy/IEnemy.h"

Game::Game(QWidget *parent , IEnemyFactory *enemyFactory)
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
    this->enemyFactory = enemyFactory;
    parser = new LevelParser(":/res/maps/map.tmx");
    towerUI = new TowerUI(this);
    hud = new HUD(this);

    road = parser->getRoad();
    level = new Level(parser->getMap(), this);

    selectedTower = nullptr;
    wave = 0;
    enemies = 10 + wave * 2;
    currentEnemy = 0;
    lifes = 10;
    money = 100;
    //********************//


    //****SIGNALS****//
    connect(this, SIGNAL(changeMoney(int)), &build_ui, SLOT(setPossible(int)));
    connect(this, SIGNAL(changeMoney(int)), towerUI, SLOT(setMoney(int)));
    connect(level,SIGNAL(setUI(Tower*)), this, SLOT(selectTower(Tower*)));
    connect(level, SIGNAL(successBuild(int)), this, SLOT(reduceMoney(int)));
    connect(&build_ui, SIGNAL(build()), level, SLOT(createTower()));

    emit change_enemy(enemies);
    emit change_lifes(lifes);
    emit changeMoney(money);
    emit change_wave(wave);
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
        this->close();
        Game * game  = new Game(nullptr, this->enemyFactory);
        game->show();
    }
    else
    {
        close();
    }
}

void Game::wastelifes()
{
    --lifes;
    --enemies;

    if(enemies == 0)
    {
        ++wave;
         enemies = 10 + wave * 2;
        emit change_wave(wave);
        emit btn_wave(true);
    }
    if (lifes <= 0  ) gameOver();

    emit change_lifes(lifes);
    emit change_enemy(enemies);

}

void Game::reduceMoney(int cash)
{
    money-=cash;
    emit changeMoney(money);
}

void Game::selectTower(Tower * tower)
{
    selectedTower = tower;
    towerUI->setUi(selectedTower);
}

void Game::upgradeTower()
{
    money-=selectedTower->getCost();
    selectedTower->upgrade();
    emit changeMoney(money);
}

void Game::sellTower()
{
    if(selectedTower)
    {
        money+=selectedTower->getSalePrice();
        level->createPlace(selectedTower->scenePos());
        emit changeMoney(money);
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
    IEnemy *enemy = enemyFactory->createEnemy(road, wave);

    level->addItem(enemy);
    ++currentEnemy;

    connect(this, SIGNAL(stopEnemy()), enemy, SLOT(stop()));
    connect(enemy, SIGNAL(win()), this, SLOT(wastelifes()));
    connect(enemy, SIGNAL(dead(int)), this, SLOT(killEnemy(int)));

    if (currentEnemy == 10 + wave * 2)
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
        ++wave;
        ++lifes;
        enemies = 10 + wave * 2;
        emit change_wave(wave);
        emit btn_wave(true);
    }
    emit change_enemy(enemies);
    emit changeMoney(money);

}

void Game::killEnemy(int prize)
{
    delete sender();
    lootEnemy(prize);

}



