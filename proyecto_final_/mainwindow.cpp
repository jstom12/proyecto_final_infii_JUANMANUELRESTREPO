#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->graphicsView->resize(800,300);
    new_pantalla = new pantalla_menu();
    scene = new QGraphicsScene(0,0,790,690);
    ui->graphicsView->setScene(scene);
    scene->backgroundBrush();
    ui->graphicsView->setBackgroundBrush(QPixmap(":/new/prefix1/resources/aguacate.png"));
    timer = new QTimer();
    timer_enemigos= new QTimer();
    timer_movimientos = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(procesos()));
    connect(timer_enemigos,SIGNAL(timeout()),this,SLOT(generacion_enemigos()));
    connect(timer_movimientos,SIGNAL(timeout()),this,SLOT(movimientos_enemigos()));
    QMessageBox::information(this,tr("BIENVENIDO"),tr("Recuerda presionar ESC para entrar al menu al cerrar esta pestaña"));




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *evento)
{
    if(evento->key()==Qt::Key_Escape)
    {
        new_pantalla->show();
    }
    //inercia_(player_1->getMapa());
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
        disparar(player_1->getPosx(),player_1->getPosy(),player_1->getDir());
    }
    if(evento->key()==Qt::Key_L)
    {
        player_2->move_right();
        player_2->setDir(4);
    }
    if(evento->key()==Qt::Key_J)
    {
        player_2->move_left();
        player_2->setDir(3);
    }
    if(evento->key()==Qt::Key_I)
    {
        player_2->move_up();
        player_2->setDir(1);
    }
    if(evento->key()==Qt::Key_K)
    {
        player_2->move_down();
        player_2->setDir(2);
    }
    if(evento->key()==Qt::Key_P)
    {
        disparar(player_2->getPosx(),player_2->getPosy(),player_2->getDir());
    }

}

void MainWindow::disparar(float posx ,float posy , int posicion)
{
    if(posicion==1)
    {
        balas_up.push_back(new bala(posx,posy,5));
        scene->addItem(balas_up.back());
        for(QList<bala*>::iterator it=balas_up.begin();it!=balas_up.end();it++)
        {
            (*it)->up();
        }
    }
    if(posicion==2)
    {
        balas_down.push_back(new bala(posx,posy,5));
        scene->addItem(balas_down.back());
        for(QList<bala*>::iterator it=balas_down.begin();it!=balas_down.end();it++)
        {
            (*it)->down();
        }
    }
    if(posicion==3)
    {
        balas_left.push_back(new bala(posx,posy,5));
        scene->addItem(balas_left.back());
        for(QList<bala*>::iterator it=balas_left.begin();it!=balas_left.end();it++)
        {
            (*it)->left();
        }
    }
    if(posicion==4)
    {
        balas_righ.push_back(new bala(posx,posy,5));
        scene->addItem(balas_righ.back());
        for(QList<bala*>::iterator it=balas_righ.begin();it!=balas_righ.end();it++)
        {
            (*it)->right();
        }
    }

}

void MainWindow::procesos()
{


    animacion_balas(balas_up,1);
    animacion_balas(balas_down,2);
    animacion_balas(balas_left,3);
    animacion_balas(balas_righ,4);

    int aux;
    aux = dano_enemigos(balas_up);
    if(aux>0)
    {
        scene->removeItem(balas_up.at(aux));
        balas_up.removeAt(aux);
    }

    aux = dano_enemigos(balas_down);
    if(aux>0)
    {
        scene->removeItem(balas_down.at(aux));
        balas_down.removeAt(aux);
    }

    aux = dano_enemigos(balas_left);
    if(aux>0)
    {
        scene->removeItem(balas_left.at(aux));
        balas_left.removeAt(aux);
    }

    aux = dano_enemigos(balas_righ);
    if(aux>0)
    {
        scene->removeItem(balas_righ.at(aux));
        balas_righ.removeAt(aux);
    }

    eliminar_enemigos();
    dano_jugador();

    ui->label_4->setText(QVariant(ronda_aux).toString());
    eliminacion_jugador();


}

void MainWindow::animacion_balas(QList<bala *> lista , int pos)
{
    for(QList<bala*>::iterator it=lista.begin();it!=lista.end();it++)
    {
        if(pos==1)
        {
            (*it)->up();
        }
        if(pos==2)
        {
            (*it)->down();
        }
        if(pos==3)
        {
            (*it)->left();
        }
        if(pos==4)
        {
            (*it)->right();
        }
    }
}

void MainWindow::generacion_enemigos()
{
    if(ronda_aux!=0)
    {
        enemigos.push_back(new enemy(90,620,1));
        scene->addItem(enemigos.back());
        enemigos.push_back(new enemy(720,620,1));
        scene->addItem(enemigos.back());
        enemigos.push_back(new enemy(720,60,1));
        scene->addItem(enemigos.back());
        enemigos.push_back(new enemy(90,60,1));
        scene->addItem(enemigos.back());
        ronda_aux = ronda_aux-1;
    }
    if(ronda_aux==0 && enemigos.isEmpty())
    {
        player_1->setRonda(player_1->getRonda()+1);
        ronda_aux = player_1->getRonda();
    }

}

void MainWindow::movimientos_enemigos()
{
    inercia_enemigos(player_1->getMapa());
    QVector<jugador*>::iterator it=jugadores.begin();
    for(QList<enemy*>::iterator itm=enemigos.begin();itm!=enemigos.end();itm++)
    {
        (*itm)->move_x((*it)->getPosx());
        (*itm)->move_y((*it)->getPosy());
        if(it==jugadores.begin())
        {
            it=jugadores.end();
        }
        if(it==jugadores.end())
        {
            it=jugadores.begin();
        }
    }
}

int MainWindow::dano_enemigos(QList<bala *> balas)
{
    QList<enemy*>::iterator itm;
    QList<bala*>::iterator it;
    for(itm=enemigos.begin();itm!=enemigos.end();itm++)
    {
        for(it=balas.begin();it!=balas.end();it++)
        {
            if((*it)->collidesWithItem((*itm)))
            {
                int nueva_vida=(*itm)->getVida()-(*it)->getDamage();
                (*itm)->setVida(nueva_vida);

                return balas.indexOf((*it));
            }
        }
    }
    return -1;
}

void MainWindow::eliminar_enemigos()
{
    QList<enemy*>::iterator it;
    int posicion_aux;
    for(it=enemigos.begin();it!=enemigos.end();it++)
    {
        if((*it)->getVida()<0)
        {
            posicion_aux = enemigos.indexOf((*it));
            scene->removeItem(enemigos.at(posicion_aux));
            enemigos.removeAt(posicion_aux);
            return;
        }
    }
}

void MainWindow::dano_jugador()
{
    QVector<jugador*>::iterator it;
    QList<enemy*>::iterator itm;
    for(it=jugadores.begin();it!=jugadores.end();it++)
    {
        for(itm=enemigos.begin();itm!=enemigos.end();itm++)
        {
            if((*it)->collidesWithItem((*itm)))
            {
                int nueva_vida= (*it)->getVida()-(*itm)->getVida();
                (*it)->setVida(nueva_vida);
                int posicion_aux_dano = enemigos.indexOf((*itm));
                scene->removeItem(enemigos.at(posicion_aux_dano));
                enemigos.removeAt(posicion_aux_dano);
                return;
            }
        }
    }
}

void MainWindow::eliminacion_jugador()
{
    QVector<jugador*>::iterator it;
    for(it=jugadores.begin();it!=jugadores.end();it++)
    {
        if((*it)->getVida()<0)
        {
            int posicion_aux=jugadores.indexOf((*it));
            scene->removeItem(jugadores.at(posicion_aux));
            jugadores.removeAt(posicion_aux);
            timer->stop();
            timer_movimientos->stop();
            return;
        }
    }

}

void MainWindow::inercia_(int map)
{
    QVector<jugador*>::iterator it;
    for(it=jugadores.begin();it!=jugadores.end();it++)
    {
        map = (*it)->getMapa();
        if(map==1)
        {
             if(((*it)->getPosx()>=290 && (*it)->getPosy()>=190) && ((*it)->getPosx()<=500 && (*it)->getPosy()<=400))//centro
             {
                 (*it)->setResis(1);
             }
             if(((*it)->getPosx()>=40 && (*it)->getPosy()>=40) && ((*it)->getPosx()<=250 && (*it)->getPosy()<=660))//derecha
             {
                 (*it)->setResis(5);
             }
             if(((*it)->getPosx()>=290 && (*it)->getPosy()>=440) && ((*it)->getPosx()<=500 && (*it)->getPosy()<=660))//centroinf
             {
                 (*it)->setResis(5);
             }
             if(((*it)->getPosx()>=290 && (*it)->getPosy()>=40) && ((*it)->getPosx()<=500 && (*it)->getPosy()<=150))//centrosup
             {
                 (*it)->setResis(3);
             }
             if(((*it)->getPosx()>=540 && (*it)->getPosy()>=40) && ((*it)->getPosx()<=760 && (*it)->getPosy()<=660))//izquierda
             {
                 (*it)->setResis(3);
             }

        }
        if(map==2)
        {
            if(((*it)->getPosx()>=290 && (*it)->getPosy()>=190) && ((*it)->getPosx()<=500 && (*it)->getPosy()<=400))//centro
            {

            }
            if(((*it)->getPosx()>=40 && (*it)->getPosy()>=40) && ((*it)->getPosx()<=250 && (*it)->getPosy()<=660))//derecha
            {

            }
            if(((*it)->getPosx()>=290 && (*it)->getPosy()>=440) && ((*it)->getPosx()<=500 && (*it)->getPosy()<=660))//centroinf
            {

            }
            if(((*it)->getPosx()>=290 && (*it)->getPosy()>=40) && ((*it)->getPosx()<=500 && (*it)->getPosy()<=150))//centrosup
            {

            }
            if(((*it)->getPosx()>=540 && (*it)->getPosy()>=40) && ((*it)->getPosx()<=760 && (*it)->getPosy()<=660))//izquierda
            {

            }

        }
        if(map==3)
        {
            if(((*it)->getPosx()>=290 && (*it)->getPosy()>=190) && ((*it)->getPosx()<=500 && (*it)->getPosy()<=400))//centro
            {

            }
            if(((*it)->getPosx()>=40 && (*it)->getPosy()>=40) && ((*it)->getPosx()<=250 && (*it)->getPosy()<=660))//derecha
            {

            }
            if(((*it)->getPosx()>=290 && (*it)->getPosy()>=440) && ((*it)->getPosx()<=500 && (*it)->getPosy()<=660))//centroinf
            {

            }
            if(((*it)->getPosx()>=290 && (*it)->getPosy()>=40) && ((*it)->getPosx()<=500 && (*it)->getPosy()<=150))//centrosup
            {

            }
            if(((*it)->getPosx()>=540 && (*it)->getPosy()>=40) && ((*it)->getPosx()<=760 && (*it)->getPosy()<=660))//izquierda
            {

            }

        }

    }
}

void MainWindow::inercia_enemigos(int map)
{
    QList<enemy*>::iterator it;
    for(it=enemigos.begin();it!=enemigos.end();it++)
    {
        map = (*it)->getMapa();
        if(map==1)
        {
             if(((*it)->getPosx()>=290 && (*it)->getPosy()>=190) && ((*it)->getPosx()<=500 && (*it)->getPosy()<=400))//centro
             {
                 (*it)->setResist(0.5);
             }
             if(((*it)->getPosx()>=40 && (*it)->getPosy()>=40) && ((*it)->getPosx()<=250 && (*it)->getPosy()<=660))//derecha
             {
                 (*it)->setResist(1);
             }
             if(((*it)->getPosx()>=290 && (*it)->getPosy()>=440) && ((*it)->getPosx()<=500 && (*it)->getPosy()<=660))//centroinf
             {
                 (*it)->setResist(1);
             }
             if(((*it)->getPosx()>=290 && (*it)->getPosy()>=40) && ((*it)->getPosx()<=500 && (*it)->getPosy()<=150))//centrosup
             {
                 (*it)->setResist(0.8);
             }
             if(((*it)->getPosx()>=540 && (*it)->getPosy()>=40) && ((*it)->getPosx()<=760 && (*it)->getPosy()<=660))//izquierda
             {
                 (*it)->setResist(0.8);
             }

        }
        if(map==2)
        {
            if(((*it)->getPosx()>=290 && (*it)->getPosy()>=190) && ((*it)->getPosx()<=500 && (*it)->getPosy()<=400))//centro
            {

            }
            if(((*it)->getPosx()>=40 && (*it)->getPosy()>=40) && ((*it)->getPosx()<=250 && (*it)->getPosy()<=660))//derecha
            {

            }
            if(((*it)->getPosx()>=290 && (*it)->getPosy()>=440) && ((*it)->getPosx()<=500 && (*it)->getPosy()<=660))//centroinf
            {

            }
            if(((*it)->getPosx()>=290 && (*it)->getPosy()>=40) && ((*it)->getPosx()<=500 && (*it)->getPosy()<=150))//centrosup
            {

            }
            if(((*it)->getPosx()>=540 && (*it)->getPosy()>=40) && ((*it)->getPosx()<=760 && (*it)->getPosy()<=660))//izquierda
            {

            }

        }
        if(map==3)
        {
            if(((*it)->getPosx()>=290 && (*it)->getPosy()>=190) && ((*it)->getPosx()<=500 && (*it)->getPosy()<=400))//centro
            {

            }
            if(((*it)->getPosx()>=40 && (*it)->getPosy()>=40) && ((*it)->getPosx()<=250 && (*it)->getPosy()<=660))//derecha
            {

            }
            if(((*it)->getPosx()>=290 && (*it)->getPosy()>=440) && ((*it)->getPosx()<=500 && (*it)->getPosy()<=660))//centroinf
            {

            }
            if(((*it)->getPosx()>=290 && (*it)->getPosy()>=40) && ((*it)->getPosx()<=500 && (*it)->getPosy()<=150))//centrosup
            {

            }
            if(((*it)->getPosx()>=540 && (*it)->getPosy()>=40) && ((*it)->getPosx()<=760 && (*it)->getPosy()<=660))//izquierda
            {

            }

        }

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
    //player_1->setMapa(1);
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
    suelos.push_back(new suelo(-20,-20,250,660,3));
    scene->addItem(suelos.back());
    suelos.push_back(new suelo(-270,-20,250,150,2));
    scene->addItem(suelos.back());
    suelos.push_back(new suelo(-520,-20,260,660,2));
    scene->addItem(suelos.back());
    suelos.push_back(new suelo(-270,-400,250,280,3));
    scene->addItem(suelos.back());
    suelos.push_back(new suelo(-270,-170,250,250,1));
    scene->addItem(suelos.back());


}

void MainWindow::on_opcion_2_clicked()
{
    //player_1->setMapa(2);
    scene->clear();
    pared_do = new pared(0,-680,780,20);
    pared_der = new pared(-780,0,20,700);
    pared_up = new pared(0,0,780,20);
    pared_izq = new pared(0,0,20,680);
    scene->addItem(pared_up);
    scene->addItem(pared_der);
    scene->addItem(pared_izq);
    scene->addItem(pared_do);

    suelos.push_back(new suelo(-20,-20,250,660,2));
    scene->addItem(suelos.back());
    suelos.push_back(new suelo(-270,-20,250,150,2));
    scene->addItem(suelos.back());
    suelos.push_back(new suelo(-520,-20,260,660,2));
    scene->addItem(suelos.back());
    suelos.push_back(new suelo(-270,-400,250,280,2));
    scene->addItem(suelos.back());
    suelos.push_back(new suelo(-270,-170,250,250,1));
    scene->addItem(suelos.back());
}

void MainWindow::on_opcion_3_clicked()
{
    //player_1->setMapa(3);
    scene->clear();
    pared_do = new pared(0,-670,780,20);
    pared_der = new pared(-780,0,20,700);
    pared_up = new pared(0,0,780,20);
    pared_izq = new pared(0,0,20,680);
    scene->addItem(pared_up);
    scene->addItem(pared_der);
    scene->addItem(pared_izq);
    scene->addItem(pared_do);


    suelos.push_back(new suelo(-20,-20,250,660,3));
    scene->addItem(suelos.back());
    suelos.push_back(new suelo(-270,-20,250,150,3));
    scene->addItem(suelos.back());
    suelos.push_back(new suelo(-520,-20,260,660,3));
    scene->addItem(suelos.back());
    suelos.push_back(new suelo(-270,-400,250,280,3));
    scene->addItem(suelos.back());
    suelos.push_back(new suelo(-270,-170,250,250,1));
    scene->addItem(suelos.back());
}

void MainWindow::iniciar_juego()
{
    if(multiplayer==true)
    {
        player_2 = new jugador(350,250,20,1);
        jugadores.push_back(player_2);
        scene->addItem(player_2);
        player_1 = new jugador(390,290,20,1);
        jugadores.push_back(player_1);
        scene->addItem(player_1);
        timer->start(10);
        timer_movimientos->start(100);

    }
    if(multiplayer==false)
    {
        player_1 = new jugador(390,290,20,1);
        jugadores.push_back(player_1);
        scene->addItem(player_1);
        timer->start(10);
        timer_movimientos->start(100);
        timer_enemigos->start(5000);
    }
}

void MainWindow::on_iniciar_game_clicked()
{
    multiplayer=false;
    iniciar_juego();
    ronda_aux = player_1->getRonda();
    generacion_enemigos();

}

void MainWindow::on_pushButton_clicked()
{   
    multiplayer = true;
    iniciar_juego();
    generacion_enemigos();
}
