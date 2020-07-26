#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0,0,790,690);
    ui->graphicsView->setScene(scene);
    scene->backgroundBrush();
    ui->graphicsView->setBackgroundBrush(QPixmap(":/new/prefix1/resources/aguacate.png"));
    timer = new QTimer();
    timer_enemigos= new QTimer();
    timer_movimientos = new QTimer();
    jump = new QTimer();
    ruleta = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(procesos()));
    connect(timer_enemigos,SIGNAL(timeout()),this,SLOT(generacion_enemigos()));
    connect(timer_movimientos,SIGNAL(timeout()),this,SLOT(movimientos_enemigos()));
    connect(jump,SIGNAL(timeout()),this,SLOT(salto_jugador()));
    connect(ruleta,SIGNAL(timeout()),this,SLOT(bolita_giro()));
    QMessageBox::information(this,tr("BIENVENIDO"),tr("Recuerda crear tu personaje si es la primera vez que juegas(NOTA: PARA EL MULTIJUGADOR NO NECESITAS INICIAR NI CREAR UN JUGADOR"));



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *evento)
{
    if(evento->key()==Qt::Key_B)
    {
        bolita_ruleta->actualizar_posicion();
        qDebug() << bolita_ruleta->getPosx() << "  " << bolita_ruleta->getPosy() << endl;
    }
    if(in_game==true)
    {
        if(evento->key()==Qt::Key_Escape)
        {
            ui->label->show();
            ui->label_2->show();
            ui->label_3->show();
            ui->opcion_1->show();
            ui->verificar_inicio->show();
            ui->crear_usuario->show();
            ui->texto_inicio->show();
            ui->iniciar_game->show();
            ui->texto_crear->show();
            ui->pushButton->show();
            ui->opcion_2->show();
            ui->opcion_3->show();
            ui->push_menu->show();
            ui->pushButton_2->show();
            timer->stop();
            timer_enemigos->stop();
            timer_movimientos->stop();
            while(!jugadores.isEmpty())
            {
                scene->removeItem(jugadores.back());
                jugadores.pop_back();
            }
            while(!enemigos.isEmpty())
            {
                scene->removeItem(enemigos.back());
                enemigos.pop_back();
            }
            while(!suelos.isEmpty())
            {
                scene->removeItem(suelos.back());
                suelos.pop_back();
            }
            while(!paredes.isEmpty())
            {
                scene->removeItem(paredes.back());
                paredes.pop_back();
            }
            scene->clear();
            balas_up.clear();
            balas_down.clear();
            balas_left.clear();
            balas_righ.clear();
            dificult=1;
            dano_balas=20;
            ronda_aux = player_1->getRonda();
            QMessageBox::information(this,tr("!!!"),tr("ACTUALIZANDO LA DATA..."));

        }
        inercia_(mapa_cho);
        if(multiplayer==1 || multiplayer==2)
        {
            if(evento->key()==Qt::Key_Q)
            {
                choose_salto_jugador=true;
                jump->start(20);
            }
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
        }

        if(multiplayer==1)
        {
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
            if(evento->key()==Qt::Key_U)
            {
                choose_salto_jugador = false;
                jump->start(20);
            }
        }
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

    choques_balas(balas_up);
    choques_balas(balas_down);
    choques_balas(balas_left);
    choques_balas(balas_righ);

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
    if(in_jump==false)
    {
        dano_jugador();
    }


    ui->label_4->setText(QVariant(player_1->getVida()).toString());
    ui->label_5->setText(QVariant(player_1->getRonda()).toString());
    ui->label_6->setText(QVariant(ronda_aux).toString());
    if(multiplayer==1)
    {
        ui->label_7->setText(QVariant(player_2->getVida()).toString());
    }
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

void MainWindow::salto_jugador()
{
    in_jump = true;
    if(choose_salto_jugador==true)
    {
        player_1->actualizar_velocidad();
        player_1->actualizar_tamano(player_1->getDir());
        if(player_1->getR()<=20)
        {
            in_jump = false;
            player_1->setR(20);
            player_1->setAux(true);
            player_1->setVel(50);
            player_1->setAngulo(50);
            jump->stop();
        }
        if(player_1->getPosx()<40 || player_1->getPosx()>760 || player_1->getPosy()<40 || player_1->getPosy()>660)
        {
            player_1->setVida(-10);
        }
    }
    if(choose_salto_jugador==false)
    {
        player_2->actualizar_velocidad();
        player_2->actualizar_tamano(player_2->getDir());
        if(player_2->getR()<=20)
        {
            in_jump = false;
            player_2->setR(20);
            player_2->setAux(true);
            player_2->setVel(50);
            player_2->setAngulo(50);
            jump->stop();
        }
        if(player_2->getPosx()<40 || player_2->getPosx()>760 || player_2->getPosy()<40 || player_2->getPosy()>660)
        {
            player_2->setVida(-10);
        }
    }

}

void MainWindow::choques_balas(QList<bala *> lista)
{
    QList<bala*>::iterator it;
    QVector<pared*>::iterator itm;
    for(it=lista.begin();it!=lista.end();it++)
    {
        for(itm=paredes.begin();itm!=paredes.end();itm++)
        {
            if((*it)->collidesWithItem((*itm)))
            {
                int posicion__=lista.indexOf((*it));
                scene->removeItem(lista.at(posicion__));
                lista.removeAt(posicion__);
                return;
            }
        }
    }
}

void MainWindow::generacion_enemigos()
{
    if(ronda_aux!=0)
    {
        enemigos.push_back(new enemy(90,620,1));
        scene->addItem(enemigos.back());
        enemigos.push_back(new enemy(720,620,4));
        scene->addItem(enemigos.back());
        enemigos.push_back(new enemy(720,60,3));
        scene->addItem(enemigos.back());
        enemigos.push_back(new enemy(90,60,4));
        scene->addItem(enemigos.back());
        ronda_aux = ronda_aux-1;
    }
    if(ronda_aux==0 && enemigos.isEmpty())
    {
        player_1->setRonda(player_1->getRonda()+1);
        ronda_aux = player_1->getRonda();
        if(dificult!=0)
        {
            dificult = dificult - 0.1;
        }
        if(dano_balas>10)
        {
            dano_balas = dano_balas - 1;
        }
        guardado();
    }

}

bool MainWindow::area_jugador(jugador *player)
{
    if(player->getPosx()>40 && player->getPosx()<760)
    {
        return true;
    }
    if(player->getPosy()>40 && player->getPosy()<660)
    {
        return true;
    }
    return false;
}

void MainWindow::movimientos_enemigos()
{
    inercia_enemigos(mapa_cho);
    QVector<jugador*>::iterator it=jugadores.begin();
    for(QList<enemy*>::iterator itm=enemigos.begin();itm!=enemigos.end();itm++)
    {
        //(*itm)->actualizar_aceleracion((*it)->getPosx(),(*it)->getPosy(),1);
        //(*itm)->actualizar_posicion();
        (*itm)->move_x((*it)->getPosx(),dificult);
        (*itm)->move_y((*it)->getPosy(),dificult);
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
                int nueva_vida=(*itm)->getVida()-dano_balas;
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
        if((*it)->getVida()<=0)
        {
            int posicion_aux=jugadores.indexOf((*it));
            scene->removeItem(jugadores.at(posicion_aux));
            jugadores.removeAt(posicion_aux);
            if(jugadores.isEmpty())
            {
                timer->stop();
                timer_movimientos->stop();
                return;
            }
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
                 (*it)->setResis(1);
             }
             if(((*it)->getPosx()>=290 && (*it)->getPosy()>=40) && ((*it)->getPosx()<=500 && (*it)->getPosy()<=150))//centrosup
             {
                 (*it)->setResis(1);
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
                (*it)->setResis(1);
            }
            if(((*it)->getPosx()>=40 && (*it)->getPosy()>=40) && ((*it)->getPosx()<=250 && (*it)->getPosy()<=660))//derecha
            {
                (*it)->setResis(3);
            }
            if(((*it)->getPosx()>=290 && (*it)->getPosy()>=440) && ((*it)->getPosx()<=500 && (*it)->getPosy()<=660))//centroinf
            {
                (*it)->setResis(3);
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
        if(map==3)
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
                (*it)->setResis(5);
            }
            if(((*it)->getPosx()>=540 && (*it)->getPosy()>=40) && ((*it)->getPosx()<=760 && (*it)->getPosy()<=660))//izquierda
            {
                (*it)->setResis(5);
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
                 (*it)->setResist(0.5);
             }
             if(((*it)->getPosx()>=290 && (*it)->getPosy()>=40) && ((*it)->getPosx()<=500 && (*it)->getPosy()<=150))//centrosup
             {
                 (*it)->setResist(0.5);
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
                (*it)->setResist(0.5);
            }
            if(((*it)->getPosx()>=40 && (*it)->getPosy()>=40) && ((*it)->getPosx()<=250 && (*it)->getPosy()<=660))//derecha
            {
                (*it)->setResist(0.8);
            }
            if(((*it)->getPosx()>=290 && (*it)->getPosy()>=440) && ((*it)->getPosx()<=500 && (*it)->getPosy()<=660))//centroinf
            {
                (*it)->setResist(0.8);
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
        if(map==3)
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
                (*it)->setResist(1);
            }
            if(((*it)->getPosx()>=540 && (*it)->getPosy()>=40) && ((*it)->getPosx()<=760 && (*it)->getPosy()<=660))//izquierda
            {
                (*it)->setResist(1);
            }

        }

    }
}

void MainWindow::eleccion_mapa(int ma)
{
    if(ma==1)
    {
        /*
        Paredes.
        */
        scene->clear();
        pared_do = new pared(0,-680,780,20);
        pared_der = new pared(-780,0,20,700);
        pared_up = new pared(0,0,780,20);
        pared_izq = new pared(0,0,20,680);
        paredes.push_back(pared_do);
        paredes.push_back(pared_der);
        paredes.push_back(pared_up);
        paredes.push_back(pared_izq);
        scene->addItem(pared_up);
        scene->addItem(pared_der);
        scene->addItem(pared_izq);
        scene->addItem(pared_do);

        /*
        Suelo.
        */
        suelos.push_back(new suelo(-20,-20,250,660,3));
        scene->addItem(suelos.back());
        suelos.push_back(new suelo(-270,-20,250,150,1));
        scene->addItem(suelos.back());
        suelos.push_back(new suelo(-520,-20,260,660,2));
        scene->addItem(suelos.back());
        suelos.push_back(new suelo(-270,-400,250,280,1));
        scene->addItem(suelos.back());
        suelos.push_back(new suelo(-270,-170,250,250,1));
        scene->addItem(suelos.back());
    }
    if(ma==2)
    {
        //player_1->setMapa(2);
        scene->clear();
        pared_do = new pared(0,-680,780,20);
        pared_der = new pared(-780,0,20,700);
        pared_up = new pared(0,0,780,20);
        pared_izq = new pared(0,0,20,680);
        paredes.push_back(pared_do);
        paredes.push_back(pared_der);
        paredes.push_back(pared_up);
        paredes.push_back(pared_izq);
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
    if(ma==3)
    {
        //player_1->setMapa(3);
        scene->clear();
        pared_do = new pared(0,-670,780,20);
        pared_der = new pared(-780,0,20,700);
        pared_up = new pared(0,0,780,20);
        pared_izq = new pared(0,0,20,680);
        paredes.push_back(pared_do);
        paredes.push_back(pared_der);
        paredes.push_back(pared_up);
        paredes.push_back(pared_izq);
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
                  name_jugador = texto_separado[0];
                  ronda_aux = texto_separado[1].toInt();
                  color_jugador = texto_separado[2].toInt();
                  QMessageBox::information(this,tr("!!!!"),tr("has iniciado correctamente"));
                  return;
              }

           }
           archivo.close();
           QMessageBox::information(this,tr("ERROR"),tr("jugador no encontrado"));
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
        in << texto_verificar << ";" << "1" << ";" << "1" << ";" << endl;
        QMessageBox::information(this,tr("!!!!!"),tr("¡Te has registrado con exito!"));
        archivo_2.close();
        return;
    }
}

void MainWindow::on_opcion_1_clicked()
{
    mapa_cho=1;
}

void MainWindow::on_opcion_2_clicked()
{
    mapa_cho=2;
}

void MainWindow::on_opcion_3_clicked()
{
    mapa_cho=3;
}

void MainWindow::iniciar_juego()
{
    if(multiplayer==1)
    {
        eleccion_mapa(mapa_cho);
        player_2 = new jugador(350,250,20,1,1);
        jugadores.push_back(player_2);
        scene->addItem(player_2);
        player_1 = new jugador(390,290,20,1,2);
        jugadores.push_back(player_1);
        scene->addItem(player_1);
        timer->start(10);
        timer_movimientos->start(100);
        timer_enemigos->start(5000);
        generacion_enemigos();
        ronda_aux = 1;
        ui->label->hide();
        ui->label_2->hide();
        ui->label_3->hide();
        //ui->label_4->hide();
        //ui->label_5->hide();
        ui->opcion_1->hide();
        ui->opcion_2->hide();
        ui->opcion_3->hide();
        ui->pushButton->hide();
        ui->texto_crear->hide();
        ui->iniciar_game->hide();
        ui->texto_inicio->hide();
        ui->crear_usuario->hide();
        ui->verificar_inicio->hide();
        ui->push_menu->hide();
        ui->pushButton_2->hide();
        in_game=true;


    }
    if(multiplayer==2)
    {
        if(name_jugador.isEmpty())
        {
            QMessageBox::information(this,tr("!!!!!"),tr("¡Debes iniciar sesion primero!"));
            return;
        }
        eleccion_mapa(mapa_cho);
        player_1 = new jugador(390,290,20,ronda_aux,color_jugador);
        jugadores.push_back(player_1);
        scene->addItem(player_1);
        timer->start(10);
        timer_movimientos->start(100);
        timer_enemigos->start(5000);
        generacion_enemigos();
        ui->label->hide();
        ui->label_2->hide();
        ui->label_3->hide();
        //ui->label_4->hide();
        //ui->label_5->hide();
        ui->opcion_1->hide();
        ui->opcion_2->hide();
        ui->opcion_3->hide();
        ui->pushButton->hide();
        ui->texto_crear->hide();
        ui->iniciar_game->hide();
        ui->texto_inicio->hide();
        ui->crear_usuario->hide();
        ui->verificar_inicio->hide();
        ui->push_menu->hide();
        ui->pushButton_2->hide();
        dificult = dificult - (0.1 * player_1->getRonda());
        dano_balas = dano_balas - player_1->getRonda();
        in_game=true;

    }
}

void MainWindow::guardado()
{
    QFile archivo("datos.txt");
    QFile new_archivo("datosnew.txt");
    QStringList texto_separado;
    if (archivo.open(QIODevice::ReadOnly) && new_archivo.open(QIODevice::WriteOnly))
    {
        QTextStream in(&archivo);
        QTextStream wr(&new_archivo);
           while (!in.atEnd())
           {
              QString line = in.readLine();
              texto_separado = line.split(';');
              if(texto_separado[0]==name_jugador)
              {
                  wr << name_jugador << ";" << player_1->getRonda() << ";"  << player_1->getColor() << ";" << endl;
              }
              else
              {
                  wr << line << endl;
              }

           }
    }
    archivo.close();
    new_archivo.close();
    archivo.remove();
    new_archivo.rename("datos.txt");
}

void MainWindow::on_iniciar_game_clicked()
{
    multiplayer = 2;
    iniciar_juego();

}

void MainWindow::on_pushButton_clicked()
{   
    multiplayer = 1;
    iniciar_juego();
}

void MainWindow::on_push_menu_clicked()
{

    if(name_jugador.isEmpty())
    {
        QMessageBox::information(this,tr("!!!!!"),tr("¡Debes iniciar sesion primero!"));
        return;
    }
    scene = new QGraphicsScene(-300,-300,605,605);
    ui->graphicsView->resize(600,600);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setBackgroundBrush(QPixmap(":/new/prefix1/resources/0a97a7a03fe6a7cee9ac254f7f81fae8.jpg"));
    bolita_ruleta = new bolita(0,0,10);
    scene->addItem(bolita_ruleta);
    ruleta->start(10);
    definir_color = true;

}

void MainWindow::bolita_giro()
{
    bolita_ruleta->actualizar_posicion();

}

void MainWindow::on_pushButton_2_clicked()
{
    scene->clear();
    ui->graphicsView->resize(800,700);
    scene = new QGraphicsScene(0,0,790,690);
    ui->graphicsView->setScene(scene);
    scene->backgroundBrush();
    ui->graphicsView->setBackgroundBrush(QPixmap(":/new/prefix1/resources/aguacate.png"));
    if(definir_color==true)
    {
        ruleta->stop();
        if((bolita_ruleta->getPosx()<=-32.38 && bolita_ruleta->getPosy()>=-197.361) || (bolita_ruleta->getPosx()>-84.75 && bolita_ruleta->getPosy()<-181.15)) //cafe
        {
            color_jugador = 3;
        }
        if((bolita_ruleta->getPosx()<=-89.25 && bolita_ruleta->getPosy()>=-178.97) || (bolita_ruleta->getPosx()>-177.10 && bolita_ruleta->getPosy()<-92.91))  // rosa
        {
            color_jugador = 2;
        }
        if((bolita_ruleta->getPosx()<=-179.37 && bolita_ruleta->getPosy()>=-88.46) || (bolita_ruleta->getPosx()>-196.65 && bolita_ruleta->getPosy()<-36.42)) //azul cla
        {
            color_jugador = 1;
        }
        if((bolita_ruleta->getPosx()<=-197.99 && bolita_ruleta->getPosy()>=-28.27) || (bolita_ruleta->getPosx()>-182.87 && bolita_ruleta->getPosy()<86.973)) //amarillo
        {
            color_jugador = 4;
        }
        if((bolita_ruleta->getPosx()<=-180.74 && bolita_ruleta->getPosy()>=85.51) || (bolita_ruleta->getPosx()>-96.57 && bolita_ruleta->getPosy()<175.13))  //verde
        {
            color_jugador = 5;
        }
        if((bolita_ruleta->getPosx()<=-89.15 && bolita_ruleta->getPosy()>=179) || (bolita_ruleta->getPosx()>-32.26 && bolita_ruleta->getPosy()<197.38))   //azul oscu
        {
            color_jugador = 6;
        }
        if((bolita_ruleta->getPosx()<=196.94 && bolita_ruleta->getPosy()>=34.82) || (bolita_ruleta->getPosx()>180 && bolita_ruleta->getPosy()<87))    //azul cla
        {
            color_jugador = 1;
        }
        if((bolita_ruleta->getPosx()<=177.85 && bolita_ruleta->getPosy()>=91.46) || (bolita_ruleta->getPosx()>95.14 && bolita_ruleta->getPosy()<175.91)) //rosa
        {
            color_jugador = 2;
        }
        if((bolita_ruleta->getPosx()<=90.72 && bolita_ruleta->getPosy()>=178.24) || (bolita_ruleta->getPosx()>29 && bolita_ruleta->getPosy()<197.9)) // cafe
        {
            color_jugador = 3;
        }
        if((bolita_ruleta->getPosx()<=84.71 && bolita_ruleta->getPosy()>=-181.17) || (bolita_ruleta->getPosx()>32.33 && bolita_ruleta->getPosy()<-97.36)) //azul oscu
        {
            color_jugador =  6;
        }
        if((bolita_ruleta->getPosx()<=196.64 && bolita_ruleta->getPosy()>=-36.47) || (bolita_ruleta->getPosx()>179.35 && bolita_ruleta->getPosy()<-88.5)) //amarillo
        {
            color_jugador = 4;
        }
        if((bolita_ruleta->getPosx()<=177 && bolita_ruleta->getPosy()>=-93) || (bolita_ruleta->getPosx()>86.21 && bolita_ruleta->getPosy()<-179)) //verde
        {
            color_jugador = 5;
        }
    }

}
