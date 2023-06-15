
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myrobot.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initialise();

private slots:
    void on_Haut_clicked();

    void on_Droite_clicked();

    void on_Gauche_clicked();

    void on_Bas_clicked();

    void on_Batterie_valueChanged(QByteArray data);

    void updateWindow(QByteArray data);

    void updateSpeed(QByteArray data);

    unsigned char* updateIR(QByteArray data);

    void on_Connexion_clicked();

    void on_Deconnexion_clicked();

    void on_Stop_clicked();

    void on_plainTextEdit_textChanged();

private:
    Ui::MainWindow *ui;
    MyRobot robot;

};

#endif // MAINWINDOW_H
