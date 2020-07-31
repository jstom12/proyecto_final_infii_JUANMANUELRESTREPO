#ifndef BOLITA_H
#define BOLITA_H
#include <math.h>
#include <QGraphicsItem>
#include <QPainter>

#define PI 3.1416   //se define el numero PI como 3.1416 para utilizarlo en la funcion actualizar_posicion.


class bolita : public QGraphicsItem
{
    /*
    La clase bolita se utiliza para graficar el objeto que gira en la ruleta,
    para realizar el movimiento de giro (MOVIMIENTO CIRCULAR UNIFORME) es necesario utilizar
    los parametros de: radio,angulo(inicial),angulo2(contrario al centro),tiempo(delta),vel(velocidad del cuerpo).

    El resto de parametros se utilizan para graficar el objeto. (posx,posy,r)
    */

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
