#ifndef PANTALLA_MENU_H
#define PANTALLA_MENU_H

#include <QMainWindow>
#include <QDialog>

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
    void on_verificar_clicked();

    void on_crear_clicked();

    void on_op_1_clicked();

    void on_op_2_clicked();

    void on_op_3_clicked();

private:
    Ui::Pantalla_Menu *ui;
};

#endif // PANTALLA_MENU_H
