#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <string>

using namespace std;
class ship;

class gameobject : public QGraphicsRectItem
{
public:
    gameobject();
};

#endif // GAMEOBJECT_H
