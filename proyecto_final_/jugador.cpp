#include "jugador.h"

int jugador::getPosx() const
{
    return posx;
}

int jugador::getPosy() const
{
    return posy;
}

int jugador::getDir() const
{
    return dir;
}

void jugador::setDir(int value)
{
    dir = value;
}

void jugador::setR(int value)
{
    r = value;
}

int jugador::getVida() const
{
    return vida;
}

void jugador::setVida(int value)
{
    vida = value;
}

void jugador::setResis(float value)
{
    resis = value;
}

int jugador::getMapa() const
{
    return mapa;
}

void jugador::setMapa(int value)
{
    mapa = value;
}

float jugador::getResis() const
{
    return resis;
}

int jugador::getRonda() const
{
    return ronda;
}

void jugador::setRonda(int value)
{
    ronda = value;
}

float jugador::getR() const
{
    return r;
}

void jugador::setAux(bool value)
{
    aux = value;
}

void jugador::setVel(float value)
{
    vel = value;
}

void jugador::setAngulo(float value)
{
    angulo = value;
}

int jugador::getColor() const
{
    return color;
}

void jugador::setColor(int value)
{
    color = value;
}

jugador::jugador()
{
    
}

jugador::jugador(float x,float y,float r_,int ronda_,int color_)
{
    posx = x;
    posy = y;
    r = r_;
    ronda = ronda_;
    color = color_;
    setPos(posx,posy);
}

QRectF jugador::boundingRect() const
{
    return QRectF(-r,-r,2*r,2*r);
}

void jugador::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
    painter->drawEllipse(boundingRect());

}

void jugador::move_right()
{
    if(posx<760)
    {
        posx+= (10-resis);
        setPos(posx,posy);
    }
}

void jugador::move_left()
{
    if(posx>40)
    {
        posx-= (10-resis);
        setPos(posx,posy);
    }
}

void jugador::move_up()
{
    if(posy>40)
    {
        posy-=(10-resis);
        setPos(posx,posy);
    }
}

void jugador::move_down()
{
    if(posy<660)
    {
        posy+= (10-resis);
        setPos(posx,posy);
    }

}

void jugador::actualizar_velocidad()
{
    vx=vel*cos(angulo);
    vy=vel*sin(angulo)-g*delta;
    vel=sqrt(vy*vy+vx*vx);
    angulo=atan2(vy,vx);


}

void jugador::actualizar_tamano(int valor)
{
    if(valor==4)
    {
        posx+=vx*delta;
    }
    if(valor==3)
    {
        posx-=vx*delta;
    }
    if(valor==2)
    {
        posy+=vx*delta;
    }
    if(valor==1)
    {
        posy-=vx*delta;
    }
    if(aux==true)
    {
        r = r+3;
        if(r>=73)
        {
            aux=false;
        }
    }
    if(aux==false)
    {
        r = r-3;
    }
    setPos(posx,posy);

}
