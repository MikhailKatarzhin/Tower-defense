#include "enemy/enemy.h"


Enemy::Enemy(Road _way, int wave) : way(_way)
{
    passedWay = 0;
    sprite = new QPixmap(":/res/images/Enemy.png");
    max_hp = 100 * pow(1.15, wave);
    current_hp = max_hp;
    speed = 1000 * pow(0.995, wave);
    point = 1;
    prize = 5 * pow(1.1, wave);
    this->setPos(way.getStart().x(), way.getStart().y());
    stepTimer = new QTimer();
    connect(stepTimer, SIGNAL(timeout()), this, SLOT(move()));
    stepTimer->start(speed / 50);
}

void Enemy::move()
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
        stepTimer->stop();
        stepTimer->disconnect();
        emit win();
        delete this;
    }
}

void Enemy::stop()
{
    stepTimer->stop();
    stepTimer->disconnect();
}

int Enemy::getPoint()
{
    return point;
}

int Enemy::getpassedWay()
{
    return  passedWay;
}

void Enemy::damaged(int damage)
{
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

void Enemy::paintHealthBar(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    if (stepTimer != nullptr)
    {
        stepTimer->stop();
        stepTimer->disconnect();
        delete stepTimer;
    }
    delete sprite;
}

void Enemy::dead(int){}
void Enemy::win(){}

