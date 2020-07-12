#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsItem>
#include <QPainter>

class enemy: public QGraphicsItem
{
    int vida,dano,r=20,type;
    int posx , posy;
    float velocidad;

public:
    enemy();
    enemy(int x,int y,int t);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    void definir_parametros();
    void up();
    void down();
    void left();
    void right();

};

#endif // ENEMY_H
