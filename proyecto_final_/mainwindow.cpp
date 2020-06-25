#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0,0,480,480);
    ui->graphicsView->setScene(scene);
    scene->backgroundBrush();
    scene_2 = new QGraphicsScene(0,0,280,100);
    ui->graphicsView->setScene(scene_2);
    scene->backgroundBrush();

    player_1 = new jugador(20,20,15);
    scene->addItem(player_1);


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
        disparar(4);

    }
    if(evento->key()==Qt::Key_A)
    {
        player_1->move_left();
        disparar(3);

    }
    if(evento->key()==Qt::Key_S)
    {
        player_1->move_down();
        disparar(2);

    }
    if(evento->key()==Qt::Key_W)
    {
        player_1->move_up();
        disparar(1);

    }
}

void MainWindow::disparar(int posicion)
{
    if(posicion==1)
    {
        disparo = new bala(player_1->getPosx(),player_1->getPosy(),5);
        disparo->up();
        scene->addItem(disparo);
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

void MainWindow::on_pushButton_clicked()
{

}
