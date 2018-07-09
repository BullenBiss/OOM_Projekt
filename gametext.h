#ifndef GAMETEXT_H
#define GAMETEXT_H

#include <QObject>
#include <QGraphicsItem>
#include <QString>
class gameText : public QGraphicsTextItem
{
public:
    gameText();
    void displayInt(int integer);
    void position(int x, int y);
    void textUpdate();
    void gameOver();
};

#endif // GAMETEXT_H
