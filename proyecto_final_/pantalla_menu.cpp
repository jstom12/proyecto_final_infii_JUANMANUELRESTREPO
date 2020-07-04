#include "pantalla_menu.h"
#include "ui_pantalla_menu.h"

Pantalla_Menu::Pantalla_Menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Pantalla_Menu)
{
    ui->setupUi(this);
    //ui->graphicsView->resize(940,650);
    scene = new QGraphicsScene(0,0,940,640);
    ui->graphicsView->setScene(scene);
    scene->backgroundBrush();
    ui->graphicsView->setBackgroundBrush(QPixmap(":/new/prefix1/resources/aguacate.png"));

    //QMessageBox::information(this,tr("BIENVENIDO"),tr("¡recuerda iniciar o crear sesion y elegir un mapa antes de entrar a jugar!"));
    //player_1 = new jugador(20,20,15);
    //scene->addItem(player_1);
}

Pantalla_Menu::~Pantalla_Menu()
{
    delete ui;
}



void Pantalla_Menu::on_verifica_inicio_clicked()
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

void Pantalla_Menu::on_verificar_crear_clicked()
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

void Pantalla_Menu::on_opcion_1_clicked()
{

}

void Pantalla_Menu::on_opcion_2_clicked()
{

}

void Pantalla_Menu::on_opcion_3_clicked()
{

}

void Pantalla_Menu::on_iniciar_juego_clicked()
{
    this->hide();
}
