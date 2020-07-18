#ifndef PANTALLA_MENU_H
#define PANTALLA_MENU_H

#include <QMainWindow>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

namespace Ui {
class pantalla_menu;
}

class pantalla_menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit pantalla_menu(QWidget *parent = nullptr);
    ~pantalla_menu();

private slots:


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_multiplayer_clicked();

    void on_opcion_1_clicked();

    void on_opcion_2_clicked();

    void on_opcion_3_clicked();

    void on_iniciar_juego_clicked();

private:
    Ui::pantalla_menu *ui;
    QString nombre_player;
    int mapa=1;
    int multiplayer=1;
    int ronde=1;
};

#endif // PANTALLA_MENU_H
