#ifndef PARED_H
#define PARED_H
#include <QGraphicsItem>
#include <QPainter>


class pared: public QGraphicsItem
{
    /*
    Esta clase grafica las paredes del juego, las variables que se utilizar son unicamente para
    graficar la clase como objeto grafico.
    */
    int posx,posy,anc,large;

public:
    pared();
    pared(int x,int y,int a,int l);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

};

#endif // PARED_H
