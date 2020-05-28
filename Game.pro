
#-------------------------------------------------
#
# Project created by QtCreator 2018-11-25T17:19:18
#
#-------------------------------------------------

QT       += core gui xml multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Game
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    enemy/BaseEnemyFactory.cpp \
    enemy/EasyEnemyFactory.cpp \
    enemy/HardEnemyFactory.cpp \
    enemy/enemy.cpp \
    enemy/enemyArmored.cpp \
    enemy/enemyRunner.cpp \
    level/TextFileLevelParser.cpp \
    level/XmlLevelParser.cpp \
    tower/buildingui.cpp \
    tower/tower.cpp \
    tower/towerarea.cpp \
    tower/towerui.cpp \
    tower/uiobject.cpp \
    main.cpp \
    map.cpp \
    road.cpp \
    game.cpp \
    menu.cpp \
    level.cpp \
    bullet.cpp \
    towerplace.cpp \
    hud.cpp

HEADERS += \
    enemy/BaseEnemyFactory.h \
    enemy/EasyEnemyFactory.h \
    enemy/HardEnemyFactory.h \
    enemy/IEnemy.h \
    enemy/IEnemyFactory.h \
    enemy/enemyArmored.h \
    enemy/enemyRunner.h \
    level/ILevelParser.h \
    level/TextFileLevelParser.h \
    level/XmlLevelParser.h \
    tower/buildingui.h \
    tower/ITower.h \
    tower/tower.h \
    tower/towerarea.h \
    tower/towerui.h \
    tower/uiobject.h \
    map.h \
    road.h \
    game.h \
    enemy/enemy.h \
    menu.h \
    level.h \
    bullet.h \
    towerplace.h \
    hud.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    res/maps/map
