#include "uiobject.h"

UiObject::UiObject(QWidget * parent)
{
    cost = 50;
    sprite = new QPixmap(":/res/images/Tower.png"); // удалить и вынести
    this->setPixmap(*sprite);
    this->setFixedSize(sprite->width(),sprite->height());
}

int UiObject::getCost()
{
    return cost;
}

void UiObject::mousePressEvent(QMouseEvent *event)
{
    emit create();
}

