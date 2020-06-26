#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->resize(256,256);
    scene = new QGraphicsScene(0,0,256,256);
    ui->graphicsView->setScene(scene);
    scene->backgroundBrush();
    ui->graphicsView->setBackgroundBrush(QPixmap(":/new/prefix1/resources/aguacate.png"));

    //player_1 = new jugador(20,20,15);
    //scene->addItem(player_1);



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
    QString texto_verificar = ui->inicio_texto->text();
    QFile archivo("datos.txt");
    QStringList texto_separado;
    if (archivo.open(QIODevice::ReadOnly))
    {
        QTextStream in(&archivo);
           while (!in.atEnd())
           {
              QString line = in.readLine();
              texto_separado = line.split(';');
              if(texto_separado[0]==texto_verificar)
              {
                  archivo.close();
                  this->close();
                  return;
              }

           }
           archivo.close();
    }

}

void MainWindow::on_pushButton_2_clicked()
{

}