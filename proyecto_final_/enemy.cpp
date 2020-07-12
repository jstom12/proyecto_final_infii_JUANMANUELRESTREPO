#include "enemy.h"

enemy::enemy()
{

}

enemy::enemy(int x, int y, int t)
{
    posx = x;
    posy = y;
    type = t;
}

QRectF enemy::boundingRect() const
{
    return QRectF(-r,-r,2*r,2*r);
}

void enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::darkRed);
    painter->drawRect(boundingRect());
}

void enemy::definir_parametros()
{
    if(type==1)
    {
        velocidad=1;
        vida=50;
        dano=20;
    }
    if(type==2)
    {
        velocidad=0.8;
        vida=60;
        dano=30;
    }
    if(type==3)
    {
        velocidad=0.5;
        vida=100;
        dano=50;
    }
    if(type==4)
    {
        velocidad=1.5;
        vida=30;
        dano=10;
    }
}
