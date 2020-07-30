#include "bolita.h"
/*
Ademas de las funciones comunces de get, set y las que vuelven la clas eun objeto grafico, tenemos la de
actualizar posicion que se explica mas a detalle en ella.

*/
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
    /*
    Esta funcion utilizar las ecuaciones del movimiento circular acelerado para graficar la posicion del objeto.
    Era necesario un metodo que cambiase el valor del radio entre positivo y negativo para que la formula graficara el ciruclo
    completo, por lo tanto, se agregaron dos condiciones que indican el valor del radio; positivo si se encuentra entre 90 y 0 grados
    y negativo si se encuentra en un grado distinto. Luego, utilizando la ley del seno, conseguimos los valores para posx y posy.
    */

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
