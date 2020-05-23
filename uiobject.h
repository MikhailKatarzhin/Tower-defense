#pragma once
#include <QtWidgets>

class UiObject : public QLabel
{
    Q_OBJECT
public:
    UiObject(QWidget *parent = nullptr);
    int getCost();
protected:
    void mousePressEvent(QMouseEvent * event);
private:
    QPixmap * sprite;
    int cost;
signals:
    void create();
};
