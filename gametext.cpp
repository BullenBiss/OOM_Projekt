#include "gametext.h"

gameText::gameText()
{
    this->setScale(5);
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
