#include "enemy/enemyRunner.h"


EnemyRunner::EnemyRunner(Road _way, int wave) : way(_way)
{
    passedWay = 0;
    sprite = new QPixmap(":/res/images/EnemyRunner.png");
    max_hp = 100 * pow(1.15, wave);
    current_hp = max_hp;
    speed = 550 * pow(1.05, wave);
    armor = 0;
    point = 1;
    prize = 7 * pow(1.1, wave);
    this->setPos(way.getStart().x(), way.getStart().y());
    lifes = new QTimer();
    connect(lifes, SIGNAL(timeout()), this, SLOT(move()));
    lifes->start(10000/ speed);
}

void EnemyRunner::move()
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

void EnemyRunner::stop()
{
    lifes->stop();
    lifes->disconnect();
}

int EnemyRunner::getPoint()
{
    return point;
}

int EnemyRunner::getpassedWay()
{
    return  passedWay;
}
int EnemyRunner::getSpeed()
{
    return speed;
}

void EnemyRunner::damaged(int damage)
{
    damage -= armor;
    if(damage >= 0)
        current_hp -=damage;

    if(current_hp <= 0 )
    {
        emit dead(prize);
    }
}

QRectF EnemyRunner::boundingRect() const
{
    return QRectF(0, 0, sprite->width(), sprite->height());
}

QPainterPath EnemyRunner::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void EnemyRunner::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(*sprite));
    painter->setPen(Qt::NoPen);
    painter->drawRect(0, 0, sprite->width(), sprite->height());
    painter->setBrush(Qt::green);
    painter->drawRect(0, 0, current_hp*sprite->width()/max_hp, 3);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

EnemyRunner::~EnemyRunner()
{
    if (lifes != nullptr)
    {
        lifes->stop();
        lifes->disconnect();
        delete lifes;
    }
    delete sprite;
}



