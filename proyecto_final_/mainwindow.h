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
#include <pantalla_menu.h>


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

    void generacion_enemigos();

    void movimientos_enemigos();

    int dano_enemigos(QList<bala*> balas);

    void eliminar_enemigos();

    void dano_jugador();

    void eliminacion_jugador();

    void inercia_(int map);

    void inercia_enemigos(int map);

    void on_verificar_inicio_clicked();

    void on_crear_usuario_clicked();

    void on_opcion_1_clicked();

    void on_opcion_2_clicked();

    void on_opcion_3_clicked();

    void iniciar_juego();

    void on_iniciar_game_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;    
    QGraphicsScene *scene;
    QTimer *timer;
    QTimer *timer_enemigos;
    QTimer *timer_movimientos;
    jugador *player_1;
    jugador *player_2;
    QList<enemy*> enemigos;
    QVector<jugador*> jugadores;
    int ronda_aux;
    bool multiplayer;
    bala *disparo;
    QList<bala*> balas_up;
    QList<bala*> balas_down;
    QList<bala*> balas_righ;
    QList<bala*> balas_left;
    pared *pared_der;
    pared *pared_izq;
    pared *pared_up;
    pared *pared_do;
    //suelo *suelo_1;
    //suelo *suelo_2;
    //suelo *suelo_3;
    //suelo *suelo_4;
    //suelo *suelo_5;
    QVector<suelo*> suelos;

    pantalla_menu *new_pantalla;
    void keyPressEvent(QKeyEvent *evento);


};
#endif // MAINWINDOW_H
