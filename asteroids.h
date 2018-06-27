#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include <QtWidgets>

class asteroids : public QGraphicsEllipseItem
{
public:
    asteroids();
    asteroids(int x, int y, int scaleX, int scaleY);
    void update();

    ~asteroids();
};

#endif // ASTEROIDS_H
