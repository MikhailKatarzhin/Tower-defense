#include "tower.h"

Tower::Tower(QGraphicsObject *parent)
{
    level = 0;
    cost[0] = 50; cost[1] = 100; cost[2] = 200;
    power[0] = 20; power[1] = 40; power[2] = 70;
    radius[0] = 200; radius[1] = 250; radius[2] = 300;

    area = nullptr;

    setAcceptHoverEvents(true);

    sprite = new QPixmap(":/res/images/Tower.png");
    setFlag(QGraphicsItem::ItemIsSelectable);

    l_centerX = sprite->width()/2;
    l_centerY = sprite->height()/2;

    detecter = new QTimer();
    connect(detecter, SIGNAL(timeout()), this, SLOT(chooseEnemy()));
    detecter->start(1000);
}

void Tower::setArea()
{
    centerX = scenePos().x() + l_centerX;
    centerY = scenePos().y() + l_centerY;
    area->setPos(centerX-radius[level]/2, centerY-radius[level]/2);
}

void Tower::chooseEnemy()
{
    QList<QGraphicsItem *> colliding_items = area->collidingItems(Qt::IntersectsItemShape);

    int max = 0;

    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        Enemy *enemy = dynamic_cast<Enemy *>(colliding_items[i]);

        //выбирает в цель врага с самым большим пройденным путём

        if(enemy && enemy->getpassedWay() > max)
        {
            max = enemy->getpassedWay();
            target = enemy;
        }
    }

    if(max)
    {
        enemyPlace = QPointF(target->pos());
        fire();
    }
}

void Tower::upgrade()
{
    if(!isSelected())
    {
        disconnect(sender(),SIGNAL(clicked()), this, SLOT(upgrade()));
    }
    else
    {
        switch (level)
        {
        case 0:
        {
            ++level;
            delete sprite;
            sprite = new QPixmap(":/res/images/Tower2.png");
            emit up(this);
            update();
            break;

        }
        case 1:
        {
            ++level;
            delete sprite;
            sprite = new QPixmap(":/res/images/Tower3.png");
            emit up(this);
            update();
            break;
        }
        default: break;
        }
    }

}

void Tower::fire()
{
    Bullet* bullet = new Bullet(this);
    bullet->setPos(centerX, centerY);

    QLineF ln(QPointF(centerX-l_centerX,centerY-l_centerY), enemyPlace);
    double angle = -1*ln.angle();
    bullet->setRotation(angle);

    scene()->addItem(bullet);
    target->damaged(power[level]);
}

int Tower::getLevel()
{
    return level;
}

int Tower::getPower(int lvl)
{
    return power[lvl];
}

int Tower::getRadius(int lvl)
{
    return radius[lvl];
}

int Tower::getCost(int lvl)
{
    return cost[lvl];
}

Tower::~Tower()
{
    delete sprite;
    delete area;
    delete detecter;
}

QRectF Tower::boundingRect() const
{
    return QRectF(0, 0, sprite->width(), sprite->height());
}

void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(area == nullptr)
    {
        area = new TowerArea(this);
        scene()->addItem(area);
        area->setRadius(radius[level]);
        setArea();
        area->show();
    }
    else
    {
        area->setRadius(radius[level]);
        setArea();
    }
    painter->setBrush(QBrush(*sprite));
    painter->drawRect(0, 0, sprite->width(), sprite->height());

    Q_UNUSED(option);
    Q_UNUSED(widget);

}

void Tower::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(!area->isVisible())
    {
        area->show();
    }
    QGraphicsItem::hoverEnterEvent(event);
}

void Tower::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if(area->isVisible())
    {
        area->hide();
    }
    QGraphicsItem::hoverLeaveEvent(event);
}


