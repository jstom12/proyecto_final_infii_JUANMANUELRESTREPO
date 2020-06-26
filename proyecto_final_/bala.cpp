#include "bala.h"

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
    posx+= posx + vel;
    setPos(posx,posy);
}

void bala::left()
{
    posx-= posx + vel;
    setPos(posx,posy);
}

void bala::up()
{
    posy-= posy + vel;
    setPos(posx,posy);
}

void bala::down()
{
    posy+= posy + vel;
    setPos(posx,posy);
}

bala::bala()
{

}

bala::bala(int x, int y, int r_)
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
