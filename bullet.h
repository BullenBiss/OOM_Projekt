#ifndef BULLET_H
#define BULLET_H

#include "arena.h"
#include <tgmath.h>
#include <QGraphicsEllipseItem>
#include <QObject>

class bullet : public QGraphicsEllipseItem, public QObject
{
public:
    bullet();
    void move(double shipAngleIn);
    void bulletVelocity(float shipV);
    void activate();
    bool active();
    ~bullet();
public slots:
    void update();
private:
    double dt = 100;
    double bulletV = 0;
    double bulletX = 0;
    double bulletY = 0;
    double shipAngle = 0;
    double blackholeAx = 0;
    double blackholeAy = 0;
    const double pi = 3.14159;
    QTimer * timer = new QTimer();                              //Skapa timer

};

#endif // BULLET_H
