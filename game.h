#ifndef GAME_H
#define GAME_H

#include <QDebug>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include <QString>
#include <vector>
#include <QKeyEvent>
#include "arena.h"
#include "ship.h"
#include "gameobject.h"
#include "bullet.h"
#include "asteroids.h"
#include "gametext.h"


class game : public QObject
{
    Q_OBJECT
public:
    game();
    ~game();
    void initiate();
    void keyPressEvent(QKeyEvent *event);
    void shootEvent();
    void asteroidUpdate();
    void spawnWave();
    void shipUpdate();
    void bulletUpdate();
    void textUpdate();
    void addBackground();
    bool collisionDetectionAsteroid(asteroids *asteroid);
    bool collisionDetectionShip(ship *ship);
public slots:
    void gameUpdate();
private:
    double shotTimer = 0;
    double waveTimer = 0;
    int wave;
    bool shoot = false;
    arena *Arena = new arena();
    ship *Ship1 = new ship;     //Skapar ship som sen kan användas i hela game klassen
    bullet *Bullet = new bullet[5];
    std::vector<asteroids*> asteroid;
    std::vector<gameText*> text;    //text[0] = lives, text[1] = score, text[2] = gameover
    QGraphicsPixmapItem * background = new QGraphicsPixmapItem;
};

#endif // GAME_H
