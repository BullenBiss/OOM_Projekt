#ifndef BULLET_H
#define BULLET_H

#include "arena.h"
#include <tgmath.h>
#include <QGraphicsEllipseItem>

class bullet : public QGraphicsEllipseItem
{
public:
    bullet();
    void move(double shipAngleIn);
    void bulletVelocity(float shipV);
    void update();
private:
    double bulletV = 0;
    double bulletX = 0;
    double bulletY = 0;
    double shipAngle = 0;
    double blackholeAx = 0;
    double blackholeAy = 0;
    const double pi = 3.14159;
};

#endif // BULLET_H
