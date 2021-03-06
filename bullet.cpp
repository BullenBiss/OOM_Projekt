#include "bullet.h"

bullet::bullet()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));    //Koppla till medlemmen update()
    this->setRect(0,0,0,0);
    this->setOpacity(0.0);
    size = 10;
    dt = 0;
    bulletAddVel = 6;
}

void bullet::move(double shipAngleIn)
{
    shipAngle = (shipAngleIn * pi)/180;     //Skriv om vinkeln till radianer
    bulletY = sin(shipAngle) * bulletV;     //Komposantuppdelning av V
    bulletX = cos(shipAngle) * bulletV;     //Komposantuppdelning av V
}

void bullet::bulletVelocity(float shipV)
{
    bulletV = abs(shipV) + bulletAddVel;
}

void bullet::activate()
{
    dt = 0;
    timer->start(1000/60);                                      //60fps typ

    this->setRect(0,0,size,size);
    this->setOpacity(1.0);
    this->setBrush(Qt::white);
}

void bullet::deactivate()
{
    timer->stop();
    this->setRect(0,0,0,0);
    this->setOpacity(0.0);
}

bool bullet::active()
{
    if(dt >= 100)
    {
        this->deactivate();
        return false;
    }
    else
    {
        return true;
    }
}

void bullet::setSize(int newSize)
{
    size = newSize;

    if(size > 20)
    {
        size = 20;
    }
}

int bullet::getSize()
{
    return size;
}

void bullet::setVel(int newVel)
{
    bulletAddVel = newVel;
}

int bullet::getVel()
{
    return bulletAddVel;
}

bullet::~bullet()
{
    delete timer;
}

void bullet::update()
{
    moveBy(bulletX, bulletY);
    this->active();
    dt++;
}

