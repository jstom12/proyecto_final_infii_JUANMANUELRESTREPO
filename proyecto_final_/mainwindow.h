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
#include "pantalla_menu.h"
#include <QMenuBar>


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



    void disparar(int posicion);


    void on_verificar_inicio_clicked();

    void on_crear_usuario_clicked();

    void on_opcion_1_clicked();

    void on_opcion_2_clicked();

    void on_opcion_3_clicked();

    void on_iniciar_game_clicked();

private:
    Ui::MainWindow *ui;
    Pantalla_Menu *second_pantalla;
    QGraphicsScene *scene;
    QTimer *timer;
    jugador *player_1;
    bala *disparo;
    QList<bala*> balas_up;
    QList<bala*> balas_down;
    QList<bala*> balas_righ;
    QList<bala*> balas_left;

    //int *posicion;
    void keyPressEvent(QKeyEvent *evento);


};
#endif // MAINWINDOW_H
