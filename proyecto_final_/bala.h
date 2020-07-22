#ifndef BALA_H
#define BALA_H
#include <QPainter>
#include <QGraphicsItem>

class bala : public QGraphicsItem
{
    float posx,posy,r;
    double vel=5;
    int damage=20;

public:
    bala();
    bala(float x, float y, float r_);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    void setPosx(int value);
    void setPosy(int value);
    void right();
    void left();
    void up();
    void down();

    int getDamage() const;
    void setDamage(int value);
};

#endif // BALA_H
