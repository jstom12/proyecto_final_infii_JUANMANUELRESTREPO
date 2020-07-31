#include "pared.h"

pared::pared()
{

}

pared::pared(int x, int y, int a, int l)
{
    posx = x;
    posy = y;
    anc = a;
    large = l;
}

QRectF pared::boundingRect() const
{
    /*
    Se utilizar las variables de la clase para crear un rectangulo en la posicion x,y con un ancho y un largo.
    */
    return QRect(-posx,-posy,anc,large);
}

void pared::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setBrush(Qt::yellow);
    painter->drawRect(boundingRect());
}
