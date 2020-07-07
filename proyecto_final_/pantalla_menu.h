#ifndef PANTALLA_MENU_H
#define PANTALLA_MENU_H

#include <QMainWindow>
#include <QGraphicsScene>
//#include <QTimer>
//#include <QKeyEvent>
#include <jugador.h>
#include <bala.h>
#include <QDialog>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QMessageBox>



namespace Ui {
class Pantalla_Menu;
}

class Pantalla_Menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Pantalla_Menu(QWidget *parent = nullptr);
    ~Pantalla_Menu();

private slots:


    void on_verifica_inicio_clicked();

    void on_verificar_crear_clicked();

    void on_opcion_1_clicked();

    void on_opcion_2_clicked();

    void on_opcion_3_clicked();

    void on_iniciar_juego_clicked();

    void on_pushButton_clicked();

private:
    Ui::Pantalla_Menu *ui;
    //MainWindow *pantalla_volver;
    QGraphicsScene *scene;
    //QTimer *timer;
    //jugador *player_1;
    //bala *disparo;
    //QList<bala*> balas_up;
    //QList<bala*> balas_down;
    //QList<bala*> balas_righ;
    //QList<bala*> balas_left;


};

#endif // PANTALLA_MENU_H
