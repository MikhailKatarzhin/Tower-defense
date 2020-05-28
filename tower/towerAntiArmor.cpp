#include "tower/towerAntiArmor.h"

TowerAntiArmor::TowerAntiArmor(QGraphicsObject *parent)
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

void TowerAntiArmor::setArea()
{
    centerX = scenePos().x() + l_centerX;
    centerY = scenePos().y() + l_centerY;
    area->setPos(centerX-radius/2, centerY-radius/2);
}

void TowerAntiArmor::chooseEnemy()
{
    if(area == nullptr)
        return;
    QList<QGraphicsItem *> colliding_items = area->collidingItems(Qt::IntersectsItemShape);

    int maxArmor = 0;
    int maxPassedWay = 0;

    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        IEnemy *enemy = dynamic_cast<IEnemy *>(colliding_items[i]);

        //выбирает в цель врага с самым большим пройденным путём

        if(enemy && enemy->getArmor() > maxArmor)
        {
            maxArmor = enemy->getArmor();
            maxPassedWay = enemy->getpassedWay();
            target = enemy;
        }else if(enemy && enemy->getArmor() == maxArmor && enemy->getpassedWay() > maxPassedWay)
        {
            maxPassedWay = enemy->getpassedWay();
            target = enemy;
        }
    }

    if(maxPassedWay)
    {
        enemyPlace = QPointF(target->pos());
        fire();
    }
}

void TowerAntiArmor::upgrade()
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

void TowerAntiArmor::fire()
{
    Bullet* bullet = new Bullet(this);
    bullet->setPos(centerX, centerY);

    QLineF ln(QPointF(centerX-l_centerX,centerY-l_centerY), enemyPlace);
    double angle = -1*ln.angle();
    bullet->setRotation(angle);

    scene()->addItem(bullet);
    target->damaged(power);
}

ITower * TowerAntiArmor::copyTower()
{
    TowerAntiArmor *tower = new TowerAntiArmor();
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

float TowerAntiArmor::getMULTIPLIERRADIUS()
{
    return MULTIPLIERRADIUS;
}
float TowerAntiArmor::getMULTIPLIERPOWER()
{
    return MULTIPLIERPOWER;
}
float TowerAntiArmor::getMULTIPLIERCOST()
{
    return MULTIPLIERCOST;
}
float TowerAntiArmor::getMULTIPLIERFIRINGRATE()
{
    return MULTIPLIERFIRINGRATE;
}

float TowerAntiArmor::getBASEFIRINGRATE()
{
    return BASEFIRINGRATE;
}
int TowerAntiArmor::getBASECOST()
{
    return BASECOST;
}
int TowerAntiArmor::getBASEPOWER()
{
    return BASEPOWER;
}
int TowerAntiArmor::getBASERADIUS()
{
    return BASERADIUS;
}

QPixmap* TowerAntiArmor::getSprite()
{
    return sprite;
}
int TowerAntiArmor::getLevel()
{
    return level;
}
int TowerAntiArmor::getPower()
{
    return power;
}
int TowerAntiArmor::getRadius()
{
    return radius;
}
int TowerAntiArmor::getCost()
{
    return cost;
}
int TowerAntiArmor::getSalePrice()
{
    return salePrice;
}
float TowerAntiArmor::getFiringRate()
{
    return firingRate;
}

TowerAntiArmor::~TowerAntiArmor()
{
    delete sprite;
    delete area;
    delete detecter;
}

QRectF TowerAntiArmor::boundingRect() const
{
    return QRectF(0, 0, sprite->width(), sprite->height());
}

void TowerAntiArmor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void TowerAntiArmor::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(!area->isVisible())
    {
        area->show();
    }
    QGraphicsItem::hoverEnterEvent(event);
}

void TowerAntiArmor::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if(area->isVisible())
    {
        area->hide();
    }
    QGraphicsItem::hoverLeaveEvent(event);
}


