#include "jugador.h"

int jugador::getPosx() const
{
    return posx;
}

int jugador::getPosy() const
{
    return posy;
}

int jugador::getDir() const
{
    return dir;
}

void jugador::setDir(int value)
{
    dir = value;
}

void jugador::setR(int value)
{
    r = value;
}

int jugador::getVida() const
{
    return vida;
}

void jugador::setVida(int value)
{
    vida = value;
}

void jugador::setResis(float value)
{
    resis = value;
}

int jugador::getMapa() const
{
    return mapa;
}

void jugador::setMapa(int value)
{
    mapa = value;
}

float jugador::getResis() const
{
    return resis;
}

int jugador::getRonda() const
{
    return ronda;
}

void jugador::setRonda(int value)
{
    ronda = value;
}

jugador::jugador()
{
    
}

jugador::jugador(float x,float y,float r_)
{
    posx = x;
    posy = y;
    r = r_;
    setPos(posx,posy);
}

QRectF jugador::boundingRect() const
{
    return QRectF(-r,-r,2*r,2*r);
}

void jugador::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
    painter->drawRect(boundingRect());

}

void jugador::move_right()
{
    posx+= (10-resis);
    setPos(posx,posy);
}

void jugador::move_left()
{
    posx-= (10-resis);
    setPos(posx,posy);
}

void jugador::move_up()
{
    posy-=(10-resis);
    setPos(posx,posy);
}

void jugador::move_down()
{
    posy+= (10-resis);
    setPos(posx,posy);
}
