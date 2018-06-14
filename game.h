#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "arena.h"
#include "ship.h"
#include "gameobject.h"
#include "bullet.h"

class game : public QObject
{
    Q_OBJECT
public:
    game();
    void initiate();
    void shootEvent();
public slots:
    void gameUpdate();
private:
    double dt = 0;
    bool shoot = false;
    arena *Arena = new arena;
    ship *Ship1 = new ship;     //Skapar ship som sen kan användas i hela game klassen
    bullet *Bullet = NULL;
};

#endif // GAME_H
