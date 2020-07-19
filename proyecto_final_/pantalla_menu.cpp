#include "pantalla_menu.h"
#include "ui_pantalla_menu.h"

pantalla_menu::pantalla_menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pantalla_menu)
{
    ui->setupUi(this);
}

pantalla_menu::~pantalla_menu()
{
    delete ui;
}


void pantalla_menu::on_pushButton_clicked()
{
    QString texto_verificar = ui->iniciar_sesion->text();
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
                  nombre_player = texto_separado[0];
                  ronde = texto_separado[1].toInt();
                  QMessageBox::information(this,tr("!!!!"),tr("has iniciado correctamente"));
                  return;
              }
           }
           archivo.close();
           QMessageBox::information(this,tr("ERROR"),tr("jugador no encontrado"));
    }
}

void pantalla_menu::on_pushButton_2_clicked()
{
    QString texto_verificar = ui->crear_jugador->text();
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

void pantalla_menu::on_multiplayer_clicked()
{
    multiplayer=2;
}

void pantalla_menu::on_opcion_1_clicked()
{
    mapa=1;
}

void pantalla_menu::on_opcion_2_clicked()
{
    mapa=2;
}

void pantalla_menu::on_opcion_3_clicked()
{
    mapa=3;
}

void pantalla_menu::on_iniciar_juego_clicked()
{
    if(nombre_player.isEmpty())
    {
        QMessageBox::information(this,tr("!!!!!"),tr("¡Debes iniciar sesion primero!"));
        return;
    }
    QFile en_juego("juego.txt");
    if (en_juego.open(QIODevice::WriteOnly))
    {
         QTextStream in(&en_juego);
         in << nombre_player << ";" << ronde << ";" << mapa << ";" << multiplayer;
         en_juego.close();
    }
    this->hide();
}
