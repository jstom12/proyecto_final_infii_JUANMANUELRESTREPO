#include "pantalla_menu.h"
#include "ui_pantalla_menu.h"

Pantalla_Menu::Pantalla_Menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Pantalla_Menu)
{
    ui->setupUi(this);
}

Pantalla_Menu::~Pantalla_Menu()
{
    delete ui;
}

void Pantalla_Menu::on_verificar_clicked()
{

}

void Pantalla_Menu::on_crear_clicked()
{

}

void Pantalla_Menu::on_op_1_clicked()
{

}

void Pantalla_Menu::on_op_2_clicked()
{

}

void Pantalla_Menu::on_op_3_clicked()
{

}
