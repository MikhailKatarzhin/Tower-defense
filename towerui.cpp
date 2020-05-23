#include "towerui.h"


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
    connect(sell, SIGNAL(clicked()), parent, SLOT(cellTower()));
}

void TowerUI::setUi(Tower * tower)
{
    if(tower != nullptr)
    {
        levelTower = tower->getLevel();
        costUp = tower->getCost(levelTower);
        pow = tower->getPower(levelTower);
        rad = tower->getRadius(levelTower);

        if(tower->getLevel() < 2)
        {
            nextCost = tower->getCost(levelTower+1);
            nextPow = tower->getPower(levelTower+1);
            nextRad = tower->getRadius(levelTower+1);

            level->setText(QString("Level: %1 (%2)").arg(levelTower+1).arg(levelTower+2));
            power->setText(QString("Power: %1 (%2)").arg(pow).arg(nextPow));
            radius->setText(QString("Radius: %1 (%2)").arg(rad).arg(nextRad));
            sell->setText(QString("Sell %1 (%2)").arg(costUp/2).arg(nextCost/2));

            upgrade->setText(QString("Upgrade %1").arg(costUp));
            checkUp();
        }
        else
        {
            level->setText(QString("Level: %1").arg(levelTower+1));
            power->setText(QString("Power: %1").arg(pow));
            radius->setText(QString("Radius: %1").arg(rad));
            sell->setText(QString("Sell %1").arg(costUp/2));

            upgrade->setEnabled(false);
            upgrade->setText("MAX LEVEL");
        }

        sell->setEnabled(true);
        connect(tower, SIGNAL(up(Tower*)), this, SLOT(setUi(Tower*)));
    }
    else
    {
        levelTower = 999;
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
    if(money >= costUp && levelTower < 2)
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

