#include "powerup.h"

powerup::powerup()
{
    _scale = 16;
    hpMap->scaled(QSize(_scale, _scale));
    shotMap->scaled(QSize(_scale, _scale));

}

powerup::~powerup()
{
    delete hpMap;
    delete shotMap;
    delete bulletMap;
    delete velMap;
}

void powerup::spawnPowerup()
{
    this->randomId();

    if(_id == 1)
    {
        this->setPixmap(*hpMap);
    }
    else if(_id == 2)
    {
        this->setPixmap(*shotMap);
    }
    else if(_id == 3)
    {
        this->setPixmap(*bulletMap);
    }
    else if(_id == 4)
    {
        this->setPixmap(*shotMap);
    }

    this->randomPos();
}

void powerup::randomPos()
{
    _X = (rand() % 1400) - 700;
    _Y = (rand() % 600) - 300;
    this->setPos(_X,_Y);
}

void powerup::randomId()
{
    _id = (rand() % 4) + 1;
}

int powerup::getId()
{
    return _id;
}

void powerup::setActive(bool active)
{
    _active = active;
}

bool powerup::active()
{
    return _active;
}
