#include "suelo.h"

float suelo::getResistencia() const
{
    return resistencia;
}

suelo::suelo()
{

}

suelo::suelo(int x, int y, int anc, int large, int ty)
{
    posx = x;
    posy = y;
    w = anc;
    h = large;
    type=ty;

}

QRectF suelo::boundingRect() const
{
    return QRect(-posx,-posy,w,h);
}

void suelo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(type==1)
    {
        painter->setBrush(Qt::lightGray);
        painter->drawRect(boundingRect());
    }
    if(type==2)
    {
        painter->setBrush(Qt::green);
        painter->drawRect(boundingRect());
    }
    if(type==3)
    {
        painter->setBrush(Qt::cyan);
        painter->drawRect(boundingRect());
    }

}

void suelo::definir_resistencia()
{
    if(type==1)
    {
        resistencia = 1;
        return;
    }
    if(type==2)
    {
        resistencia = 0.8;
        return;
    }
    if(type==3)
    {
        resistencia = 0.5;
        return;
    }
}
