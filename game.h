#ifndef GAME_H
#define GAME_H

#include <QProcess>
#include <QDebug>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include <QString>
#include <vector>
#include <QKeyEvent>
#include "sound.h"
#include "arena.h"
#include "ship.h"
#include "gameobject.h"
#include "bullet.h"
#include "asteroids.h"
#include "gametext.h"
#include "powerup.h"

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
    void powerupUpdate();
    void addBackground();
    bool collisionDetectionAsteroid(asteroids *asteroid);
    bool collisionDetectionShip(ship *ship);
    bool collisionDetectionPowerup(powerup *Power);
    void resetValues();
public slots:
    void gameUpdate();
private:
    double shotTimer = 0;
    double waveTimer = 0;
    double lifeTimer = 0;
    double powerupTimer = 0;
    int bulletNr;
    int shotLimit;
    int wave = 1;
    bool shoot = false;
    QTimer * timer = new QTimer();                              //Skapa timer
    arena *Arena = new arena();
    ship *Ship1 = new ship;     //Skapar ship som sen kan användas i hela game klassen
    ship *ghostShip = new ship;
    bullet *Bullet = new bullet[5];
    std::vector<asteroids*> asteroid;
    std::vector<gameText*> text;    //text[0] = lives, text[1] = score, text[2] = gameover
    QGraphicsPixmapItem * background = new QGraphicsPixmapItem;
    sound *s = new sound;
    powerup *power = new powerup(Arena->getWidth(), Arena->getHeight());
};

#endif // GAME_H
