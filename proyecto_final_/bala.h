#ifndef BALA_H
#define BALA_H
#include <QPainter>
#include <QGraphicsItem>

class bala : public QGraphicsItem
{
    int posx,posy,r;
    double vel=5;

public:
    bala();
    bala(int x, int y, int r_);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    void setPosx(int value);
    void setPosy(int value);
    void right();
    void left();
    void up();
    void down();

};

#endif // BALA_H
