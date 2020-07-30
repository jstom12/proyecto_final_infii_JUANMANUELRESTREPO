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
    jugador *player_1;
    jugador *player_2;
    bolita *bolita_ruleta;
    QList<enemy*> enemigos;
    QVector<jugador*> jugadores;
    bala *disparo;
    QList<bala*> balas_up;
    QList<bala*> balas_down;
    QList<bala*> balas_righ;
    QList<bala*> balas_left;
    pared *pared_der;
    pared *pared_izq;
    pared *pared_up;
    pared *pared_do;
    QVector<pared*> paredes;
    QVector<suelo*> suelos;
    QString name_jugador;
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
    int ronda_aux;
    int multiplayer=0;
    int mapa_cho=1;
    int dano_balas=20;
    int color_jugador=1;
    float dificult=1;
    bool in_game=false;
    bool in_jump=false;
    bool choose_salto_jugador;
    bool definir_color=false;


    void keyPressEvent(QKeyEvent *evento);


};
#endif // MAINWINDOW_H
