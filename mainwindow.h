
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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_Batterie_valueChanged(QByteArray data);

    void updateWindow(QByteArray data);

    void updateSpeed(QByteArray data);

    void updateIR(QByteArray data);

private:
    Ui::MainWindow *ui;
    MyRobot robot;

};

#endif // MAINWINDOW_H
