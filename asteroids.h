#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include <QtWidgets>
#include <time.h>
#include <QGraphicsItem>
#include <QPixmap>

class asteroids : public QGraphicsPixmapItem
{
public:
    asteroids();
    asteroids(int x, int y, int scaleX, int scaleY);
    void spawnAsteroid();
    int getScaleX();
    int getScaleY();
    void randomPos();
    void randomVel();
    void randomRot();
    void update();
    ~asteroids();
private:
    int velocityX;
    int velocityY;
    int _X;
    int _Y;
    int _scaleX;
    int _scaleY;
    int _rotation, _randRot;

};

#endif // ASTEROIDS_H
