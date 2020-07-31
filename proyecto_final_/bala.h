#ifndef BALA_H
#define BALA_H
#include <QPainter>
#include <QGraphicsItem>

class bala : public QGraphicsItem
{
    /*
    La clase bala tiene los parametros de posx y posy para su ubicacion en la escena; r para su tamano grafico en esta misma;
    Vel para definir la velocidad en la que viajara el cuerpo; damage para definir cuanto quitara al impactar.

    */
    float posx,posy,r;
    double vel=5;
    int damage=20; // esta variable cambia en el codigo principal del juego, permitiendo aumentar la dificultad.

public:
    bala();
    bala(float x, float y, float r_);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    void setPosx(int value);
    void setPosy(int value);
    void right();
    void left();
    void up();
    void down();

    int getDamage() const;
    void setDamage(int value);
};

#endif // BALA_H
