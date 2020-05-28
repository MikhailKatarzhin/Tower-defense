#include "tower/buildingui.h"
#include "tower/tower.h"
BuildingUI::BuildingUI(QWidget *parent) : QWidget(parent)
{
    v_box.setAlignment(Qt::AlignTop);

    QLabel * name = new QLabel("<b>Towers:<b>");
    v_box.addWidget(name);


    UiObject * obj =    new UiObject(nullptr, new Tower());
    QLabel * cost =     new QLabel(QString("Cost: %1").arg(obj->getTower()->getBASECOST()));
    QLabel * radius =   new QLabel(QString("Radius: %1").arg(obj->getTower()->getBASERADIUS()));
    QLabel * power =    new QLabel(QString("Power: %1").arg(obj->getTower()->getBASEPOWER()));

    connect(obj, SIGNAL(create(ITower*)), this, SLOT(sendBuild(ITower*)));

    list.push_back(obj);
    list.push_back(cost);
    list.push_back(radius);
    list.push_back(power);

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
