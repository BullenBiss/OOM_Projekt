#ifndef GAME_H
#define GAME_H

#include <QDebug>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include <vector>
#include "arena.h"
#include "ship.h"
#include "gameobject.h"
#include "bullet.h"
#include "asteroids.h"


class game : public QObject
{
    Q_OBJECT
public:
    game();
    ~game();
    void initiate();
    void shootEvent();
    void asteroidUpdate();
    void shipUpdate();
    void bulletUpdate();
    bool collisionDetectionAsteroid(asteroids *asteroid);
    bool collisionDetectionShip(ship *ship);
public slots:
    void gameUpdate();
private:
    double shotTimer = 0;
    bool shoot = false;
    arena *Arena = new arena();
    ship *Ship1 = new ship;     //Skapar ship som sen kan användas i hela game klassen
    bullet *Bullet = new bullet[5];
    std::vector<asteroids*> asteroid;
};

#endif // GAME_H
