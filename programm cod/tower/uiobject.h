#pragma once
#include <QtWidgets>
#include "tower/ITower.h"
class UiObject : public QLabel
{
    Q_OBJECT
public:
    UiObject(QWidget *parent, ITower * tower);
    ITower* getTower();
protected:
    void mousePressEvent(QMouseEvent * event);
private:
    ITower * tower;
    QPixmap * sprite;
signals:
    void create(ITower*);
};
