#include "game.h"
#include "enemy/IEnemy.h"
#include "roadFinder/RoadFinder.h"

Game::Game(QWidget *parent , IEnemyFactory *enemyFactory, ILevelParser* levelParser)
{

    //****Background image****//
    QPalette pal;
    pal.setBrush(this->backgroundRole(), QBrush(QImage(":/res/images/Fon.jpg")));
    this->setPalette(pal);
    this->setAutoFillBackground(true);
    //********************//

    adjustSize();
    setWindowTitle("Tower Defense");
    move(20,20);

    //****Background music****//
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/res/music/back.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    music = new QMediaPlayer(this);
    music->setPlaylist(playlist);
    music->setVolume(1);
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
    this->levelParser = levelParser;
    this->enemyFactory = enemyFactory;
    towerUI = new TowerUI(this);
    hud = new HUD(this);

    level = new Level( levelParser->getMap(), this);
    listDens = new QList<DenPlace *>();
    QList<QGraphicsItem*> listOfItems = level->items();
    for (QGraphicsItem* item : listOfItems)
    {
        DenPlace * denPlace = dynamic_cast<DenPlace*>(item);
        if(denPlace != nullptr)
        {
            listDens->push_back(denPlace);
        }
    }
    RoadFinder *roadFinder = new RoadFinder(
                level,
                levelParser->getMap().getTileH(),
                levelParser->getMap().getTileW()
    );
    emit roadFinder->calculationMap();

    selectedTower = nullptr;
    wave = 0;
    enemies = 0;
    currentEnemy = 0;
    lifes = 15;
    money = 250;
    //********************//


    //****SIGNALS****//
    connect(this, SIGNAL(changeMoney(int)), &build_ui, SLOT(setPossible(int)));
    connect(this, SIGNAL(changeMoney(int)), towerUI, SLOT(setMoney(int)));
    connect(level,SIGNAL(setUI(ITower*)), this, SLOT(selectTower(ITower*)));
    connect(level, SIGNAL(successBuild(int)), this, SLOT(reduceMoney(int)));
    connect(&build_ui, SIGNAL(build(ITower*)), level, SLOT(createTower(ITower*)));

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

    QMessageBox * restart = new QMessageBox (QMessageBox::Question,"GameOver","Do you want to restart level?", QMessageBox::Yes| QMessageBox::No);
    music->stop();
    spawnTimer->stop();
    spawnTimer->disconnect();

    emit stopEnemy();

    int choice = restart->exec();

    if(choice == QMessageBox::Yes)
    {
        Game * game  = new Game(nullptr, this->enemyFactory, this->levelParser);
        this->close();
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
    emit change_lifes(lifes);
    --enemies;
    emit change_enemy(enemies);
    if (lifes <= 0  ) gameOver();
}

void Game::reduceMoney(int cash)
{
    money-=cash;
    emit changeMoney(money);
}

void Game::selectTower(ITower * tower)
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
    ++wave;
    emit change_wave(wave);
    ++lifes;
    emit change_lifes(lifes);
    money += lifes * wave * 5;
    emit changeMoney(money);
    emit btn_wave(false);
    spawnTimer = new  QTimer();
    connect(spawnTimer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
    if(wave < 100)
        spawnTimer->start(1000 - 9 * wave);
    else
        spawnTimer->start(100);

}

void Game::spawnEnemy()
{
    QList<IEnemy *> * listEnemies = enemyFactory->createEnemies(listDens, wave, level);
    for(IEnemy * enemy : *listEnemies)
    {
        level->addItem(enemy);
        ++currentEnemy;
        ++enemies;
        emit change_enemy(enemies);
        connect(this, SIGNAL(stopEnemy()), enemy, SLOT(stop()));
        connect(enemy, SIGNAL(win()), this, SLOT(wastelifes()));
        connect(enemy, SIGNAL(dead(int)), this, SLOT(killEnemy(int)));

        if (currentEnemy >= 10 + wave * 2)
        {
            spawnTimer->disconnect();
            currentEnemy = 0;
            emit btn_wave(true);
        }
    }
}

void Game::killEnemy(int prize)
{
    delete sender();
    money += prize;
    --enemies;
    emit change_enemy(enemies);
    emit changeMoney(money);
}



