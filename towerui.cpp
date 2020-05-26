#include "towerui.h"
#include <math.h>


TowerUI::TowerUI(QWidget *parent) : QWidget(parent)
{
    setFixedSize(220,145);
    power = new QLabel("Power: ", this);
    radius = new QLabel("Radius: ", this);
    level = new QLabel("Level: ", this);
    sell = new QPushButton("Sell", this);
    sell->setEnabled(false);
    upgrade = new QPushButton(this);
    upgrade->setEnabled(false);
    levelTower = 999;
    QVBoxLayout * v_box = new QVBoxLayout();
    QHBoxLayout * h_box = new QHBoxLayout();
    h_box->addWidget(upgrade);
    h_box->addWidget(sell);
    v_box->addWidget(level);
    v_box->addWidget(power);
    v_box->addWidget(radius);
    v_box->addLayout(h_box);
    v_box->setAlignment(Qt::AlignBottom);
    setLayout(v_box);
    setUi();
    connect(upgrade, SIGNAL(clicked()), parent, SLOT(upgradeTower()));
    connect(sell, SIGNAL(clicked()), parent, SLOT(sellTower()));
}

void TowerUI::setUi(Tower * tower)
{
    if(tower != nullptr)
    {
        levelTower  = tower->getLevel();
        costUp      = tower->getCost();

        level->setText(QString("Level: %1 (%2)").arg(levelTower).arg(levelTower+1));
        power->setText(QString("Power: %1 (+%2)").arg(tower->getPower()).arg((int)(tower->getPower() * (tower->MULTIPLIERPOWER - 1))));
        radius->setText(QString("Radius: %1 (+%2)").arg(tower->getRadius()).arg((int)(tower->getRadius() * (tower->MULTIPLIERRADIUS - 1))));
        sell->setText(QString("Sell %1").arg(tower->getSalePrice()));

        upgrade->setText(QString("Upgrade %1").arg(costUp));
        checkUp();

        sell->setEnabled(true);
        connect(tower, SIGNAL(up(Tower*)), this, SLOT(setUi(Tower*)));
    }
    else
    {
        levelTower = -1;
        upgrade->setText("Upgrade");
        upgrade->setEnabled(false);

        sell->setText("Sell");
        sell->setEnabled(false);

        power->setText("Power: ");
        radius->setText("Radius: ");
        level->setText("Level: ");

    }
}

void TowerUI::checkUp()
{   
    if(money >= costUp)
    {
        upgrade->setEnabled(true);
    }
    else
    {
        upgrade->setEnabled(false);
    }

}

void TowerUI::setMoney(int _money)
{
    money = _money;
    checkUp();
}

