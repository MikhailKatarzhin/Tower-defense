#pragma once
#include <QtWidgets>

class HUD : public QWidget
{
    Q_OBJECT
public:
    HUD(QWidget *parent = nullptr);
    ~HUD();
public slots:
    void life(int);
    void money(int);
    void enemy(int);
    void wave(int);
private:
    QLabel * l_life ;
    QLabel * l_money;
    QLabel * l_wave;
    QLabel * l_enemy;
    QPushButton * startWave;
    QVBoxLayout * v_box;
};

