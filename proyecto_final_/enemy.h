#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsItem>
#include <QPainter>
#include <math.h>

class enemy: public QGraphicsItem
{
    int vida,dano,r=20,type,mapa;
    float posx , posy;
    float velocidad,resist=1;
    float velx,vely,ax,ay,mass=1,radio,angulo;

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
};

#endif // ENEMY_H
