#include "level.h"
#include "tower/tower.h"

Level::Level(Map & _map, QWidget *parent)
{
    map = _map;
    build_curs = nullptr;
    building = false;
    renderMap();
}

void Level::createPlace(QPointF point)
{
    TowerPlace * place = new TowerPlace();
    place->setPos(point);
    addItem(place);
}

void Level::renderMap()
{
    if (nullptr == roadFinder)
        roadFinder = new RoadFinder(
                    this,
                    this->map.getTileH(),
                    this->map.getTileW()
        );
    QVector<QVector<int>> sc_lvl = map.getlvlID();

    lvl_h = map.mapH()*map.getTileH();
    lvl_w = map.mapW()*map.getTileW();

    setSceneRect(0,0, lvl_w, lvl_h);

    for(int i = 0; i < map.mapH(); ++i)
    {
        for (int j =0 ; j < map.mapW(); ++j)
        {
            switch (sc_lvl[i][j])
            {
            case 1 :
            {
                TowerPlace * tplace = new TowerPlace();
                tplace->setPos(j*map.getTileW(), i*map.getTileH());
                addItem(tplace);
                break;
            }
            case 2:
            {
                RoadPlace * rplace = new RoadPlace();
                rplace->setPos(j*map.getTileW(), i*map.getTileH());
                addItem(rplace);
                break;
            }
            case 3:
            {
                RoadPlace * rplace = new RoadPlace();
                rplace->setPos(j*map.getTileW(), i*map.getTileH());
                addItem(rplace);

                DenPlace * dplace = new DenPlace();
                dplace->setPos(j*map.getTileW(), i*map.getTileH());
                addItem(dplace);
                break;
            }
            case 4:
            {
                QGraphicsPixmapItem * sc_obj = new QGraphicsPixmapItem (QPixmap(":/res/images/Blue.png"));
                sc_obj->setPos(j*map.getTileW(), i*map.getTileH());
                addItem(sc_obj);
                break;
            }
            case 5:
            {
                RoadPlace * rplace = new RoadPlace();
                rplace->setPos(j*map.getTileW(), i*map.getTileH());
                addItem(rplace);

                CastlePlace * cplace = new CastlePlace();
                cplace->setPos(j*map.getTileW(), i*map.getTileH());
                addItem(cplace);
                break;
            }
            }
        }
    }
}

void Level::createTower(ITower * tower)
{
    this->tower = tower;
    if (build_curs) removeItem(build_curs);
    build_curs = new QGraphicsPixmapItem();
    build_curs->setPixmap(*(tower->getSprite()));
    build_curs->hide();
    addItem(build_curs);
    building = true;
}


void Level::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (build_curs)
    {
        build_curs->show();
        build_curs->setPos(event->scenePos().x()-16,event->scenePos().y()-16 );
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void Level::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    TowerPlace * place = dynamic_cast<TowerPlace*>(items(event->scenePos()).last());
    ITower * tow = dynamic_cast<ITower*>(items(event->scenePos()).last());
    clearSelection();

    if(event->button() == Qt::LeftButton)
    {
        if (building == true && place != nullptr)
        {
            ITower * tower = this->tower;
            this->tower = nullptr;
            tower->setPos(place->scenePos());
            this->addItem(tower);
            this->removeItem(place);

            this->removeItem(build_curs);
            building = false;

            clearSelection();

            tower->setSelected(true);
            emit setUI(tower);
            emit successBuild(tower->getCost());
            return;
        }

        if (building == true && place == nullptr)
        {
            QGraphicsScene::mousePressEvent(event);
            return;
        }

        if(tow != nullptr && (!tow->isSelected()))
        {
            clearSelection();
            tow->setSelected(true);
            emit setUI(tow);
            return;
        }
        emit setUI(nullptr);
        return;
    }

    if (event->button() == Qt::RightButton)
    {
        if (building == true && build_curs->isVisible())
        {
            clearSelection();
            removeItem(build_curs);
            building = false;
        }
        QGraphicsScene::mousePressEvent(event);
    }
}

