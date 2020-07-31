#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>
#include <QMainWindow>
#include <jugador.h>
#include <bala.h>
#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDialog>
#include <QMenuBar>
#include <pared.h>
#include <suelo.h>
#include <enemy.h>
#include <QDebug>
#include <bolita.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:



    void disparar(float posx, float posy, int posicion);

    void procesos();

    void animacion_balas(QList<bala*> lista , int pos);

    void salto_jugador();

    void choques_balas(QList<bala*> lista);

    void generacion_enemigos();

    bool area_jugador(jugador* player);

    void movimientos_enemigos();

    int dano_enemigos(QList<bala*> balas);

    void eliminar_enemigos();

    void dano_jugador();

    void eliminacion_jugador();

    void inercia_(int map);

    void inercia_enemigos(int map);

    void eleccion_mapa(int ma);

    void on_verificar_inicio_clicked();

    void on_crear_usuario_clicked();

    void on_opcion_1_clicked();

    void on_opcion_2_clicked();

    void on_opcion_3_clicked();

    void iniciar_juego();

    void guardado();

    void on_iniciar_game_clicked();

    void on_pushButton_clicked();

    void on_push_menu_clicked();

    void bolita_giro();

    void on_pushButton_2_clicked();

private:
    /*
    Parametros necesarios para la correcta ejecución del juego.
    */
    Ui::MainWindow *ui;    
    QGraphicsScene *scene;
    /*
    Timers para la ejecucion del juego.
    */
    QTimer *timer;
    QTimer *timer_enemigos;
    QTimer *timer_movimientos;
    QTimer *jump;
    QTimer *ruleta;

    /*
    variables de los objetos graficos.
    */
    /*
    Variables de tipo jugador que corresponden a los dos jugadores.
    */
    jugador *player_1;
    jugador *player_2;
    bolita *bolita_ruleta; // variable tipo bolita que es la que se muestra girando en la ruleta.
    QList<enemy*> enemigos; // QList de tipo enemy donde se almacenan los enemigos.
    QVector<jugador*> jugadores; // QVector donde se almacenan las dos variables de jugador.
    bala *disparo; // variable tipo bala que permite mostrar en la escena el disparo que se realiza.
    QList<bala*> balas_up; //QList tipo bala donde se almacenan las balas que van hacia arriba.
    QList<bala*> balas_down; //QList tipo bala donde se almacenan las balas que van hacia abajo.
    QList<bala*> balas_righ; //QList tipo bala donde se almacenan las balas que van hacia la derecha.
    QList<bala*> balas_left; //QList tipo bala donde se almacenan las balas que van hacia la izquierda.
    /*
    Variables tipo pared que forman un cuadrado para no permitir que los objetos graficos salgan de la escena.
    */
    pared *pared_der;
    pared *pared_izq;
    pared *pared_up;
    pared *pared_do;
    QVector<pared*> paredes; //Qvector tipo pared donde se almacenan las paredes.
    QVector<suelo*> suelos; //QVector tipo suelo donde se almacenan los suelos del mapa.
    QString name_jugador; //variable donde se almacena el nombre del jugador.
    /*
    Las siguientes variables tipo jugador son las utilizadas para graficar los circulos en la ruleta,
    dos de cada color para que, al momento de la bolita detenerse en alguno de estos, obtener ese color
    y darselo al jugador.
    */
    jugador *cuadro_amarillo;
    jugador *cuadro_rosa;
    jugador *cuadro_azul_cla;
    jugador *cuadro_azul_oscu;
    jugador *cuadro_verde;
    jugador *cuadro_cafe;
    jugador *cuadro_amarillo_2;
    jugador *cuadro_rosa_2;
    jugador *cuadro_azul_cla_2;
    jugador *cuadro_azul_oscu_2;
    jugador *cuadro_verde_2;
    jugador *cuadro_cafe_2;

    /*
    Auxiliares para la correcta ejecucion del codigo.
    */
    int ronda_aux; // obtiene la ronda del jugador para empezar el conteo de oleadas
    int multiplayer=0; //indica si juega un jugador(2) o multijugador(1).
    int mapa_cho=1; // indica la eleccion del mapa.
    int dano_balas=20; // el dano que realizan las balas a los enemigos.  (dano_enemigos)
    int color_jugador=1; // obtiene el color del jugador de la base de datos.
    float dificult=1; // esta variable permite reducir el movimiento de los enemigos.  (movimientos_enemigos)
    bool in_game=false; // variable que permite saber si el juego esta en ejecucion. (iniciar_juego)
    bool in_jump=false; // variable que permite saber si el jugador se encuentra saltando.
    bool choose_salto_jugador; // variable que permite saber, en multijugador, cual de los dos jugadores realizo el salto.
    bool definir_color=false; // variable que permite cambiar el color del jugador. Solo cambia a true al momento de detener la ruleta.


    void keyPressEvent(QKeyEvent *evento);


};
#endif // MAINWINDOW_H
