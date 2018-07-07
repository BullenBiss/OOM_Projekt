#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include <QtWidgets>
#include <time.h>

class asteroids : public QGraphicsEllipseItem
{
public:
    asteroids();
    asteroids(int x, int y, int scaleX, int scaleY);
    void spawnAsteroid();
    int getScaleX();
    int getScaleY();
    void randomPos();
    void randomVel();
    void update();
    ~asteroids();
private:
    int velocityX;
    int velocityY;
    int _X;
    int _Y;
    int _scaleX;
    int _scaleY;
};

#endif // ASTEROIDS_H
