#include "arena.h"

arena::arena()
{

    QRect screenGeometry = screen->geometry();
    sceneWidth = screenGeometry.width() - 10;
    sceneHeight = screenGeometry.height() - 75;
}

void arena::setResolution(int width, int height)
{
    sceneWidth = width;
    sceneHeight = height;
}

arena::~arena()
{
    delete scene;
    delete view;
}

void arena::create()
{

    view->setFixedSize(sceneWidth, sceneHeight);
    QRectF sceneRect(0,0,sceneWidth,sceneHeight);
    sceneRect.setCoords(-(sceneWidth/2), sceneHeight/2, sceneWidth/2, -(sceneHeight/2));    //Sätter origo i mitten av arenan istället för i hörnet.

    view->setSceneRect(sceneRect);
    view->show();
}

void arena::bounds(QGraphicsItem *Ship)  //Skickar in ship-klass och definierar arenagränserna
{
    if(Ship->x() > sceneWidth/2)
    {
        Ship->setX(-(sceneWidth/2));
    }
    else if(Ship->x() < (-sceneWidth/2))
    {
        Ship->setX(sceneWidth/2);
    }
    else if(Ship->y() < -(sceneHeight/2))
    {
        Ship->setY(sceneHeight/2);
    }
    else if(Ship->y() > sceneHeight/2)
    {
        Ship->setY(-(sceneHeight/2));
    }
}

int arena::getWidth()
{
    return sceneWidth;
}

int arena::getHeight()
{
    return sceneHeight;
}

void arena::hide()
{
    view->setFixedSize(0,0);
}

void arena::addToScene(QGraphicsItem *item)
{
    scene->addItem(item);
}

void arena::removeFromScene(QGraphicsItem *item)
{
    scene->removeItem(item);
}
