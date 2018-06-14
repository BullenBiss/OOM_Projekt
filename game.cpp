#include "game.h"
game::game()
{
    QTimer * timer = new QTimer();                              //Skapa timer
    connect(timer, SIGNAL(timeout()), this, SLOT(gameUpdate()));    //Koppla till medlemmen update()
    timer->start(1000/60);                                      //60fps typ

}

void game::initiate()
{
    Ship1->setRect(0,0,50,25);
    Ship1->setTransformOriginPoint(25,12.5);
    Ship1->setPos(-500, 0);

    Arena->create();
    Arena->addToScene(Ship1);

    Ship1->setFlag(QGraphicsItem::ItemIsFocusable);
    Ship1->setFocus();

}


void game::shootEvent()
{

    if(Ship1->shoot() && shoot != true)
    {
        shoot = true;
        dt = 0;
        Bullet = new bullet;
        Bullet->setPos(Ship1->x()+20, Ship1->y()+12.5);
        Bullet->bulletVelocity(Ship1->getVelocity());
        Bullet->move(Ship1->rotation());

        Arena->addToScene(Bullet);
    }

    if(dt == 100)
    {
        shoot = false;
        Arena->removeItem(Bullet);
        delete Bullet;
    }
}


void game::gameUpdate()     //Timer som updaterar spelet.
{
    Arena->bounds(Ship1);
    Ship1->update();
    shootEvent();
    dt += 1;
    if (shoot)
    {
        Bullet->update();
    }
}
