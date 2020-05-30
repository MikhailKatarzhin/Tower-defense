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
    this->setPos(way.getStart().x(), way.getStart().y());
    lifes = new QTimer();
    connect(lifes, SIGNAL(timeout()), this, SLOT(move()));
    lifes->start(10000 / speed);
}

void Enemy::move()
{
    dy = 0;
    dx = 0;
    qDebug()<<"x:\t"<<this->pos().x() << "\ty:\t" << this->pos().y();
    QTransform * qtransform = new QTransform();
    QGraphicsItem * upperItem = level->itemAt(this->pos().x(), this->pos().y(), *qtransform);
    QList<QGraphicsItem *> listItems = upperItem->collidingItems();
    RoadPlace *currentRoadPlace/* = dynamic_cast<RoadPlace *>(level->itemAt(this->pos().x(), this->pos().y(), *qtransform))*/;
    for(QGraphicsItem * item : listItems)
    {
        currentRoadPlace =  dynamic_cast<RoadPlace *>(item);
        if(currentRoadPlace != nullptr)
            break;
    }

    if( currentRoadPlace != nullptr )
    {

        RoadPlace *upRoadPlace = dynamic_cast<RoadPlace *>(level->itemAt(this->pos().x(), this->pos().y() + currentRoadPlace->y(), *qtransform));
        RoadPlace *downRoadPlace = dynamic_cast<RoadPlace *>(level->itemAt(this->pos().x(), this->pos().y() - currentRoadPlace->y(), *qtransform));
        RoadPlace *rightRoadPlace = dynamic_cast<RoadPlace *>(level->itemAt(this->pos().x() + currentRoadPlace->x(), this->pos().y(), *qtransform));
        RoadPlace *leftRoadPlace = dynamic_cast<RoadPlace *>(level->itemAt(this->pos().x() + currentRoadPlace->x(), this->pos().y(), *qtransform));

        if(upRoadPlace != nullptr && upRoadPlace->getWeight() < currentRoadPlace->getWeight())
        {
            if(downRoadPlace != nullptr)
            {
                if(upRoadPlace->getWeight() <= downRoadPlace->getWeight())
                    dy = 1;
            }else
                dy = 1;
        }

        if(downRoadPlace != nullptr && downRoadPlace->getWeight() < currentRoadPlace->getWeight())
        {
            if(upRoadPlace != nullptr)
            {
                if(downRoadPlace->getWeight() < upRoadPlace->getWeight())
                    dy = -1;
            }else
                dy = -1;
        }

        if(rightRoadPlace != nullptr && rightRoadPlace->getWeight() < currentRoadPlace->getWeight())
        {
            if(leftRoadPlace != nullptr)
            {
                if(rightRoadPlace->getWeight() <= leftRoadPlace->getWeight())
                    dy = 1;
            }else
                dy = 1;
        }

        if(leftRoadPlace != nullptr && leftRoadPlace->getWeight() < currentRoadPlace->getWeight())
        {
            if(rightRoadPlace != nullptr)
            {
                if(leftRoadPlace->getWeight() < rightRoadPlace->getWeight())
                    dy = -1;
            }else
                dy = -1;
        }
    }

    moveBy(dx,dy);

    upperItem = level->itemAt(this->pos().x(), this->pos().y(), *qtransform);
    listItems = upperItem->collidingItems();
    CastlePlace *castlePlace/* = dynamic_cast<RoadPlace *>(level->itemAt(this->pos().x(), this->pos().y(), *qtransform))*/;
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


