#include "asteroids.h"

asteroids::asteroids()
{
    _scaleX = 100;
    _scaleY = 100;
    this->randomPos();
    this->spawnAsteroid();
}

asteroids::asteroids(int x, int y, int scaleX, int scaleY)
{
    this->setX(x);
    this->setY(y);
    _scaleX = scaleX;
    _scaleY = scaleY;
    this->spawnAsteroid();
}

void asteroids::spawnAsteroid()
{
    this->setRect(0,0,_scaleX,_scaleY);
    this->setOpacity(1.0);
    this->setBrush(Qt::SolidPattern);
    this->randomVel();
}

int asteroids::getScaleX()
{
    return _scaleX;
}

int asteroids::getScaleY()
{
    return _scaleY;
}


void asteroids::randomPos()
{
    _X = (rand() % 1800) - 900;
    _Y = (rand() % 1000) - 500;
    this->setPos(_X,_Y);
}

void asteroids::randomVel()
{
    velocityX = (rand() % 4) - 2;
    velocityY = (rand() % 4) - 2;

    if(velocityX == 0)
    {
        velocityX = 1;
    }

    if(velocityY == 0)
    {
        velocityY = -1;
    }
}

void asteroids::update()
{
    this->moveBy(velocityX,velocityY);
}


asteroids::~asteroids()
{
    this->setRect(0,0,0,0);
}
