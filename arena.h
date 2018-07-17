#ifndef ARENA_H
#define ARENA_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "ship.h"
#include <QRectF>
#include <QGraphicsItem>
#include <QScreen>



class arena : public QGraphicsScene
{
public:
    arena();
    arena(int width, int height);
    ~arena();
    void create(); //Lägg till ship2 när den ska implementeras
    void bounds(QGraphicsItem *Ship);
    void setResolution(int width, int height);
    int getWidth();
    int getHeight();
    void hide();
    void addToScene(QGraphicsItem *item);
    void removeFromScene(QGraphicsItem *item);
private:
    int sceneWidth;
    int sceneHeight;   //Lägger den här så att jag kan skapa en "addToScene" medlem
    QGraphicsScene * scene = new QGraphicsScene(0,0,1920,1080);
    QGraphicsView * view = new QGraphicsView(scene);
};

#endif // ARENA_H
