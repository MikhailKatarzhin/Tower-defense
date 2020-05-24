#pragma once
#include <QtWidgets>

class HUD : public QWidget
{
    Q_OBJECT
public:
    HUD(QWidget *parent = nullptr);
    ~HUD();
public slots:
    void lifes(int);
    void money(int);
    void enemy(int);
    void wave(int);
private:
    QLabel * l_lifes ;
    QLabel * l_money;
    QLabel * l_wave;
    QLabel * l_enemy;
    QLabel * l_score;
    QPushButton * startWave;
    QVBoxLayout * v_box;
};

