#include "enemy/enemyArmored.h"


EnemyArmored::EnemyArmored(Road _way, int wave) : way(_way)
{
    passedWay   = 0;
    sprite      = new QPixmap(":/res/images/EnemyArmored.png");
    max_hp      = 175 * pow(1.25, wave);
    current_hp  = max_hp;
    speed       = 400 * pow(1.005, wave);
    armor       = 6 * pow(1.1, wave);
    point       = 1;
    prize       = 8 * pow(1.1, wave);
    this->setPos(way.getStart().x(), way.getStart().y());
    lifes = new QTimer();
    connect(lifes, SIGNAL(timeout()), this, SLOT(move()));
    lifes->start(10000 / speed);
}

void EnemyArmored::move()
{
    // тут наверное стоит пересчитывать путь и идти
    // хотя не это затратно
    // а может и нет
    //
    if(this->scenePos() != way.getPoints().last())
    {
        passedWay += (this->scenePos() - way.getPoints()[point]).manhattanLength();

        if(this->scenePos() == way.getPoints()[point]) ++point;
        else
        {
            if(this->scenePos().x() < ((way.getPoints()[point]).x()))
            {
                dx = 1;
            }
            else if (this->scenePos().x() > (way.getPoints()[point].x()))
            {
                dx = -1;
            }
            else
            {
                dx = 0;
            }
            if(this->scenePos().y() < (way.getPoints()[point].y()))
            {
                dy = 1;
            }
            else if (this->scenePos().y() > (way.getPoints()[point].y()))
            {
                dy = -1;
            }
            else
            {
                dy = 0;
            }

            moveBy(dx,dy);
        }
    }
    else
    {
        lifes->stop();
        lifes->disconnect();
        emit win();
        delete this;
    }
}

void EnemyArmored::stop()
{
    lifes->stop();
    lifes->disconnect();
}

int EnemyArmored::getPoint()
{
    return point;
}

int EnemyArmored::getpassedWay()
{
    return  passedWay;
}
int EnemyArmored::getSpeed()
{
    return speed;
}
void EnemyArmored::damaged(int damage)
{
    damage -= armor;
    if(damage >= 0)
        current_hp -=damage;

    if(current_hp <= 0 )
    {
        emit dead(prize);
    }
}

QRectF EnemyArmored::boundingRect() const
{
    return QRectF(0, 0, sprite->width(), sprite->height());
}

QPainterPath EnemyArmored::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void EnemyArmored::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(*sprite));
    painter->setPen(Qt::NoPen);
    painter->drawRect(0, 0, sprite->width(), sprite->height());
    painter->setBrush(Qt::green);
    painter->drawRect(0, 0, current_hp*sprite->width()/max_hp, 3);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

EnemyArmored::~EnemyArmored()
{
    if (lifes != nullptr)
    {
        lifes->stop();
        lifes->disconnect();
        delete lifes;
    }
    delete sprite;
}



