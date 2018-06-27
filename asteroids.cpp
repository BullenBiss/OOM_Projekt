#include "asteroids.h"

asteroids::asteroids()
{
    this->setRect(0,0,40,40);
    this->setOpacity(1.0);
    this->setBrush(Qt::SolidPattern);
}

asteroids::asteroids(int x, int y, int scaleX, int scaleY)
{
    this->setRect(x,y,scaleX,scaleY);
    this->setOpacity(1.0);
    this->setBrush(Qt::SolidPattern);
}

void asteroids::update()
{
    this->moveBy(2,2);
}


asteroids::~asteroids()
{
    this->setRect(0,0,0,0);
    delete this;
}
