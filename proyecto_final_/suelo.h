#ifndef SUELO_H
#define SUELO_H
#include <QGraphicsItem>
#include <QPainter>


class suelo: public QGraphicsItem
{
    int type,posx,posy,w,h;
    float resistencia;

public:
    suelo();
    suelo(int x,int y,int anc,int large,int ty);


    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    void definir_resistencia();
};

#endif // SUELO_H
