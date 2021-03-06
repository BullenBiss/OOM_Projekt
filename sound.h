#ifndef SOUND_H
#define SOUND_H

#include <QMediaPlayer>
#include <String>

using namespace std;

class sound: public QMediaPlayer
{
public:
    sound();
    void soundInitiate();
    void soundShoot();
    void soundAsteroidExplosion();
    void soundShipExplosion();
    void soundPowerup();

private:
    QMediaPlayer shootSound;
    QMediaPlayer asteroidExplosion;
    QMediaPlayer shipExplosion;
    QMediaPlayer powerupSound;
};

#endif // SOUND_H
