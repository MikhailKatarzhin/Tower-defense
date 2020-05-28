#include "tower/buildingui.h"
#include "tower/tower.h"
#include "tower/towerRapidFire.h"
BuildingUI::BuildingUI(QWidget *parent) : QWidget(parent)
{
    v_box.setAlignment(Qt::AlignTop);

    QLabel * name = new QLabel("<b>Towers:<b>");
    v_box.addWidget(name);


    UiObject * baseTower =    new UiObject(nullptr, new Tower());
    QLabel * costBT =     new QLabel(QString("Cost: %1").arg(baseTower->getTower()->getBASECOST()));
    QLabel * radiusBT =   new QLabel(QString("Radius: %1").arg(baseTower->getTower()->getBASERADIUS()));
    QLabel * powerBT =    new QLabel(QString("Power: %1").arg(baseTower->getTower()->getBASEPOWER()));
    QLabel * firingRateBT =    new QLabel(QString("Shoot per sec: %1").arg(baseTower->getTower()->getBASEFIRINGRATE()));

    connect(baseTower, SIGNAL(create(ITower*)), this, SLOT(sendBuild(ITower*)));

    list.push_back(baseTower);
    list.push_back(costBT);
    list.push_back(radiusBT);
    list.push_back(powerBT);
    list.push_back(firingRateBT);

    UiObject * rapidFireTower =    new UiObject(nullptr, new TowerRapidFire());
    QLabel * costRFT =     new QLabel(QString("Cost: %1").arg(rapidFireTower->getTower()->getBASECOST()));
    QLabel * radiusRFT =   new QLabel(QString("Radius: %1").arg(rapidFireTower->getTower()->getBASERADIUS()));
    QLabel * powerRFT =    new QLabel(QString("Power: %1").arg(rapidFireTower->getTower()->getBASEPOWER()));
    QLabel * firingRateRFT =    new QLabel(QString("Shoot per sec: %1").arg(rapidFireTower->getTower()->getBASEFIRINGRATE()));

    connect(rapidFireTower, SIGNAL(create(ITower*)), this, SLOT(sendBuild(ITower*)));

    list.push_back(rapidFireTower);
    list.push_back(costRFT);
    list.push_back(radiusRFT);
    list.push_back(powerRFT);
    list.push_back(firingRateRFT);

    for(auto wgt : list)
    {
        v_box.addWidget(wgt);
    }
    this->setContentsMargins(1,1,1,1);
    this->setLayout(&v_box);
}

void BuildingUI::sendBuild(ITower* tower)
{
    emit build(tower);
}

void BuildingUI::setPossible(int money)
{
    for(auto i : list)
    {
        if (UiObject * obj = dynamic_cast<UiObject*>(i))
        {
            if(money < obj->getTower()->getBASECOST())
            {
                i->setEnabled(false);
            }
            else
            {
                i->setEnabled(true);
            }
        }
    }
}
