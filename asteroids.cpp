#include "asteroids.h"

asteroids::asteroids()
{
    _scaleX = 150;
    _scaleY = 150;
    this->setTransformOriginPoint(_scaleX/2, _scaleY/2);
    this->randomPos();
    this->spawnAsteroid();

}

asteroids::asteroids(int x, int y, int scaleX, int scaleY)
{
    this->setTransformOriginPoint(_scaleX/2, _scaleY/2);
    this->setX(x);
    this->setY(y);
    _scaleX = scaleX;
    _scaleY = scaleY;
    this->setTransformOriginPoint(_scaleX/2, _scaleY/2);
    this->spawnAsteroid();
}

void asteroids::spawnAsteroid()
{
    QPixmap pixmap(":/new/images/Asteroid.png");
    QPixmap scaled = pixmap.scaled(QSize(_scaleX, _scaleY));
    this->setPixmap(scaled);
    this->randomVel();
    this->randomRot();
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
    velocityX = (rand() % 6) - 3;
    velocityY = (rand() % 6) - 3;

    if(velocityX == 0)
    {
        velocityX = 1;
    }

    if(velocityY == 0)
    {
        velocityY = -1;
    }
}

void asteroids::randomRot()
{
    _randRot = (rand() % 6) - 3;
}
void asteroids::update()
{
    this->moveBy(velocityX,velocityY);
    this->setRotation(_rotation);
    _rotation += _randRot;
}


asteroids::~asteroids()
{
    //this->setRect(0,0,0,0);

}
