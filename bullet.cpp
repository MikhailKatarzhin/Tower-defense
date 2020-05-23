#include "bullet.h"
#include <QtMath>

Bullet::Bullet(QGraphicsObject * parent)
{
    STEP_SIZE = 20;
    sprite = new QPixmap(":/res/images/Arrow.png");
    move_timer = new QTimer(this);
    connect(move_timer, SIGNAL(timeout()), this, SLOT(move()));
    move_timer->start(30);
}

void Bullet::move()
{
    Enemy* enemy = static_cast<Enemy*>(collidingItems().first());

    if(enemy)
    {
        move_timer->stop();
        move_timer->disconnect();
        delete this;
    }
    else
    {
        theta = rotation();
        dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
        dx = STEP_SIZE * qCos(qDegreesToRadians(theta));
        moveBy(dx,dy);
    }
}

QRectF Bullet::boundingRect() const
{
    return QRectF(0, 0, sprite->width(), sprite->height());
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(*sprite));
    painter->setPen(Qt::NoPen);
    painter->drawRect(0, 0, sprite->width(), sprite->height());

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QPainterPath Bullet::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

Bullet::~Bullet()
{
    delete sprite;
    move_timer->stop();
    move_timer->disconnect();
    delete move_timer;
}
