#include "bullet.h"

bullet::bullet()
{
    this->setRect(0,0,12,12);
    this->setOpacity(1.0);
    this->setBrush(Qt::SolidPattern);

}

void bullet::move(double shipAngleIn)
{
    shipAngle = (shipAngleIn * pi)/180;     //Skriv om vinkeln till radianer
    bulletY = sin(shipAngle) * bulletV;     //Komposantuppdelning av V
    bulletX = cos(shipAngle) * bulletV;     //Komposantuppdelning av V
}

void bullet::bulletVelocity(float shipV)
{
    bulletV = shipV + 6;
}


void bullet::update()
{
    moveBy(bulletX, bulletY);
}

