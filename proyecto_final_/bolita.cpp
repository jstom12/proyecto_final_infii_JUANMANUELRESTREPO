#include "bolita.h"

float bolita::getPosx() const
{
    return posx;
}

float bolita::getPosy() const
{
    return posy;
}

bolita::bolita()
{

}

bolita::bolita(float x, float y, int r_)
{
    posx = x;
    posy = y;
    r = r_;
}

QRectF bolita::boundingRect() const
{
    return QRectF(-r,-r,2*r,2*r);
}

void bolita::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::blue);
    painter->drawEllipse(boundingRect());
}

void bolita::actualizar_posicion()
{
    if(angulo<=(PI/2) || angulo>=0)
    {
        radio=200;
    }
    if(angulo>(PI/2) || angulo<0)
    {
        radio=-200;
    }
    angulo = (vel/radio)*delta;
    angulo2 = (PI/2)-angulo;
    delta+=0.1;
    posx=sin(angulo2)*radio;
    posy=sin(angulo)*radio;
    setPos(posx,posy);
}
