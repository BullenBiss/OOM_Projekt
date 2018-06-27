#include "bullet.h"

bullet::bullet()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));    //Koppla till medlemmen update()
    this->setRect(0,0,0,0);
    this->setOpacity(0.0);
    this->setBrush(Qt::SolidPattern);
    dt = 0;
}

void bullet::move(double shipAngleIn)
{
    shipAngle = (shipAngleIn * pi)/180;     //Skriv om vinkeln till radianer
    bulletY = sin(shipAngle) * bulletV;     //Komposantuppdelning av V
    bulletX = cos(shipAngle) * bulletV;     //Komposantuppdelning av V
}

void bullet::bulletVelocity(float shipV)
{
    bulletV = abs(shipV) + 6;
}

void bullet::activate()
{
    dt = 0;
    timer->start(1000/60);                                      //60fps typ

    this->setRect(0,0,12,12);
    this->setOpacity(1.0);
    this->setBrush(Qt::SolidPattern);
}

bool bullet::active()
{
    if(dt >= 100)
    {
        timer->stop();
        this->setRect(0,0,0,0);
        this->setOpacity(0.0);
        this->setBrush(Qt::SolidPattern);
        return false;
    }
    else
    {
        return true;
    }
}

bullet::~bullet()
{
    delete this;
}

void bullet::update()
{
    moveBy(bulletX, bulletY);
    this->active();
    dt++;
}

