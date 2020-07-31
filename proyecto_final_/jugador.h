#ifndef JUGADOR_H
#define JUGADOR_H
#include <QGraphicsItem>
#include <QPainter>
#include <math.h>
#include <QDebug>


class jugador : public QGraphicsItem
{
    /*
    Los parametros dir,vida,mapa,ronda,resis,color son los necesarios para la correcta jugabilidad del jugador;
    Los parametros posx,posy y r son los necesarios para mostrar el jugador en la escena.
    */
    float posx,posy; //posicion en la escena.
    int r; //tamano del jugador.
    int dir=4,vida=100, mapa=1, ronda=2; // datos necesarios para la jugabilidad.
    float resis=0; // inercia.
    float masa__=1;
    float vel=50,vx,vy,angulo=50,g=9.8,delta=0.1; //variables necesarias para movimiento parabolico.
    bool aux=true; // variable auxiliar que permite saber cuando el objeto debe decrecer al momento de saltar.
    int color;

public:
    jugador();
    jugador(float x,float y,float r_,int ronda_,int color_);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    void move_right();
    void move_left();
    void move_up();
    void move_down();
    void actualizar_velocidad();
    void actualizar_tamano(int valor);



    int getPosx() const;
    int getPosy() const;
    int getDir() const;
    void setDir(int value);
    void setR(int value);
    int getVida() const;
    void setVida(int value);
    void setResis(float value);
    int getMapa() const;
    void setMapa(int value);
    float getResis() const;
    int getRonda() const;
    void setRonda(int value);
    float getR() const;
    void setAux(bool value);
    void setVel(float value);
    void setAngulo(float value);
    int getColor() const;
    void setColor(int value);
};

#endif // JUGADOR_H
