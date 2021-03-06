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
    /*
    Vemos que, para pintar el objeto grafico, es necesario la variable type que nos indica de que tipo es el suelo
    a graficarse; dependiendo el tipo el color sera diferente.
    */
    if(type==1)
    {
        painter->setBrush(Qt::lightGray);
        painter->drawRect(boundingRect());
    }
    if(type==2)
    {
        painter->setBrush(QPixmap(":/new/prefix1/resources/hierba.png"));
        painter->drawRect(boundingRect());
    }
    if(type==3)
    {
        painter->setBrush(QPixmap(":/new/prefix1/resources/agua_suelo.png"));
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
        resistencia = 3;
        return;
    }
    if(type==3)
    {
        resistencia = 5;
        return;
    }
}
