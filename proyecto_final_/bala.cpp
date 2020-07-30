#include "bala.h"


/*
Para realizar los movimientos estan 4 funciones que corresponden a cada lado en el que puede viajar el disparo;
todos funcionan de la misma manera, se le suma la velocidad a la posicion actual y se le resta esa misma posicion
pero sin la suma de la velocidad y el resultado se suma a la posicion actual, asi se recrea un trayecto corto
por parte de la bala.


*/
void bala::setPosx(int value)
{
    posx = value;
}

void bala::setPosy(int value)
{
    posy = value;
}

void bala::right()
{
    posx+= ((posx+vel)-posx);
    setPos(posx,posy);
}

void bala::left()
{
    posx+= (posx-(posx+vel));
    setPos(posx,posy);
}

void bala::up()
{
    posy += (posy-(posy+vel));
    setPos(posx,posy);
}

void bala::down()
{
    posy+= ((posy+vel)-posy);
    setPos(posx,posy);
}

int bala::getDamage() const
{
    return damage;
}

void bala::setDamage(int value)
{
    damage = value;
}

bala::bala()
{

}

bala::bala(float x, float y,float  r_)
{
    posx = x;
    posy = y;
    r = r_;
}

QRectF bala::boundingRect() const
{
    return QRectF(-r,-r,2*r,2*r);
}

void bala::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::blue);
    painter->drawEllipse(boundingRect());
}
