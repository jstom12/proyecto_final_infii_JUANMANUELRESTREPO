#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsItem>
#include <QPainter>
#include <math.h>

class enemy: public QGraphicsItem
{
    /*
    la clase enemigo tiene los parametros vida,dano,resist y velocidad destinados para la jugabilidad, es decir,
    son parametros que se utilizan para hacer funcionar de forma correcta el modo de juego.
    Hay varios tipos de enemigos por lo cual no se definen los parametros directamente sino que se invoca una funcion
    en el constructor y esta define los parametros del enemigo dependiendo que tipo es.

    posx,posy y r son parametros para graficar en la escena el enemigo.
    */

    int vida,dano,r=20,type,mapa;
    float posx , posy;
    float velocidad,resist=1;
    float velx,vely,ax,ay,mass=1,radio,angulo; //estas variables no se utilizan.

public:
    enemy();
    enemy(float x,float y,int t);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    void definir_parametros();
    void move_y(int player_y, float dificultad);
    void move_x(int player_x, float dificultad);
    void actualizar_aceleracion(float x, float y, int masa);
    void actualizar_posicion();


    int getVida() const;
    void setVida(int value);
    void setResist(float value);
    int getMapa() const;
    void setMapa(int value);
    float getPosx() const;
    float getPosy() const;
    float getDificultad() const;
    void setDificultad(float value);
    int getDano() const;
};

#endif // ENEMY_H
