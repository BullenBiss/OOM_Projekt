#include "game.h"
game::game()
{
    QTimer * timer = new QTimer();                              //Skapa timer
    connect(timer, SIGNAL(timeout()), this, SLOT(gameUpdate()));//Koppla till medlemmen update()
    timer->start(1000/60);                                      //60fps typ
}

void game::initiate()
{
    qDebug() << "initiate";
    Ship1->setRect(0,0,50,25);
    Ship1->setTransformOriginPoint(25,12.5);
    Ship1->setPos(-500, 0);

    asteroid.push_back(new asteroids());
    asteroid.push_back(new asteroids(50,50,40,40));

    Arena->create();
    Arena->addToScene(Ship1);
    Arena->addToScene(asteroid[0]);
    Arena->addToScene(asteroid[1]);
    Ship1->setFlag(QGraphicsItem::ItemIsFocusable);
    Ship1->setFocus();

}


void game::shootEvent()
{
    if(Ship1->shoot())
    {
        for(int i = 0; i <= 4; i++)
        {
            if(shotTimer < 10)
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
            asteroid.erase(asteroid.begin()+h);
        }
    }
}

bool game::collisionDetectionAsteroid(asteroids *asteroid)
{
    QList<QGraphicsItem*> list = asteroid->collidingItems(); //Make a list of all items the asteroid collides with

    for(int element = 0; element < list.size(); element++)
    {
        bullet* bullet_cast = dynamic_cast<bullet*>(list[element]);
        if(bullet_cast)
        {
            qDebug() << "TRUE CAST";
            return true;
        }

    }
    qDebug() << "FALSE RETURN";
    return false;
}

void game::gameUpdate()     //Timer som updaterar spelet.
{
    Arena->bounds(Ship1);
    Ship1->update();
    this->shootEvent();
    for(int j = 0; j <= 4; j++)  //Update each bullet
    {
        Bullet[j].update();
        Arena->bounds(&Bullet[j]);
    }
    shotTimer++;
    asteroidUpdate();
}
