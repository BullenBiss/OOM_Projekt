#include "game.h"
game::game()
{
    QTimer * timer = new QTimer();                              //Skapa timer
    connect(timer, SIGNAL(timeout()), this, SLOT(gameUpdate()));//Koppla till medlemmen update()
    timer->start(1000/60);                                      //60fps typ
}

game::~game()
{
    asteroid.clear();
    delete Ship1;
    delete Bullet;
    delete Arena;
}

void game::initiate()
{
    qDebug() << "initiate";
    Ship1->setRect(0,0,50,25);
    Ship1->setTransformOriginPoint(25,12.5);
    Ship1->setPos(-500, 0);

    Arena->create();
    Arena->addToScene(Ship1);
    for(int n = 0; n <= 3; n++)
    {
        asteroid.push_back(new asteroids());
        Arena->addToScene(asteroid[n]);
    }
    Ship1->setFlag(QGraphicsItem::ItemIsFocusable);
    Ship1->setFocus();
}

void game::shootEvent()
{
    if(Ship1->shoot())
    {
        for(int i = 0; i <= 4; i++)
        {
            if(shotTimer < 40)
            {
                return;
            }
            else if(!Bullet[i].active())
            {
                Bullet[i].activate();
                Bullet[i].setPos(Ship1->x()+20, Ship1->y()+12.5);
                Bullet[i].bulletVelocity(Ship1->getVelocity());
                Bullet[i].move(Ship1->rotation());
                Arena->addToScene(&Bullet[i]);
                shotTimer = 0;
                return;
            }
        }
    }

    for(int j = 0; j <= 4; j++)
    {
        if(!Bullet[j].active())
        {
            //Arena->removeItem(&Bullet[j]);
        }
    }
}

void game::asteroidUpdate()
{
    for(int h = 0; h < asteroid.size(); h++)
    {
        asteroid[h]->update();
        Arena->bounds(asteroid[h]);
        if(collisionDetectionAsteroid(asteroid[h]))
        {
            Arena->removeFromScene(asteroid[h]);
            if(asteroid[h]->getScaleX() > 25)
            {
                asteroid.push_back(new asteroids(asteroid[h]->x(), asteroid[h]->y(), asteroid[h]->getScaleX()/2, asteroid[h]->getScaleY()/2));
                Arena->addToScene(asteroid.back());
                asteroid.push_back(new asteroids(asteroid[h]->x(), asteroid[h]->y(), asteroid[h]->getScaleX()/2, asteroid[h]->getScaleY()/2));
                Arena->addToScene(asteroid.back());
            }
            asteroid.erase(asteroid.begin()+h);
        }
    }
}

void game::shipUpdate()
{
    shootEvent();
    if(collisionDetectionShip(Ship1))
    {
        Arena->removeFromScene(Ship1);
    }
}

void game::bulletUpdate()
{
    for(int j = 0; j <= 4; j++)  //Update each bullet
    {
        Bullet[j].update();
        Arena->bounds(&Bullet[j]);
    }
}

bool game::collisionDetectionAsteroid(asteroids *asteroid)
{
    QList<QGraphicsItem*> list = asteroid->collidingItems(); //Make a list of all items the asteroid collides with

    for(int element = 0; element < list.size(); element++)
    {
        bullet* bullet_cast = dynamic_cast<bullet*>(list[element]); /* Try and cast class bullet,
                                                                        if it works then the list contains a bullet*/
        if(bullet_cast)
        {
            bullet_cast->deactivate();                              //Deactivate the bullet that collides
            return true;
        }

    }
    return false;
}

bool game::collisionDetectionShip(ship *ship)
{
    QList<QGraphicsItem*> list = ship->collidingItems(); //Make a list of all items the asteroid collides with

    for(int element = 0; element < list.size(); element++)
    {
        asteroids* asteroid_cast = dynamic_cast<asteroids*>(list[element]);
        if(asteroid_cast)
        {
            return true;
        }

    }
    return false;
}

void game::gameUpdate()     //Timer som updaterar spelet.
{
    Arena->bounds(Ship1);
    Ship1->update();
    shipUpdate();
    bulletUpdate();
    shotTimer++;
    asteroidUpdate();
    qDebug() << Ship1->x();
}
