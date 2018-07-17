#ifndef POWERUP_H
#define POWERUP_H

#include <QGraphicsItem>

class powerup : public QGraphicsPixmapItem
{
public:
    powerup();
    powerup(int width, int height);
    ~powerup();
    void spawnPowerup();
    void randomPos();
    void randomId();
    int getId();
    void setActive(bool active);
    bool active();
    void setSpawnLimits(int width, int height);

private:
    int _X;
    int _Y;
    int _scale;
    int _id;
    int _width;
    int _height;
    bool _active;
    QPixmap *hpMap = new QPixmap(":/new/images/hp.png");
    QPixmap *shotMap = new QPixmap(":/new/images/shot.png");
    QPixmap *bulletMap = new QPixmap(":/new/images/bulletSize.png");
    QPixmap *velMap = new QPixmap(":/new/images/bulletVel.png");
};

#endif // POWERUP_H
