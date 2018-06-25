#include "bullet.h"

bullet::bullet()
{
    QTimer * timer = new QTimer();                              //Skapa timer
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));    //Koppla till medlemmen update()
    timer->start(1000/60);                                      //60fps typ

    this->setRect(0,0,12,12);
    this->setOpacity(1.0);
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
    bulletV = shipV + 6;
}

void bullet::lifeTime()
{
    if(dt == 100)
    {
        this->~bullet();
    }
}

bullet::~bullet()
{
    delete this;
}

void bullet::update()
{
    moveBy(bulletX, bulletY);
    this->lifeTime();
    dt++;
}

