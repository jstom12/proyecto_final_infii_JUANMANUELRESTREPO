#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->graphicsView->resize(800,300);
    scene = new QGraphicsScene(0,0,790,690);
    ui->graphicsView->setScene(scene);
    scene->backgroundBrush();
    ui->graphicsView->setBackgroundBrush(QPixmap(":/new/prefix1/resources/aguacate.png"));
    //timer = new QTimer();
    //connect(timer,SIGNAL(timeout()),this,SLOT(disparar()));
    QMessageBox::information(this,tr("BIENVENIDO"),tr("¡recuerda iniciar o crear sesion y elegir un mapa antes de entrar a jugar!"));

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


void MainWindow::on_verificar_inicio_clicked()
{
    QString texto_verificar = ui->texto_inicio->text();
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

void MainWindow::on_crear_usuario_clicked()
{
    QString texto_verificar = ui->texto_crear->text();
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
                  QMessageBox::information(this,tr("ERROR"),tr("Este jugador ya esta registrado"));
                  archivo.close();
                  return;
              }
           }
    }
    archivo.close();
    QFile archivo_2("datos.txt");
    if (archivo_2.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream in(&archivo_2);
        in << texto_verificar << ";" << endl;
        QMessageBox::information(this,tr("!!!!!"),tr("¡Te has registrado con exito!"));
        archivo_2.close();
        return;
    }
}

void MainWindow::on_opcion_1_clicked()
{
    /*
    Paredes.
    */
    scene->clear();
    pared_do = new pared(0,-680,780,20);
    pared_der = new pared(-780,0,20,700);
    pared_up = new pared(0,0,780,20);
    pared_izq = new pared(0,0,20,680);
    scene->addItem(pared_up);
    scene->addItem(pared_der);
    scene->addItem(pared_izq);
    scene->addItem(pared_do);

    /*
    Suelo.
    */
    suelo_1 = new suelo(-20,-20,250,650,2);
    suelo_2 = new suelo(-270,-20,250,150,3);
    suelo_3 = new suelo(-520,-20,230,650,2);
    suelo_4 = new suelo(-270,-400,250,250,3);
    suelo_5 = new suelo(-270,-170,250,250,1);
    scene->addItem(suelo_1);
    scene->addItem(suelo_2);
    scene->addItem(suelo_3);
    scene->addItem(suelo_4);
    scene->addItem(suelo_5);

}

void MainWindow::on_opcion_2_clicked()
{
    scene->clear();
    pared_do = new pared(0,-680,780,20);
    pared_der = new pared(-780,0,20,700);
    pared_up = new pared(0,0,780,20);
    pared_izq = new pared(0,0,20,680);
    scene->addItem(pared_up);
    scene->addItem(pared_der);
    scene->addItem(pared_izq);
    scene->addItem(pared_do);
}

void MainWindow::on_opcion_3_clicked()
{
    scene->clear();
    pared_do = new pared(0,-670,780,20);
    pared_der = new pared(-770,0,20,700);
    pared_up = new pared(0,0,780,20);
    pared_izq = new pared(0,0,20,680);
    scene->addItem(pared_up);
    scene->addItem(pared_der);
    scene->addItem(pared_izq);
    scene->addItem(pared_do);
}

void MainWindow::on_iniciar_game_clicked()
{
    player_1 = new jugador(0,0,20);
    scene->addItem(player_1);
}
