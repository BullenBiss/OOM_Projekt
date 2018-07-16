#ifndef POWERUP_H
#define POWERUP_H

#include <QGraphicsItem>

class powerup : public QGraphicsPixmapItem
{
public:
    powerup();
    ~powerup();
    void spawnPowerup();
    void randomPos();
    void randomId();
    int getId();
    void setActive(bool active);
    bool active();

private:
    int _X;
    int _Y;
    int _scale;
    int _id;
    bool _active;
    QPixmap *hpMap = new QPixmap(":/new/images/hp.png");
    QPixmap *shotMap = new QPixmap(":/new/images/shot.png");
    QPixmap *bulletMap = new QPixmap(":/new/images/bulletSize.png");
    QPixmap *velMap = new QPixmap(":/new/images/bulleVel.png");
};

#endif // POWERUP_H
