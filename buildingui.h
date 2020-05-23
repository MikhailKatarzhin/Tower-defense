#pragma once
#include <QWidget>
#include "uiobject.h"

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
    void sendBuild();
    void setPossible(int money);

signals:
    void build();
};

