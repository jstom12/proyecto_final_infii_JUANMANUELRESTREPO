#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsItem>
#include <QPainter>

class enemy: public QGraphicsItem
{
    int vida,dano,r=20,type,mapa;
    float posx , posy;
    float velocidad,resist=1;

public:
    enemy();
    enemy(float x,float y,int t);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    void definir_parametros();
    void move_y(int player_y);
    void move_x(int player_x);


    int getVida() const;
    void setVida(int value);
    void setResist(float value);
    int getMapa() const;
    void setMapa(int value);
    float getPosx() const;
    float getPosy() const;
};

#endif // ENEMY_H
