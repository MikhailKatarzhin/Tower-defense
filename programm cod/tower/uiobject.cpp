#include "tower/uiobject.h"

UiObject::UiObject(QWidget * parent, ITower * tower)
{
    sprite = new QPixmap(*(tower->getSprite()));
    this->tower = tower;
    this->setPixmap(*sprite);
    this->setFixedSize(sprite->width(),sprite->height());
}

ITower* UiObject::getTower()
{
    return tower;
}

void UiObject::mousePressEvent(QMouseEvent *event)
{
    emit create(tower->copyTower());
}

