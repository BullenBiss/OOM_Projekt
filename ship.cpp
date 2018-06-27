
#include "ship.h"


ship::ship()
{
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

bool ship::shoot()
{
    if(shootPress){
        return true;
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
    moveBy(VMx, VMy);
    shoot();
    getAngle();
}
