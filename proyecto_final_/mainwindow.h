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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void disparar(int posicion);
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsScene *scene_2;
    QTimer *timer;
    jugador *player_1;
    bala *disparo;
    //int *posicion;
    void keyPressEvent(QKeyEvent *evento);


};
#endif // MAINWINDOW_H
