#ifndef SUELO_H
#define SUELO_H
#include <QGraphicsItem>
#include <QPainter>


class suelo: public QGraphicsItem
{
    /*
    La clase suelo tiene las variables posx,posy,w,h exclusivas para la grafica del suelo y las
    variables type,resistencia necesarias para la jugabilidad.
    */
    int type,posx,posy,w,h;
    float resistencia; // esta variable quedo obsoleta al encontrar una mejor manera de conseguir la inercia.

public:
    suelo();
    suelo(int x,int y,int anc,int large,int ty);


    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    void definir_resistencia();
    float getResistencia() const;
};

#endif // SUELO_H
