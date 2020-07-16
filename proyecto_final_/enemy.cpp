#include "enemy.h"

int enemy::getVida() const
{
    return vida;
}

void enemy::setVida(int value)
{
    vida = value;
}

void enemy::setResist(float value)
{
    resist = value;
}

int enemy::getMapa() const
{
    return mapa;
}

void enemy::setMapa(int value)
{
    mapa = value;
}

float enemy::getPosx() const
{
    return posx;
}

float enemy::getPosy() const
{
    return posy;
}

enemy::enemy()
{
    
}

enemy::enemy(float x, float y, int t)
{
    posx = x;
    posy = y;
    type = t;
    definir_parametros();
    setPos(posx,posy);
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
        velocidad=4;
        vida=50;
        dano=20;
    }
    if(type==2)
    {
        velocidad=3;
        vida=60;
        dano=30;
    }
    if(type==3)
    {
        velocidad=2;
        vida=100;
        dano=50;
    }
    if(type==4)
    {
        velocidad=5;
        vida=30;
        dano=10;
    }
}

void enemy::move_y(int player_y)
{
    if(player_y>posy)
    {
        posy = posy+(velocidad-resist);
        setPos(posx,posy);
    }
    if(player_y<posy)
    {
        posy= posy-(velocidad-resist);
        setPos(posx,posy);
    }
}

void enemy::move_x(int player_x)
{
    if(player_x>posx)
    {
        posx +=(velocidad-resist);
        setPos(posx,posy);
    }
    if(player_x<posx)
    {
        posx = posx-(velocidad-resist);
        setPos(posx,posy);
    }
}
