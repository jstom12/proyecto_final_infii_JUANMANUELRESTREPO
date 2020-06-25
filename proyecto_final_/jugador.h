#ifndef JUGADOR_H
#define JUGADOR_H
#include <QGraphicsItem>
#include <QPainter>


class jugador : public QGraphicsItem
{
    int posx,posy,r;
    int dir;

public:
    jugador();
    jugador(int x,int y, int r_);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    void move_right();
    void move_left();
    void move_up();
    void move_down();

    int getPosx() const;
    int getPosy() const;
};

#endif // JUGADOR_H
