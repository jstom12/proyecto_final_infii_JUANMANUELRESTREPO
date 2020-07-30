#include "enemy.h"

int enemy::getVida() const
{
    return vida;
}

void enemy::setVida(int value)
{
    vida = value;
}

void enemy::setResist(float value)
{
    resist = value;
}

int enemy::getMapa() const
{
    return mapa;
}

void enemy::setMapa(int value)
{
    mapa = value;
}

float enemy::getPosx() const
{
    return posx;
}

float enemy::getPosy() const
{
    return posy;
}

int enemy::getDano() const
{
    return dano;
}

enemy::enemy()
{
    
}

enemy::enemy(float x, float y, int t)
{
    posx = x;
    posy = y;
    type = t;
    definir_parametros();
    setPos(posx,posy);
}

QRectF enemy::boundingRect() const
{
    return QRectF(-r,-r,2*r,2*r);
}

void enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::darkRed);
    painter->drawRect(boundingRect());
}

void enemy::definir_parametros()
{
    /*
    En esta funcion se definen los parametros del enemigo dependiendo el tipo que es, cada una
    tiene caracteristicas propias con la intencion de darle variedad al juego.
    */
    if(type==1)
    {
        velocidad=6;
        vida=50;
        dano=20;
    }
    if(type==2)
    {
        velocidad=5;
        vida=60;
        dano=30;
    }
    if(type==3)
    {
        velocidad=4;
        vida=100;
        dano=50;
    }
    if(type==4)
    {
        velocidad=8;
        vida=50;
        dano=15;
    }
}

void enemy::move_y(int player_y , float dificultad)
{
    /*
    Realizar los movimientos del enemigo es sencillo, lo unico que se debe hacer es encontrar la diferencia
    entre la posicion del enemigo y el jugador y sumarle la velocidad en la que se mueve el enemigo; esta
    velocidad se multiplica por la variable dificultad que corresponde a la inercia del cuerpo con el suelo
    en el que se encuentra el enemigo.
    */
    if(player_y>posy)
    {
        posy = posy+(velocidad-(resist*dificultad));
        setPos(posx,posy);
    }
    if(player_y<posy)
    {
        posy= posy-(velocidad-(resist*dificultad));
        setPos(posx,posy);
    }
}

void enemy::move_x(int player_x , float dificultad)
{
    if(player_x>posx)
    {
        posx +=(velocidad-(resist*dificultad));
        setPos(posx,posy);
    }
    if(player_x<posx)
    {
        posx = posx-(velocidad-(resist*dificultad));
        setPos(posx,posy);
    }
}

void enemy::actualizar_aceleracion(float x, float y, int masa)
{
    angulo = atan2((y-posy),(x-posx));
    //radio = pow((x-posx),2)+pow((y-posy),2);
    ax = ax + (masa*cos(angulo));//radio;
    ay = ay + (masa*sin(angulo));//radio;

}

void enemy::actualizar_posicion()
{
    velx = velx + ax;
    vely = vely + ay;
    posx = posx + velx;
    posy = posy + vely;
    //velx=0;
    //vely=0;
    setPos((posx),(posy));
}
