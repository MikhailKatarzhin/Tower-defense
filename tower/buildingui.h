#pragma once
#include <QWidget>
#include "tower/uiobject.h"
#include "tower/ITower.h"

/**
 * @brief The BuildingUI class
 * This is UI with list of the towers.
 */
class BuildingUI : public QWidget
{
    Q_OBJECT

public:
    BuildingUI(QWidget *parent = nullptr);

private:
    QVBoxLayout v_box;
    QWidgetList list;

public slots:
    void sendBuild(ITower*);
    void setPossible(int money);

signals:
    void build(ITower*);
};

