#pragma once
#include <QObject>
#include <QtWidgets>

class Menu : public QWidget
{
    Q_OBJECT

public:
    Menu(QWidget * parent  = nullptr);
public slots:
    void chooseLvl();
private:
    QPushButton  startgame;
    QPushButton  quit;

};


