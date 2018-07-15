#include "sound.h"

sound::sound()
{

}

void sound::soundInitiate()
{
    shootSound.setMedia(QUrl("qrc:/sounds/shootSound.wav"));
    asteroidExplosion.setMedia(QUrl("qrc:/sounds/asteroidExplosion.wav"));
    shipExplosion.setMedia(QUrl("qrc:/sounds/shipExplosion.wav"));
}

void sound::soundShoot()
{
    shootSound.play();
}

void sound::soundAsteroidExplosion()
{
    asteroidExplosion.play();
}

void sound::soundShipExplosion()
{
    shipExplosion.play();
}
void sound::makeSound(string sound)
{

    if(sound.compare("shoot"))
    {
        asteroidExplosion.play();
    }
    else if(sound.compare("asteroidExplosion"))
    {

    }
    else if(sound.compare("shipExplosion"))
    {
        shipExplosion.play();
    }
    else
    {
        return;
    }

}

