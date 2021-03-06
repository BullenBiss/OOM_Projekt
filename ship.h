#ifndef SHIP_H
#define SHIP_H

#include "gameobject.h"
#include <QKeyEvent>
#include <tgmath.h>
#include <QtWidgets>
#include <QKeyEvent>
#include <cmath>
//#include "bullet.h"


class ship : public QGraphicsPixmapItem
{
public:
    ship();
    ~ship();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void velocityVector();
    void spawn();
    void setActive(bool active);
    bool active();
    void addLife();
    void addScore();
    int getScore();
    void resetScore();
    void looseLife();
    int getLife();
    float getVelocity();
    void resetVelocity();
    void explosion();
    void movement();
    void update();
    bool shoot();
    bool escKey();
    void resetInput();
    double getAngle();
    const float pi = 3.14159;
protected:
    int lives;
    int score;
    int scaleX = 60;
    int scaleY = 50;
    bool _active;
    float acc = 0.6;
    float Vx = 0;       //V komposant
    float Vy = 0;       //V komposant
    float VMx = 0;      //Rörelsevektor komposant
    float VMy = 0;      //Rörelsevektor komposant
    float V = 0;        //V som skickas in
    double Vmax = 30;
    float angle = 2;    //Vinkel för rotation
    double angleRad = 0;

    bool rotateLeft = false, rotateRight = false, forwardPress = false; //Knapptryckflaggor
    bool upRotateLeft = false, upRotateRight = false;
    bool shootPress = false;
    bool escPress = false;
    float ax = 0;
    float ay = 0;
    float aB = 10.5;
    float h;
    QPixmap *pixmap = new QPixmap(":/new/images/Spaceship.png");
};

#endif // SHIP_H
