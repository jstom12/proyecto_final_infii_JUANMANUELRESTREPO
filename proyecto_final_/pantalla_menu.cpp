#include "pantalla_menu.h"
#include "ui_pantalla_menu.h"

Pantalla_Menu::Pantalla_Menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Pantalla_Menu)
{
    ui->setupUi(this);
    //ui->graphicsView->resize(940,650);
    scene = new QGraphicsScene(0,0,940,640);
    ui->graphicsView->setScene(scene);
    scene->backgroundBrush();
    ui->graphicsView->setBackgroundBrush(QPixmap(":/new/prefix1/resources/aguacate.png"));
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(disparar()));
    //QMessageBox::information(this,tr("BIENVENIDO"),tr("¡recuerda iniciar o crear sesion y elegir un mapa antes de entrar a jugar!"));
    player_1 = new jugador(20,20,15);
    scene->addItem(player_1);
}

Pantalla_Menu::~Pantalla_Menu()
{
    delete ui;
}

void Pantalla_Menu::keyPressEvent(QKeyEvent *evento)
{
    if(evento->key()==Qt::Key_D)
    {
        player_1->move_right();
        player_1->setDir(4);

    }
    if(evento->key()==Qt::Key_A)
    {
        player_1->move_left();
        player_1->setDir(3);

    }
    if(evento->key()==Qt::Key_S)
    {
        player_1->move_down();
        player_1->setDir(2);

    }
    if(evento->key()==Qt::Key_W)
    {
        player_1->move_up();
        player_1->setDir(1);

    }
    if(evento->key()==Qt::Key_R)
    {
        disparar(player_1->getDir());
        //timer->start(30);
    }

}
void Pantalla_Menu::disparar(int posicion)
{
    if(posicion==1)
    {
        disparo = new bala(player_1->getPosx(),player_1->getPosy(),5);
        disparo->up();
        scene->addItem(disparo);
        /*balas_up.push_back(new bala(player_1->getPosx(),player_1->getPosy(),5));
        scene->addItem(balas_up.back());
        for(QList<bala*>::iterator it=balas_up.begin();it!=balas_up.end();it++)
        {
            (*it)->up();
        }*/
    }
    if(posicion==2)
    {
        disparo = new bala(player_1->getPosx(),player_1->getPosy(),5);
        disparo->down();
        scene->addItem(disparo);
    }
    if(posicion==3)
    {
        disparo = new bala(player_1->getPosx(),player_1->getPosy(),5);
        disparo->left();
        scene->addItem(disparo);
    }
    if(posicion==4)
    {
        disparo = new bala(player_1->getPosx(),player_1->getPosy(),5);
        disparo->right();
        scene->addItem(disparo);
    }

}
