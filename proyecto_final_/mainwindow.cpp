#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    /*
    Al iniciar el programa, se agrega una escena para los objetos graficos, se definen los timer y se conectan a su
    correspondiente funcion.

    En esta parte, el programa va a mostrar una interfaz grafica con un menu y, al momento de hacer uso de este, procedera
    a ejecutar las diferentes funciones.
    */
    ui->setupUi(this);
    scene = new QGraphicsScene(0,0,790,690);
    ui->graphicsView->setScene(scene);
    scene->backgroundBrush();
    ui->graphicsView->setBackgroundBrush(QPixmap(":/new/prefix1/resources/aguacate.png"));
    /*
    El QTimer timer esta conectado a la funcion proceso a una velocidad de 10ms, dentro de dicha funcion tiene otras funciones
    destinadas a la jugabilidad del juego (dano del jugador, trayecto de disparos, dano a enemigos) que necesitan
    estar ejecutandose de manera constante para el correcto funcionamiento.
    Se inicia al momento de iniciar el juego(con la funcion iniciar_juego).
    */
    timer = new QTimer();
    /*
    El QTimer timer_enemigos esta conectado a la funcion generacion_enemigos a una velocidad de 5000ms, dentro de dicha
    funcion esta el codigo que permite generar enemigos y agregarlos a la escena del juego.
    Se inicia al momento de iniciar el juego(con la funcion iniciar_juego).
    Se detiene al presionar ESC.
    */
    timer_enemigos= new QTimer();
    /*
    El QTimer timer_movimientos esta conectado a la funcion movimientos_enemigos a una velocidad de 100ms, dentro de dicha funcion
    se itera todos los enemigos y se ejecutan las funciones que permiten moverlos. la velocidad de 100ms
    es un tiempo que consigue que los movimientos no sean ni muy rapidos ni muy lentos.
    se inicia al momento de iniciar el juego(con la funcion iniciar_juego).
    Se detiene al presionar ESC
    */
    timer_movimientos = new QTimer();
    /*
    El QTimer jump esta conectado a la funcion salto_jugador a una velocidad de 20ms, dentro de dicha funcion se ejecuta la funcion
    que permite al jugador realizar el movimiento parabolico.
    Se inicia al momento de presionar las teclas Q o U que son las definidas para realizar los saltos.
    Se detiene al momento en el que el jugador vuelve a su tamano original.
    */
    jump = new QTimer();
    /*
    El QTimer ruleta esta conectado a la fucion bolita_giro a una velocidad de 10ms, dentro de dicha funcion se ejecuta la funcion
    que permite a la bolita actualizar su posicion. Note que tiene la misma velocidad que el QTimer timer pero, dado a que funcionan
    en escenas distintas, se opto por utilizar un timer diferente para evitar problemas en tiempo de ejecucion.
    */
    ruleta = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(procesos()));
    connect(timer_enemigos,SIGNAL(timeout()),this,SLOT(generacion_enemigos()));
    connect(timer_movimientos,SIGNAL(timeout()),this,SLOT(movimientos_enemigos()));
    connect(jump,SIGNAL(timeout()),this,SLOT(salto_jugador()));
    connect(ruleta,SIGNAL(timeout()),this,SLOT(bolita_giro()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *evento)
{
    if(evento->key()==Qt::Key_B)
    {
        /*
        La tecla B permite esconder los controles de los jugadores.
        */
        ui->label_8->hide();
        ui->label_9->hide();
        ui->label_10->hide();
        ui->label_11->hide();
        ui->label_12->hide();
        ui->label_13->hide();
        ui->label_14->hide();
        ui->label_15->hide();
        ui->label_16->hide();
        ui->label_17->hide();
        ui->label_20->hide();
    }
    if(evento->key()==Qt::Key_V)
    {
        /*
        La tecla V permite mostrar los controles de los jugadores.
        */
        ui->label_10->show();
        ui->label_11->show();
        ui->label_12->show();
        ui->label_13->show();
        ui->label_14->show();
        ui->label_15->show();
        ui->label_16->show();
        ui->label_17->show();
        ui->label_20->show();
    }
    if(in_game==true)
    {
        /*
        Esta condicion esta para que solo se pueda ejecutar los controles de jugador
        cuando se este ejecutando el juego; De lo contrario, no se ejecutaras. Esto para evitar
        errores durante el tiempo en el que no se este ejecutando el juego.
        */
        if(evento->key()==Qt::Key_Escape)
        {
            /*
            La tecla ESC permite reiniciar la partida, es decir, si el jugador muere permite regresar al menu
            o salirse del juego durante su ejecucion para regresar al menu.

            Para esto, se eliminan todos los objetos graficos de la escena, se detienen los timer y se muestra
            la interfez del menu.
            */
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
        if(multiplayer==2 || multiplayer==1)
        {
            /*
            Esta funcion esta para evitar que, al presionar los controles del multijugador,
            se genere un error en la ejecucion.
            Cuando multiplayer es igual a 2 significa que se esta jugando en modo un jugador y solo se
            ejecutaran los controles del jugador 1;
            Cuando multiplayer es igual a 1 significa que se esta jugando en modo multijugador y se podran
            ejecutar los controles de ambos jugadores sin errores.
            */
            if(evento->key()==Qt::Key_Q)
            {
                /*
                La tecla Q ejecuta un movimiento parabolico que simula un salto por parte del jugador.
                Para esto se indica que el jugador esta saltando con la variable choose_salto_jugador(
                true para el jugador 1, false para el jugador 2)
                y se inicia el timer que ejecuta los saltos. Dentro de la funcion se detiene el timer
                y se cambia el valor de la variable para dejarlos a la espera de otro salto.
                */
                choose_salto_jugador=true;
                jump->start(20);
            }
            if(evento->key()==Qt::Key_D)
            {
                /*
                Las teclas AWSD ejecutan los movimientos del jugador 1. Para realizar los saltos y disparos es necesario
                saber a que direccion se esta mirando; Para esto se define una variable dir y recibe un valor cada que se
                presiona una tecla, ese valor lo reconocen las funciones como la direccion hacia donde esta mirando el jugador.
                */
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
                /*
                La tecla R permite al jugador disparar; Lo que se hace aqui es llamar a la funcion disparar
                que recibe la posicion actual del jugador junto a la direccion a la que esta mirando.
                */
                disparar(player_1->getPosx(),player_1->getPosy(),player_1->getDir());
            }
        }

        if(multiplayer==1)
        {
            /*
            Las teclas JIKL ejecutan los movimientos del jugador 1. Para realizar los saltos y disparos es necesario
            saber a que direccion se esta mirando; Para esto se define una variable dir y recibe un valor cada que se
            presiona una tecla, ese valor lo reconocen las funciones como la direccion hacia donde esta mirando el jugador.
            */
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
                /*
                La tecla P permite al jugador disparar; Lo que se hace aqui es llamar a la funcion disparar
                que recibe la posicion actual del jugador junto a la direccion a la que esta mirando.
                */
                disparar(player_2->getPosx(),player_2->getPosy(),player_2->getDir());
            }
            if(evento->key()==Qt::Key_U)
            {
                /*
                La tecla U ejecuta un movimiento parabolico que simula un salto por parte del jugador.
                Para esto se indica que el jugador esta saltando con la variable choose_salto_jugador
                y se inicia el timer que ejecuta los saltos. Dentro de la funcion se detiene el timer
                y se cambia el valor de la variable para dejarlos a la espera de otro salto.
                */
                choose_salto_jugador = false;
                jump->start(20);
            }
        }
    }

}

void MainWindow::disparar(float posx ,float posy , int posicion)
{
    /*
    La funcion disparar lo que hace es recibir una posicion en x, una posicion en Y y un entero
    que corresponde a la direccion; se crea el objeto grafico que corresponde a la bala con
    las posiciones X y Y con un tamano de radio 5 y el entero que corresponde a la direccion
    lo que hace es, dependiendo el numero, agregarlo a una lista de balas en particular. Esto
    ultimo necesario para el movimiento de las balas.
     */
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

    /*
    En esta funcion se ejecutan todas esas funciones necesarias para la ejecucion del juego.
    */


    /*
    Estas 4 lineas corresponden a la funcion que realiza el movimiento de las balas,
    recibe una lista de balas y un entero que corresponde a la direccion.
    */
    animacion_balas(balas_up,1);
    animacion_balas(balas_down,2);
    animacion_balas(balas_left,3);
    animacion_balas(balas_righ,4);

    /*
    Estas 4 lineas corresponden a la funcion que verifica si las balas estan en contacto con
    alguna pared para así eliminar las balas de la escena. recibe una lista de balas.
    */
    choques_balas(balas_up);
    choques_balas(balas_down);
    choques_balas(balas_left);
    choques_balas(balas_righ);

    /*
    Las siguientes lineas corresponden a el dano que realizan las balas a los enemigos.
    Es necesario una variable entero (en este caso aux) para almacenar la posicion de la bala
    que toca un enemigo para poder eliminarla de la escena y de su lista correspondiente.
    */
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

    /*
    La siguiente funcion corresponde a la encargada para verificar que enemigo tiene una vida menor 0 igual a
    0 para eliminarlo de la escena.
    */
    eliminar_enemigos();
    /*
    Esta condicion permite que, cuando el jugador este saltando, los enemigos no puedan hacerle dano
    (debido a que el dano de los enemigos es cuando los objetos graficos se tocan y durante el salto,
    para hacer el efecto de saltar, el jugador crece en tamano).
    */
    if(in_jump==false)
    {
        dano_jugador();
    }


    /*
    Estas lineas actualizan en la interfaz grafica los numeros que corresponden a la vida, la ronda y la oleada del jugador;
    Si esta en modo multijugador, actualiza tambien la vida de un segundo jugador.
    */
    ui->label_4->setText(QVariant(player_1->getVida()).toString());
    ui->label_5->setText(QVariant(player_1->getRonda()).toString());
    ui->label_7->setText(QVariant(ronda_aux).toString());
    if(multiplayer==1)
    {
        ui->label_6->setText(QVariant(player_2->getVida()).toString());
    }

    /*
    esta funcion verifica la vida del jugador para saber si fue o no eliminado.
    */
    eliminacion_jugador();


}

void MainWindow::animacion_balas(QList<bala *> lista , int pos)
{
    /*
    esta funcion realiza los movimientos de las balas, recibe una lista y un entero que corresponde a la
    posicion y recorre toda la lista ejecutando la funcion de movimiento que corresponden a la direccion recibida con la lista.
    */
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
    /*
    la funcion salto_jugador se encarga de, cuando se indica que el jugador va a realizar un salto,
    elige primero si es el jugador 1 o el jugador 2 quien va a realizar el salto (esto con la variable
    choose_salto_jugador) y empieza a ejecutar la funcion actualizar_velocidad y actualizar_tamano en el jugador.
    Cuando el tamano del jugador llega a ser menor o igual a 20 significa que el salto termino y, para dejarlo
    listo para un proxima salto, se devuelven las variables utilizadas para realizar el salto a su valor predeterminado.

    NOTA: Si el jugador intenta salir del mapa saltando, es decir sale de la zona de juego, se le quita toda la vida y se termina
    el juego.
    */
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

    /*
    En esta funcion se inicializan dos variables tipo iterador, una que corresponde a la lista de balas
    recibida y otra que corresponde a la lista de paredes; Luego se mepieza a verificar si alguna bala colisiona
    con alguna pared para proceder a eliminar la bala de la escena. De no chocar con ninguna pared, no se hace nada con la bala.
    */
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
    /*
    La funcion de generacion_enemigos es la que se encarga que generar enemigos en la escena;
    la variable ronda_aux corresponde a la oleada en la que se encuentra el jugador y, mientras esta
    es diferente de 0, se generan enemigos y se resta 1 a la variable. Así cuando la variable ronda_aux es igual
    a 0 y todos los enemigos fueron eliminador, se suma 1 a la rondas del jugador, se le resta un 0.1 a la variable
    dificult siempre que dificult sea diferente de 0 y se le resta 1 a la variable dano_balas siempre que la variable
    sea mayor a 10. Luego se realiza un guardado de los datos del jugador.
    */
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
    /*
    Esta funcion hace recibe una variable de tipo jugador y verifica que este dentro de la zonda de juego.
    Si lo esta, retorna un true; si no lo está retorna un false.
    */
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
    /*
    La funcion movimientos_enemigos se encarga de mover a los enemigos en la direccion del jugador.
    primera se ejecuta la funcion inercia_enemigos que recibe la variable mapa_cho que es un entero
    que corresponde al mapa donde se juega.
    luego se inicia un iterador de tipo jugador y se ejecuta un for que evalua todos los enemigos
    que hay en la escena. dentro del ciclo se ejecutan dos fuciones en cada enemigos que recibe la posicion del
    jugador y la variable dificult (esta variable lo que hace es restarle velocidad a los enemigos, cuanto
    mas avances en el juego, menor sera el valor de dificult).
    */
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
    /*
    La funcion dano_enemigos recibe una lista de balas; luego
    se itera en cada enemigo en la escena todas las balas para verificar si colisionan, si
    colision se le resta el valor de la variable dano_balas a la vida del enemigos y luego
    se retorna la posicion de la bala para proceder a elimarla en la funcion de procesos.
    */
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
    /*
    Si no se cumple la condicion dentro del for, se retorna un -1 indicando que las balas no colisionan con ningun enemigos.
    */
    return -1;
}

void MainWindow::eliminar_enemigos()
{
    /*
    La funcion es encargada de verificar si la vida de los enemigos es menor a 0, si esta condicion se
    cumple entonces se elimina el enemigo de la escena y de la lista de enemigos.
    Hay una variable posicion_aux que es un entero que recibe la posicion del enemigo que se quiere
    eliminar para proceder a eliminarlo de la escena y de la lista sin errores. Luego se retorna la funcion
    para dejar de ejecutarla y así evitar errores.
    */
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
    /*
    la funcion dano_jugador es la encargada de verificar si los enemigos colisionan con el jugador
    para efectuar una reduccion en la vida del jugador.
    Se inicializan dos iteradores, uno tipo jugador y otro tipo enemy, luego se itera en cada jugador
    todos los enemigos y se verifica si colisiona con alguno, si esto pasa, se inicializa la variable entera
    nueva_vida que es el resultado de la vida actual del jugador menos el dano que realiza el enemigos.
    luego se setea la nueva vida del jugador, se guarda la posicion del enemigo y se elimina de la escena.
    */
    QVector<jugador*>::iterator it;
    QList<enemy*>::iterator itm;
    for(it=jugadores.begin();it!=jugadores.end();it++)
    {
        for(itm=enemigos.begin();itm!=enemigos.end();itm++)
        {
            if((*it)->collidesWithItem((*itm)))
            {
                int nueva_vida= (*it)->getVida()-(*itm)->getDano();
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
    /*
    La funcion eliminacion_jugador verifica si hay algun jugador en la lista de jugadores que
    tengo la vida menor o igual a cero, si esto es positivo entonces se elimina el jugador de la escena
    y, si la lista de jugadores queda vacia, se detiene los timer y la ejecucion del juego.
    */
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
    /*
    La funcion inercia_ es la encargada de definir la resistencia al movimiento que genera el mapa
    sobre el jugador. Vemos que itera en la lista de jugadores, obtiene el mapa que eligió el jugador
    e iniciar a definir la variable resis al jugador. Esta variable es la que limita los movimientos
    del jugador.
    */
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
    /*
    La funcion inercia_enemigos funciona de manera similar a la funcion inercia_ pero esta es disenada
    para los enemigos. dado a que los movimientos de los enemigos son un poco mas limitados que los del jugador, los
    valores de la inercia son equivalentes a los de la inercia del jugador pero en cifras menores.
    Otra vez, la funcion itera en la lista de enemigos y define la variable resist de cada uno.
    */
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
    /*
    la funcion eleccion_mapa permite graficar diferentes mapas que selecciona el jugador en la
    interfez grafica.
    Recibe un entero que corresponde al mapa a graficar. Luego, entra en una condicion
    y anade todos los objetos a la escena.
    */
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
    /*
    Esta funcion se activa cuando el jugador presiona el boton para iniciar sesion;
    En esta se recibe el nombre del jugador, se abre el archivo de texto donde se
    almacenan los datos de los jugadores y se verifica si existe el jugador, es decir, si
    esta registrado. Si esto ultimo se da entonces se recolectan los datos del jugador
    (nombre, ronda, color) y se guardan en el programa para proceder a iniciar el juego.
    */
    QString texto_verificar = ui->texto_inicio->text();
    QFile archivo("datos.txt");
    QStringList texto_separado;
    if (archivo.open(QIODevice::ReadOnly))
    {
        /*
        Aqui se recorre linea por linea el archivo datos.txt y se procede a separar
        las lineas cada que se encuentre un ";" y se almacena la linea separada en una
        lista de strings, luego se verifica que la primera posicion de la lista (que corresponde
        al nombre del jugador) sea igual al nombre ingresado para proceder a obtener los datos.
        */
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
           /*
            De no coincidir ningun dato, se mostrara en pantalla que el jugador no fue encontrado.
            */
           archivo.close();
           QMessageBox::information(this,tr("ERROR"),tr("jugador no encontrado"));
    }
}

void MainWindow::on_crear_usuario_clicked()
{
    /*
    Esta funcion es llamada cuando el usuario presiona el boton para crear un usuario.
    Primero se recibe el nombre a crear y se verifica que no este registrado.
    Si el jugador ya se encuentra en los datos entonces se mostrara un mensaje que muestre esto.
    El sistema que se usa es el mismo para verificar el inicio de un jugador.
    */
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
        /*
        Luego, si el jugador no esta en los datos, se vuelve a abrir el archivo en modo
        escritura y se anade el nombre del jugador junto a unos datos predeterminados.
        */
        QTextStream in(&archivo_2);
        in << texto_verificar << ";" << "1" << ";" << "1" << ";" << endl;
        QMessageBox::information(this,tr("!!!!!"),tr("¡Te has registrado con exito!"));
        archivo_2.close();
        return;
    }
}

void MainWindow::on_opcion_1_clicked()
{
    // al presionar el boton del mapa, se define la variable mapa_cho como 1 que indica el mapa a crear.
    mapa_cho=1;
}

void MainWindow::on_opcion_2_clicked()
{
    // al presionar el boton del mapa, se define la variable mapa_cho como 2 que indica el mapa a crear.
    mapa_cho=2;
}

void MainWindow::on_opcion_3_clicked()
{
    // al presionar el boton del mapa, se define la variable mapa_cho como 3 que indica el mapa a crear.
    mapa_cho=3;
}

void MainWindow::iniciar_juego()
{
    /*
    Esta funcion es la que se encarga de poner en marcha el juego.
    Depentiendo de si se elije la opcion de un jugador o multijugador se inician igual
    con la unica diferencia que en el multijugador no es necesario iniciar sesion y se
    agrega el segundo jugador a la escena.

    De resto, se procede a llamar la funcion eleccion_mapa para que grafique el mapa, se crean los jugadores,
    se inician los timer, se generan los enemigos, se cambia la variable in_game a true indicando que se inicio el juego
    y se oculta el menu de la interfaz grafica.
    */
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
            /*
            Para la opcion de un jugador se anade esa condicion que, si el usuario no ha iniciado sesion,
            no le permite iniciar el juego y le muestra un mensaje diciendole eso.
            */
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
    /*
    La funcion de guardado permite actualizar los datos del jugador,
    esto abriendo el archivo de datos.txt en modo lectura y un nuevo archivo
    en modo escritura.
    se empieza a copiar los datos de un archivo a otro y la linea que corresponde al jugador
    es reemplazada por los nuevos datos. luego se elimina el archivo con los datos desactualizados
    y se cambio el nombre de los neuvos archivos a datos.txt
    */
    QFile archivo("datos.txt");
    QFile new_archivo("datosnew.txt");
    QStringList texto_separado; // esta variable para almacenar strings
    if (archivo.open(QIODevice::ReadOnly) && new_archivo.open(QIODevice::WriteOnly))
    {
        QTextStream in(&archivo);
        QTextStream wr(&new_archivo);
           while (!in.atEnd())
           {
              QString line = in.readLine();
              texto_separado = line.split(';'); // se separa la linea en varios strings.
              if(texto_separado[0]==name_jugador)
              {
                  /*
                    Se encuentran los datos del jugador y se reemplazan.
                    */
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
    /*
    esta funcion es llamada cuando se presiona el boton para iniciar el juegos, en esta se llama
    a la funcion iniciar_juego y se define la variable multiplayer igual a 2 indicando que
    se selecciono el modo de un jugador.
    */
    multiplayer = 2;
    iniciar_juego();

}

void MainWindow::on_pushButton_clicked()
{   
    /*
    Esta funcion es llamada cuando se presiona el boton de multiplayer y lo que hace es llamar a la funcion
    de iniciar_juego y definir la variable multiplayer igual a 1 indicando que el juego se va a ejecutar en modo
    multijugador.
    */
    multiplayer = 1;
    iniciar_juego();
}

void MainWindow::on_push_menu_clicked()
{
    /*
    Esta funcion es llamada al presionar el boton ruleta y lo que hace es mostrar la ruleta para que el jugador
    pueda cambiar el color de su personaje.
    Para esto es necesario cambiar la escena y esconder los botones que permiten iniciar el juego para evitar errores,
    luego se crean los espacios de colores y se agregan a la escena.
    Se inicia el timer ruleta que permite a la bolita de la ruleta girar al rededor y define la variable
    definir_color como true.
    */
    if(name_jugador.isEmpty())
    {
        QMessageBox::information(this,tr("!!!!!"),tr("¡Debes iniciar sesion primero!"));
        return;
    }

    ui->iniciar_game->hide(); // se esconden los botones de iniciar y multijugador.
    ui->pushButton->hide();
    scene = new QGraphicsScene(-300,-300,605,605); // se cambia la escena con (0,0) en en centro de esta.
    ui->graphicsView->resize(600,600);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setBackgroundBrush(QPixmap(""));


    /*
    Se crean y se agregan las zonas de colores a la escena.
    */
    cuadro_rosa = new jugador (-143,-140,50,1,2);
    scene->addItem(cuadro_rosa);
    cuadro_cafe = new jugador(-44,-195,50,1,3);
    scene->addItem(cuadro_cafe);
    cuadro_amarillo = new jugador(188,-67,50,1,4);
    scene->addItem(cuadro_amarillo);
    cuadro_azul_cla = new jugador(-196,-40,50,1,1);
    scene->addItem(cuadro_azul_cla);
    cuadro_azul_oscu = new jugador(45,-190,50,1,6);
    scene->addItem(cuadro_azul_oscu);
    cuadro_verde = new jugador(144,-138,50,1,5);
    scene->addItem(cuadro_verde);

    cuadro_rosa_2 = new jugador (137,146,50,1,2);
    scene->addItem(cuadro_rosa_2);
    cuadro_cafe_2 = new jugador(50,193,50,1,3);
    scene->addItem(cuadro_cafe_2);
    cuadro_amarillo_2 = new jugador(-196,40,50,1,4);
    scene->addItem(cuadro_amarillo_2);
    cuadro_azul_cla_2 = new jugador(197,31,50,1,1);
    scene->addItem(cuadro_azul_cla_2);
    cuadro_azul_oscu_2 = new jugador(-25,199,50,1,6);
    scene->addItem(cuadro_azul_oscu_2);
    cuadro_verde_2 = new jugador(-138,143,50,1,5);
    scene->addItem(cuadro_verde_2);

    /*
    Se crea y se agrega la bolita que hace gira en toda la escena. se inicializa el timer y se
    cambia la variable definir_color a true (indicando que se puede cambiar de color).
    */
    bolita_ruleta = new bolita(0,0,10);
    scene->addItem(bolita_ruleta);
    ruleta->start(10);
    definir_color = true;

}

void MainWindow::bolita_giro()
{
    /*
    Esta funcion esta conectada al timer ruleta y lo que hace es actualizar la posicion de la bolita para
    que realice un movimiento circular.
    */
    bolita_ruleta->actualizar_posicion();
}

void MainWindow::on_pushButton_2_clicked()
{
    /*
    Esta funcion es llamada cuando se presiona el boton stop y lo que hace es detener la ruleta.
    volver la escena a su estado original y definir el color del jugador.
    */
    ui->iniciar_game->show(); // se muestran los botones para iniciar y multijugador.
    ui->pushButton->show();
    ui->graphicsView->resize(800,700); // se cambia el tamano de la escena.
    scene = new QGraphicsScene(0,0,790,690); // se crea una nueva escena.
    ui->graphicsView->setScene(scene);
    scene->backgroundBrush();
    ui->graphicsView->setBackgroundBrush(QPixmap(":/new/prefix1/resources/aguacate.png"));
    if(definir_color==true)
    {
        /*
        Se detiene el QTimer ruleta y, dependiendo la bolita con que objeto grafico este colisionando, se define
        el color del jugador que es almacenado en la variable color_jugador.
        */
        ruleta->stop();
        if(bolita_ruleta->collidesWithItem(cuadro_azul_cla) || bolita_ruleta->collidesWithItem(cuadro_azul_cla_2))
        {
            color_jugador = 1;
            return;
        }
        if(bolita_ruleta->collidesWithItem(cuadro_rosa) || bolita_ruleta->collidesWithItem(cuadro_rosa_2))
        {
            color_jugador = 2;
            return;
        }
        if(bolita_ruleta->collidesWithItem(cuadro_cafe) || bolita_ruleta->collidesWithItem(cuadro_cafe_2))
        {
            color_jugador = 3;
            return;
        }
        if(bolita_ruleta->collidesWithItem(cuadro_amarillo) || bolita_ruleta->collidesWithItem(cuadro_amarillo))
        {
            color_jugador = 4;
            return;
        }
        if(bolita_ruleta->collidesWithItem(cuadro_verde) || bolita_ruleta->collidesWithItem(cuadro_verde_2))
        {
            color_jugador = 5;
            return;
        }
        if(bolita_ruleta->collidesWithItem(cuadro_azul_oscu) || bolita_ruleta->collidesWithItem(cuadro_azul_oscu_2))
        {
            color_jugador = 6;
            return;
        }
    }
}
