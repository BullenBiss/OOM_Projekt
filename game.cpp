#include "game.h"
game::game()
{
    QTimer * timer = new QTimer();                              //Skapa timer
    connect(timer, SIGNAL(timeout()), this, SLOT(gameUpdate()));//Koppla till medlemmen update()
    timer->start(1000/60);                                      //60fps typ
}

game::~game()
{
    text.clear();
    asteroid.clear();
    delete Ship1;
    delete Bullet;
    delete Arena;
}

void game::initiate()
{
    qDebug() << "initiate";

    Arena->create();
    this->addBackground();
    Arena->addToScene(Ship1);

    this->spawnWave();

    for(int i = 0; i <= 2; i++) //Create vector of text
    {
        text.push_back(new gameText());
    }
    Arena->addToScene(text[0]); //lives
    Arena->addToScene(text[1]); //score
    Ship1->setFlag(QGraphicsItem::ItemIsFocusable);
    Ship1->setFocus();
    text[0]->position(Arena->getWidth()/3, -Arena->getHeight()/3);
    text[1]->position((-Arena->getWidth()/3), (-Arena->getHeight()/3));

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
    if(asteroid.empty())
    {
        waveTimer++;
        if(waveTimer == 100)
        {
            spawnWave();
            waveTimer = 0;
        }
    }

    for(int h = 0; h < asteroid.size(); h++)
    {
        asteroid[h]->update();
        Arena->bounds(asteroid[h]);
        if(collisionDetectionAsteroid(asteroid[h]))
        {
            Arena->removeFromScene(asteroid[h]);
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
    for(int n = 0; n <= 3; n++) //Create vector of asteroids
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
        Ship1->looseLife();
        Arena->removeFromScene(Ship1);
        if(Ship1->getLife() > 0)
        {
            Ship1->spawn();
            Ship1->resetVelocity();
            Arena->addToScene(Ship1);
            Ship1->setFocus();
        }
        else if (Ship1->getLife()==0)
        {
            text[2]->gameOver();
            Arena->addToScene(text[2]);
        }
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

void game::textUpdate()
{
    text[0]->displayInt(Ship1->getLife());
    text[1]->displayInt(Ship1->getScore());
}

void game::addBackground()
{
    QPixmap bgpixmap("C:/Users/Max Pettersson/Desktop/Skola/Objektorienterad mjukvaruutveckling/Projekt/bg.png");
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

void game::gameUpdate()     //Timer som updaterar spelet.
{
    Arena->bounds(Ship1);
    Ship1->update();
    shipUpdate();
    bulletUpdate();
    shotTimer++;
    asteroidUpdate();
    qDebug() << Ship1->x();
    textUpdate();
}
