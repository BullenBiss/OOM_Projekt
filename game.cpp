#include "game.h"
game::game()
{

}

game::~game()
{
    text.clear();
    asteroid.clear();
    delete power;
    delete timer;
    delete Ship1;
    delete ghostShip;
    delete Bullet;
    delete background;
    delete Arena;
    delete s;
}

void game::initiate()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(gameUpdate()));//Koppla till medlemmen update()
    timer->start(1000/60);

    wave = 1;
    Arena->create();
    this->addBackground();
    Arena->addToScene(Ship1);
    Arena->setStickyFocus(true);

    for(int i = 0; i <= 4; i++) //Create vector of text
    {
        text.push_back(new gameText());
    }
    Arena->addToScene(text[0]); //lives
    Arena->addToScene(text[1]); //score

    text[0]->position(Arena->getWidth()/3, -Arena->getHeight()/3);
    text[1]->position((-Arena->getWidth()/3), (-Arena->getHeight()/3));

    text[2]->setPlainText("Wave");
    text[2]->position(-300,0);

    text[3]->position(0,0);

    Ship1->setActive(true);
    Ship1->setFlag(QGraphicsItem::ItemIsFocusable);
    Ship1->setFocus();
    Ship1->setPanelModality(QGraphicsItem::SceneModal);

    ghostShip->setFlag(QGraphicsItem::ItemIsFocusable);
    ghostShip->setPos(-3000,-3000);
    Arena->addToScene(ghostShip);
    s->soundInitiate();

    shotLimit = 80;
    bulletNr = 4;
}

void game::shootEvent()
{
    if(Ship1->shoot())
    {
        for(int i = 0; i <= bulletNr; i++)
        {
            if(shotTimer < shotLimit)
            {
                return;
            }
            else if(!Bullet[i].active())
            {
                s->soundShoot();
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
}

void game::asteroidUpdate()
{
    if(asteroid.empty())
    {

        text[3]->displayInt(wave);
        Arena->addToScene(text[2]);
        Arena->addToScene(text[3]);
        waveTimer++;
        if(waveTimer == 200)
        {
            wave++;
            spawnWave();
            waveTimer = 0;
            Arena->removeFromScene(text[2]);
            Arena->removeFromScene(text[3]);
        }
    }

    for(int h = 0; h < asteroid.size(); h++)
    {
        asteroid[h]->update();
        Arena->bounds(asteroid[h]);
        if(collisionDetectionAsteroid(asteroid[h]))
        {
            Arena->removeFromScene(asteroid[h]);
            s->soundAsteroidExplosion();
            if(asteroid[h]->getScaleX() > 40)
            {
                asteroid.push_back(new asteroids(asteroid[h]->x(), asteroid[h]->y(), asteroid[h]->getScaleX()/2, asteroid[h]->getScaleY()/2));
                Arena->addToScene(asteroid.back());
                asteroid.push_back(new asteroids(asteroid[h]->x(), asteroid[h]->y(), asteroid[h]->getScaleX()/2, asteroid[h]->getScaleY()/2));
                Arena->addToScene(asteroid.back());
            }
            asteroid.erase(asteroid.begin()+h);
            Ship1->addScore();
        }
    }
}

void game::spawnWave()
{
    for(int n = 0; n <= wave; n++) //Create vector of asteroids
    {
        asteroid.push_back(new asteroids());
        Arena->addToScene(asteroid[n]);
    }
}

void game::shipUpdate()
{
    shootEvent();
    if(collisionDetectionShip(Ship1))
    {
        Ship1->resetInput();
        Ship1->setActive(false);
        ghostShip->setFocus();
        Ship1->explosion();
        Ship1->resetVelocity();
        lifeTimer = 0;
        s->soundShipExplosion();
    }

    if(!Ship1->active() && lifeTimer >= 100)
    {

        Arena->removeFromScene(Ship1);
        if(Ship1->getLife() > 0)
        {
            Ship1->looseLife();
            Ship1->spawn();
            Arena->addToScene(Ship1);
            Ship1->setActive(true);
            Ship1->setFocus();
            this->resetValues();
        }
        else if (Ship1->getLife()==0)
        {
            text[2]->gameOver();
            Arena->addToScene(text[2]);
            ghostShip->setFocus();
            if(ghostShip->escKey())
            {
                timer->stop();
                Arena->hide();
                this->~game();
                return;
            }
        }

    }
    if(!Ship1->hasFocus() && Ship1->active())
    {
        Ship1->setFocus();
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

void game::powerupUpdate()
{
    if(collisionDetectionPowerup(power))
    {
        if(power->getId() == 1)
        {
            Ship1->addLife();
            power->setActive(false);
            Arena->removeFromScene(power);

            powerupTimer = 0;
        }
        else if(power->getId() == 2)
        {
            shotLimit -= 20;
            if(shotLimit < 20)
            {
                shotLimit = 10;
            }

            power->setActive(false);
            Arena->removeFromScene(power);
            powerupTimer = 0;
        }
        else if(power->getId() == 3)
        {
            for(int k = 0; k <= bulletNr; k++)
            {
                Bullet[k].setSize(Bullet[k].getSize() + 4);
            }

            power->setActive(false);
            Arena->removeFromScene(power);
            powerupTimer = 0;
        }
        else if(power->getId() == 4)
        {
            for(int k = 0; k <= bulletNr; k++)
            {
                Bullet[k].setVel(Bullet[k].getVel() + 2);
            }
            power->setActive(false);
            Arena->removeFromScene(power);
            powerupTimer = 0;
        }
    }

   if(powerupTimer <= 1000)
   {
       powerupTimer++;
   }
   else if(!power->active())
   {
       power->spawnPowerup();
       power->setActive(true);
       Arena->addToScene(power);
   }

}

void game::textUpdate()
{
    text[0]->displayInt(Ship1->getLife());
    text[1]->displayInt(Ship1->getScore());
}

void game::addBackground()
{
    QPixmap bgpixmap(":/new/images/bg.png");
    //bgpixmap.scaled(QSize(200, 150));
    background->setPixmap(bgpixmap);
    background->setPos(-Arena->getWidth()/2, -Arena->getHeight()/2);

    Arena->addToScene(background);
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

bool game::collisionDetectionPowerup(powerup *Power)
{
    QList<QGraphicsItem*> list = Power->collidingItems(); //Make a list of all items the asteroid collides with

    for(int element = 0; element < list.size(); element++)
    {
        ship* power_cast = dynamic_cast<ship*>(list[element]);
        if(power_cast)
        {
            return true;
        }

    }
    return false;
}

void game::resetValues()
{
    for(int h = 0; h <= bulletNr; h++)
    {
        Bullet[h].setSize(10);
        Bullet[h].setVel(6);
    }
    shotLimit = 80;
}

void game::gameUpdate()     //Timer som updaterar spelet.
{

       Arena->bounds(Ship1);
       Ship1->update();
       bulletUpdate();
       shotTimer++;
       lifeTimer++;
       asteroidUpdate();
       textUpdate();
       powerupUpdate();
       shipUpdate();

}
