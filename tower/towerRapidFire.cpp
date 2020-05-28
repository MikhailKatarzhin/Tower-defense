#include "towerRapidFire.h"

TowerRapidFire::TowerRapidFire(QGraphicsObject *parent)
{
    area    = nullptr;

    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable);

    l_centerX = sprite->width()/2;
    l_centerY = sprite->height()/2;

    detecter = new QTimer();
    connect(detecter, SIGNAL(timeout()), this, SLOT(chooseEnemy()));
    detecter->start(1000/firingRate);
}

void TowerRapidFire::setArea()
{
    centerX = scenePos().x() + l_centerX;
    centerY = scenePos().y() + l_centerY;
    area->setPos(centerX-radius/2, centerY-radius/2);
}

void TowerRapidFire::chooseEnemy()
{
    if(area == nullptr)
        return;
    QList<QGraphicsItem *> colliding_items = area->collidingItems(Qt::IntersectsItemShape);

    int maxSpeed = 0;
    int maxPassedWay = 0;

    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        IEnemy *enemy = dynamic_cast<IEnemy *>(colliding_items[i]);

        //выбирает в цель врага с самой высокой скоростью передвижения

        if(enemy && enemy->getSpeed() > maxSpeed)
        {
            maxSpeed = enemy->getSpeed();
            maxPassedWay = enemy->getpassedWay();
            target = enemy;
        }else if(enemy && enemy->getSpeed() == maxSpeed && enemy->getpassedWay() > maxPassedWay)
        {
            maxPassedWay = enemy->getpassedWay();
            target = enemy;
        }
    }

    if(maxSpeed)
    {
        enemyPlace = QPointF(target->pos());
        fire();
    }
}

void TowerRapidFire::upgrade()
{
    if(!isSelected())
    {
        disconnect(sender(),SIGNAL(clicked()), this, SLOT(upgrade()));
    }
    else
    {
        if(INT_MAX / MULTIPLIERRADIUS > radius)
            radius *= MULTIPLIERRADIUS;
        else
            radius = INT_MAX;

        if(INT_MAX / MULTIPLIERPOWER > power)
            power *= MULTIPLIERPOWER;
        else
            power = INT_MAX;

        if(radius == INT_MAX && power == INT_MAX)
            cost = 0;
        else
            ++level;

        if(INT_MAX / MULTIPLIERCOST > cost)
            cost  *= MULTIPLIERCOST;
        else
            cost = INT_MAX;

        if(INT_MAX - cost/2 > salePrice)
            salePrice += cost/2;
        else
            salePrice = INT_MAX;

        firingRate *= MULTIPLIERFIRINGRATE;
        detecter->start(1000/firingRate);

        switch (level)
        {
        case 5:
        {
            power   *= 2;
            break;

        }
        case 20:
        {
            power   *= 3;
            break;
        }
        default: break;
        }
        emit updateTower(this);
    }

}

void TowerRapidFire::fire()
{
    Bullet* bullet = new Bullet(this);
    bullet->setPos(centerX, centerY);

    QLineF ln(QPointF(centerX-l_centerX,centerY-l_centerY), enemyPlace);
    double angle = -1*ln.angle();
    bullet->setRotation(angle);

    scene()->addItem(bullet);
    target->damaged(power);
}

ITower * TowerRapidFire::copyTower()
{
    TowerRapidFire *tower = new TowerRapidFire();
    tower->sprite    = this->sprite;
    tower->radius    = this->radius;
    tower->power     = this->power;
    tower->cost      = this->cost;
    tower->radius    = this->radius;
    tower->level     = this->level;
    tower->salePrice = this->salePrice;
    tower->firingRate= this->firingRate;
    return tower;
}

float TowerRapidFire::getMULTIPLIERRADIUS()
{
    return MULTIPLIERRADIUS;
}
float TowerRapidFire::getMULTIPLIERPOWER()
{
    return MULTIPLIERPOWER;
}
float TowerRapidFire::getMULTIPLIERCOST()
{
    return MULTIPLIERCOST;
}
float TowerRapidFire::getMULTIPLIERFIRINGRATE()
{
    return MULTIPLIERFIRINGRATE;
}

float TowerRapidFire::getBASEFIRINGRATE()
{
    return BASEFIRINGRATE;
}
int TowerRapidFire::getBASECOST()
{
    return BASECOST;
}
int TowerRapidFire::getBASEPOWER()
{
    return BASEPOWER;
}
int TowerRapidFire::getBASERADIUS()
{
    return BASERADIUS;
}

QPixmap* TowerRapidFire::getSprite()
{
    return sprite;
}
int TowerRapidFire::getLevel()
{
    return level;
}
int TowerRapidFire::getPower()
{
    return power;
}
int TowerRapidFire::getRadius()
{
    return radius;
}
int TowerRapidFire::getCost()
{
    return cost;
}
int TowerRapidFire::getSalePrice()
{
    return salePrice;
}
float TowerRapidFire::getFiringRate()
{
    return firingRate;
}

TowerRapidFire::~TowerRapidFire()
{
    delete sprite;
    delete area;
    delete detecter;
}

QRectF TowerRapidFire::boundingRect() const
{
    return QRectF(0, 0, sprite->width(), sprite->height());
}

void TowerRapidFire::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(area == nullptr)
    {
        area = new TowerArea(this);
        scene()->addItem(area);
        area->setRadius(radius);
        setArea();
        area->show();
    }
    else
    {
        area->setRadius(radius);
        setArea();
    }
    painter->setBrush(QBrush(*sprite));
    painter->drawRect(0, 0, sprite->width(), sprite->height());

    Q_UNUSED(option);
    Q_UNUSED(widget);

}

void TowerRapidFire::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(!area->isVisible())
    {
        area->show();
    }
    QGraphicsItem::hoverEnterEvent(event);
}

void TowerRapidFire::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if(area->isVisible())
    {
        area->hide();
    }
    QGraphicsItem::hoverLeaveEvent(event);
}


