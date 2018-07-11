
#include "ship.h"


ship::ship()
{
    QPixmap pixmap("C:/Users/Max Pettersson/Desktop/Skola/Objektorienterad mjukvaruutveckling/Projekt/Spaceship.png");
    QPixmap scaled = pixmap.scaled(QSize(scaleX, scaleY));
    this->setPixmap(scaled);
    this->setTransformOriginPoint(scaleX/2,scaleY/2);
    this->spawn();
    lives = 3;
    score = 0;
}

void ship::keyPressEvent(QKeyEvent *event)                //Styr då knappen trycks in
{
    switch(event->key())
    {
        case Qt::Key_Left:              //Flaggar att knappen är i-tryckt
        {
            rotateLeft = true;
            break;
        }
        case Qt::Key_Right:
        {
            rotateRight = true;
            break;
        }
        case Qt::Key_Up:
        {
            forwardPress = true;
            break;
        }
        case Qt::Key_Space:
        {
            shootPress = true;
            break;
        }
        case Qt::Key_Escape:
        {
            QApplication::quit();
            break;
        }
    }

}

void ship::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())
    {
     case Qt::Key_Up:
     {
        forwardPress = false;
        V = 0;
        break;

     }
    case Qt::Key_Left:
    {
        rotateLeft = false;
        break;
    }
    case Qt::Key_Right:
    {
        rotateRight = false;
        break;
    }
    case Qt::Key_Space:
    {
        shootPress = false;
        break;
    }
    }
}

void ship::spawn()
{
    this->setPos(-500,0);
}

void ship::addLife()
{
    lives++;
}

void ship::addScore()
{
    score += 10;
}

int ship::getScore()
{
    return score;
}

void ship::resetScore()
{
    score = 0;
}

void ship::looseLife()
{
    lives--;
}

int ship::getLife()
{
    return lives;
}

void ship::movement()                     //Tar in-tryckt flaggan och utför utan delayen
{

    if(rotateLeft && forwardPress)
    {
        setRotation(rotation() - angle/2);
        V += acc;
        velocityVector();
    }

    if(rotateRight && forwardPress)
    {
        setRotation(rotation() + angle/2);
        V += acc;
        velocityVector();
    }

    if(rotateLeft)
    {
        setRotation(rotation() - angle);
    }

    if(rotateRight)
    {
        setRotation(rotation() + angle);
    }

    if(forwardPress)                        //Acc framåt
    {
        V += acc;
        velocityVector();
    }
    moveBy(VMx, VMy);
}

void ship::velocityVector()
{

    if(V >= 0.05)       //Smoothar accelerationskurvan
    {
        V = 0.05;
    }

    angleRad = (rotation() * pi)/180;     //Skriv om vinkeln till radianer
    Vy = sin(angleRad) * V;                     //Komposantuppdelning av V
    Vx = cos(angleRad) * V;                     //Komposantuppdelning av V

    VMx += Vx;                                  //Rörelsevektorn för skeppet. Simulerar 2 olika vektorer för skeppet
    if(VMx >= Vmax)
    {
        VMx = Vmax;
    }
    else if(VMx <= -Vmax)
    {
        VMx = -Vmax;
    }

    VMy += Vy;
    if(VMy >= Vmax)
    {
        VMy = Vmax;
    }
    else if(VMy <= -Vmax)
    {
        VMy = -Vmax;
    }

    Vx = 0;                                     //Sätter tillbaka till noll, annars ökar hastigheten hela tiden vid accelation. Den kör accelerationskurvan en gång bara
    Vy = 0;

}

float ship::getVelocity()
{
    return abs(VMx)+abs(VMy);
}

void ship::resetVelocity()
{
    VMx = 0;
    VMy = 0;
}

bool ship::shoot()
{
    if(shootPress){
        return true;
    }
    else
    {
        return false;
    }
}

double ship::getAngle()
{
    double returnAngle = rotation();
    return returnAngle;
}


void ship::update()
{
    movement();
    shoot();
    getAngle();
}
