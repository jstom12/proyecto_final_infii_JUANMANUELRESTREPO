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
    /*
    Para elegir de que color se pinta el objeto, se recibe un entero que corresponde a un color sacado
    de la ruleta de colores que tiene incorporado el juego y este esta guardado en los datos del jugador
    y tambien puede ser extraido al momento de iniciar sesion.
    */
    if(color==1)
    {
        painter->setBrush(QPixmap(":/new/prefix1/resources/azul_claro.png"));
        painter->drawEllipse(boundingRect());
    }
    if(color==2)
    {
        painter->setBrush(QPixmap(":/new/prefix1/resources/rosa.png"));
        painter->drawEllipse(boundingRect());
    }
    if(color==3)
    {
        painter->setBrush(QPixmap(":/new/prefix1/resources/cafe.png"));
        painter->drawEllipse(boundingRect());
    }
    if(color==4)
    {
        painter->setBrush(Qt::yellow);
        painter->drawEllipse(boundingRect());
    }
    if(color==5)
    {
        painter->setBrush(QPixmap(":/new/prefix1/resources/verde.png"));
        painter->drawEllipse(boundingRect());
    }
    if(color==6)
    {
        painter->setBrush(QPixmap(":/new/prefix1/resources/azul_escuro.png"));
        painter->drawEllipse(boundingRect());
    }
}

void jugador::move_right()
{
    /*
    Los movimientos del jugador es una simple suma que corresponde a 10 menos la inercia del cuerpo y el suelo.
    */
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
    /*
    Esta funcion es necesaria para realizar el efecto de un movimiento parabolico.
    */
    vx=vel*cos(angulo);
    vy=vel*sin(angulo)-g*delta;
    vel=sqrt(vy*vy+vx*vx);
    angulo=atan2(vy,vx);
}

void jugador::actualizar_tamano(int valor)
{
    /*
    Esta es la funcion que recrea en la escena el movimiento parabolico, recibe un entero que define
    en que direccion va el movimiento. Luego, el radio del jugador crece de 3 en 3 si este es menor a 73
    y decrece de 3 en 3 si es mayor o igual a 73 (esto porque al utilizar la ecuacion, no funcionaba de manera
    correcta pero, en un simulador con estas mismas ecuaciones, encontré que el radio tendía a crecer de 3 en 3
    hasta que alcanzaba el 73 y ahí empezaba a decrecer).
    */
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
