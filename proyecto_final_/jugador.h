#ifndef JUGADOR_H
#define JUGADOR_H
#include <QGraphicsItem>
#include <QPainter>


class jugador : public QGraphicsItem
{
    float posx,posy,r;
    int dir,vida=10;
    float resis=1;

public:
    jugador();
    jugador(float x,float y,float r_);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    void move_right();
    void move_left();
    void move_up();
    void move_down();

    int getPosx() const;
    int getPosy() const;
    int getDir() const;
    void setDir(int value);
    void setR(int value);
    int getVida() const;
    void setVida(int value);
    void setResis(float value);
};

#endif // JUGADOR_H
