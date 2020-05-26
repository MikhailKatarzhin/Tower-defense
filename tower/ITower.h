#pragma once
#include <QtWidgets>
#include <QGraphicsObject>

class ITower : public QGraphicsObject
{
    Q_OBJECT

public:

    virtual float   getMULTIPLIERRADIUS() = 0;
    virtual float   getMULTIPLIERPOWER() = 0;
    virtual float   getMULTIPLIERCOST() = 0;
    virtual int     getBASECOST() = 0;

    virtual void setArea() = 0;
    virtual void fire() = 0;

    virtual QPixmap* getSprite() = 0;
    virtual int getLevel() = 0;
    virtual int getPower() = 0;
    virtual int getRadius() = 0;
    virtual int getCost() = 0;
    virtual int getSalePrice() = 0;

signals:
    virtual void updateTower(ITower*) = 0;

public slots:
    virtual void chooseEnemy() = 0;
    virtual void upgrade() = 0;

protected:
    virtual QRectF boundingRect() const = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event) = 0;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event) = 0;
};
