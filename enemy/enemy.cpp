#include "enemy/enemy.h"
#include "places/castlePlace.h"
#include <QGraphicsItem>
#include <QtDebug>

Enemy::Enemy(Road _way, int wave, QGraphicsScene * level) : way(_way)
{
    this->level = level;
    passedWay   = 0;
    sprite      = new QPixmap(":/res/images/Enemy.png");
    max_hp      = 100 * pow(1.15, wave);
    current_hp  = max_hp;
    speed       = 500 * pow(1.005, wave);
    armor       = 3 * pow(1.1, wave);
    point       = 1;
    prize       = 5 * pow(1.1, wave);
    this->setPos(way.getStart().x(),
                 way.getStart().y());


    QPointF tmpPoint;
    QList<QGraphicsItem *> listItems;
    tmpPoint.setX(this->x());
    tmpPoint.setY(this->y());
    listItems = level->items(tmpPoint);
    for(QGraphicsItem * item : listItems)
    {
        nextRoadPlace =  dynamic_cast<RoadPlace *>(item);
        if(nextRoadPlace != nullptr)
            break;
    }

    lifes = new QTimer();
    connect(lifes, SIGNAL(timeout()), this, SLOT(move()));
    lifes->start(10000 / speed);
}

void Enemy::move()
{
    qDebug()<<"x:\t"<<this->pos().x() << "\ty:\t" << this->pos().y();
    QPointF tmpPoint;
    QList<QGraphicsItem *> listItems;


    tmpPoint.setX(this->x());
    tmpPoint.setY(this->y());
    listItems = level->items(tmpPoint);
    RoadPlace *currentRoadPlace = nullptr;
    for(QGraphicsItem * item : listItems)
    {
        currentRoadPlace =  dynamic_cast<RoadPlace *>(item);
        if(currentRoadPlace != nullptr)
            break;
    }
    if( currentRoadPlace == nullptr )
        return;


    if( this->x() == nextRoadPlace->x() && this->y() == nextRoadPlace->y())
    {
        qDebug()<<"x:\t"<< this->x() << "\ty:\t" << this->y();

        tmpPoint.setX(this->x());
        tmpPoint.setY(this->y() - currentRoadPlace->getSprite()->height());
        listItems = level->items(tmpPoint);
        RoadPlace *upRoadPlace = nullptr;
        for(QGraphicsItem * item : listItems)
        {
            upRoadPlace =  dynamic_cast<RoadPlace *>(item);
            if(upRoadPlace != nullptr)
                break;
        }


        tmpPoint.setX(this->x());
        tmpPoint.setY(this->y() + currentRoadPlace->getSprite()->height());
        listItems = level->items(tmpPoint);
        RoadPlace *downRoadPlace = nullptr;
        for(QGraphicsItem * item : listItems)
        {
            downRoadPlace =  dynamic_cast<RoadPlace *>(item);
            if(downRoadPlace != nullptr)
                break;
        }


        tmpPoint.setX(this->x() + currentRoadPlace->getSprite()->width());
        tmpPoint.setY(this->y());
        listItems = level->items(tmpPoint);
        RoadPlace *rightRoadPlace = nullptr;
        for(QGraphicsItem * item : listItems)
        {
            rightRoadPlace =  dynamic_cast<RoadPlace *>(item);
            if(rightRoadPlace != nullptr)
                break;
        }


        tmpPoint.setX(this->x() - currentRoadPlace->getSprite()->width());
        tmpPoint.setY(this->y());
        listItems = level->items(tmpPoint);
        RoadPlace *leftRoadPlace = nullptr;
        for(QGraphicsItem * item : listItems)
        {
            leftRoadPlace =  dynamic_cast<RoadPlace *>(item);
            if(leftRoadPlace != nullptr)
                break;
        }

        RoadPlace *minRoadPlace = currentRoadPlace;
        if(upRoadPlace != nullptr)
            if(upRoadPlace->getWeight() < minRoadPlace->getWeight())
                minRoadPlace = upRoadPlace;
        if(downRoadPlace != nullptr)
            if(downRoadPlace->getWeight() < minRoadPlace->getWeight())
                minRoadPlace = downRoadPlace;
        if(rightRoadPlace != nullptr)
            if(rightRoadPlace->getWeight() < minRoadPlace->getWeight())
                minRoadPlace = rightRoadPlace;
        if(leftRoadPlace != nullptr)
            if(leftRoadPlace->getWeight() < minRoadPlace->getWeight())
                minRoadPlace = leftRoadPlace;
        nextRoadPlace = minRoadPlace;
    }

    int dy = (this->y() < nextRoadPlace->y() ? 1 : (this->y() > nextRoadPlace->y() ? -1 : 0));
    int dx = (this->x() < nextRoadPlace->x() ? 1 : (this->x() > nextRoadPlace->x() ? -1 : 0));

    moveBy(dx,dy);
    passedWay += sqrt(pow(dx,2) + pow(dy, 2));

    tmpPoint.setX(this->x());
    tmpPoint.setY(this->y());
    listItems = this->collidingItems();
    CastlePlace *castlePlace =nullptr;
    for(QGraphicsItem * item : listItems)
    {
        castlePlace =  dynamic_cast<CastlePlace *>(item);
        if(castlePlace != nullptr)
        {
            lifes->stop();
            lifes->disconnect();
            emit win();
            delete this;
            break;
        }
    }
}

void Enemy::stop()
{
    lifes->stop();
    lifes->disconnect();
}

int Enemy::getPoint()
{
    return point;
}

int Enemy::getpassedWay()
{
    return  passedWay;
}
int Enemy::getSpeed()
{
    return speed;
}
int Enemy::getArmor()
{
    return  armor;
}

void Enemy::damaged(int damage)
{
    damage -= armor;
    if(damage >= 0)
        current_hp -=damage;

    if(current_hp <= 0 )
    {
        emit dead(prize);
    }
}

QRectF Enemy::boundingRect() const
{
    return QRectF(0, 0, sprite->width(), sprite->height());
}

QPainterPath Enemy::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Enemy::Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(*sprite));
    painter->setPen(Qt::NoPen);
    painter->drawRect(0, 0, sprite->width(), sprite->height());
    painter->setBrush(Qt::green);
    painter->drawRect(0, 0, current_hp*sprite->width()/max_hp, 3);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

Enemy::~Enemy()
{
    if (lifes != nullptr)
    {
        lifes->stop();
        lifes->disconnect();
        delete lifes;
    }
    delete sprite;
}


