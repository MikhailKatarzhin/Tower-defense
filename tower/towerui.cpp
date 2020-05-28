#include "tower/towerui.h"
#include <math.h>


TowerUI::TowerUI(QWidget *parent) : QWidget(parent)
{
    setFixedSize(220,145);
    power = new QLabel("Power: ", this);
    radius = new QLabel("Radius: ", this);
    level = new QLabel("Level: ", this);
    firingRate = new QLabel("Shoot per sec: ", this);
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
    v_box->addWidget(firingRate);
    v_box->addLayout(h_box);
    v_box->setAlignment(Qt::AlignBottom);
    setLayout(v_box);
    setUi();
    connect(upgrade, SIGNAL(clicked()), parent, SLOT(upgradeTower()));
    connect(sell, SIGNAL(clicked()), parent, SLOT(sellTower()));
}

void TowerUI::setUi(ITower * tower)
{
    if(tower != nullptr)
    {
        levelTower  = tower->getLevel();
        costUp      = tower->getCost();

        level->setText(QString("Level: %1 (%2)").arg(levelTower).arg(levelTower+1));
        power->setText(QString("Power: %1 (+%2)").arg(tower->getPower()).arg((int)(tower->getPower() * (tower->getMULTIPLIERPOWER() - 1))));
        radius->setText(QString("Radius: %1 (+%2)").arg(tower->getRadius()).arg((int)(tower->getRadius() * (tower->getMULTIPLIERRADIUS() - 1))));
        firingRate->setText(QString("Shoot per sec: %1 (+%2)").arg(tower->getFiringRate()).arg(tower->getFiringRate() * (tower->getMULTIPLIERFIRINGRATE() - 1)));
        sell->setText(QString("Sell %1").arg(tower->getSalePrice()));

        upgrade->setText(QString("Upgrade %1").arg(costUp));
        checkUp();

        sell->setEnabled(true);
        connect(tower, SIGNAL(updateTower(ITower*)), this, SLOT(setUi(ITower*)));
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
        firingRate->setText("Shoot per sec: ");
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

