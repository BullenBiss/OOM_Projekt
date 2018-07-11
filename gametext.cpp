#include "gametext.h"

gameText::gameText()
{
    this->setScale(5);
    this->setDefaultTextColor(Qt::white);
    this->setTransformOriginPoint(this->boundingRect().center());
}

void gameText::displayInt(int integer)
{
    this->setPlainText(QString::number(integer));
}

void gameText::position(int x, int y)
{
    this->setPos(x, y);
}

void gameText::textUpdate()
{

}

void gameText::gameOver()
{
    this->setPos(-300,0);
    this->setPlainText("Game Over\nPress ESC");
    this->setScale(10);
}
