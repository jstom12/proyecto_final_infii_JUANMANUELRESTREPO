#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->graphicsView->resize(800,300);
    scene = new QGraphicsScene(0,0,980,680);
    ui->graphicsView->setScene(scene);
    scene->backgroundBrush();
    ui->graphicsView->setBackgroundBrush(QPixmap(":/new/prefix1/resources/aguacate.png"));
    //timer = new QTimer();
    //connect(timer,SIGNAL(timeout()),this,SLOT(disparar()));
    QMessageBox::information(this,tr("BIENVENIDO"),tr("¡recuerda iniciar o crear sesion y elegir un mapa antes de entrar a jugar!"));
    player_1 = new jugador(20,20,15);
    scene->addItem(player_1);
    this->hide();
    second_pantalla = new Pantalla_Menu(this);
    second_pantalla->show();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *evento)
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
    if(evento->key()==Qt::Key_Escape)
    {
        Pantalla_Menu *pantalla_menu = new Pantalla_Menu;
        this->hide();
        pantalla_menu->show();
    }
}

void MainWindow::disparar(int posicion)
{
    if(posicion==1)
    {
        balas_up.push_back(new bala(player_1->getPosx(),player_1->getPosy(),5));
        scene->addItem(balas_up.back());
        for(QList<bala*>::iterator it=balas_up.begin();it!=balas_up.end();it++)
        {
            (*it)->up();
        }


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

