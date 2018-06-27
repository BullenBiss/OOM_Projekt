#ifndef ARENA_H
#define ARENA_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "ship.h"
#include <QRectF>
#include <QGraphicsItem>



class arena : public QGraphicsScene
{
public:
    arena();
    arena(int width, int height);
    void create(); //Lägg till ship2 när den ska implementeras
    void bounds(QGraphicsItem *Ship);
    void setResolution(int width, int height);
    int getWidth();
    int getHeight();
    void addToScene(QGraphicsItem *item);
    void removeFromScene(QGraphicsItem *item);
private:
    int sceneWidth = 0;
    int sceneHeight = 0;   //Lägger den här så att jag kan skapa en "addToScene" medlem
    QGraphicsScene * scene = new QGraphicsScene;
};

#endif // ARENA_H
