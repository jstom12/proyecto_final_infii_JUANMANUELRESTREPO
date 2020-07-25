#ifndef BOLITA_H
#define BOLITA_H
#include <math.h>
#include <QGraphicsItem>
#include <QPainter>

#define PI 3.1416


class bolita : public QGraphicsItem
{
    float posx,posy,radio,angulo=0,delta=0.1,vel=50,angulo2;
    int r=10;



public:
    bolita();
    bolita(float x, float y, int r_);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    void actualizar_posicion();
    float getPosx() const;
    float getPosy() const;
};

#endif // BOLITA_H
