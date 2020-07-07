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
    return QRect(-posx,-posy,anc,large);
}

void pared::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QPixmap pixmap;
    pixmap.load(":/new/prefix1/resources/puas.jpg");
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
}
