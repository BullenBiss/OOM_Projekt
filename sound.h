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
    void makeSound(string sound);
    void soundShoot();
    void soundAsteroidExplosion();
    void soundShipExplosion();

private:
    QMediaPlayer shootSound;
    QMediaPlayer asteroidExplosion;
    QMediaPlayer shipExplosion;
};

#endif // SOUND_H
