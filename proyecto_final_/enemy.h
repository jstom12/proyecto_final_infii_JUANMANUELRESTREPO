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
    void move_y(int player_y);
    void move_x(int player_x);


};

#endif // ENEMY_H
