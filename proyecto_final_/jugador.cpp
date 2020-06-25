#include "jugador.h"

int jugador::getPosx() const
{
    return posx;
}

int jugador::getPosy() const
{
    return posy;
}

jugador::jugador()
{

}

jugador::jugador(int x, int y, int r_)
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
    posx+= 10;
    setPos(posx,posy);
}

void jugador::move_left()
{
    posx-= 10;
    setPos(posx,posy);
}

void jugador::move_up()
{
    posy-=10;
    setPos(posx,posy);
}

void jugador::move_down()
{
    posy+= 10;
    setPos(posx,posy);
}
