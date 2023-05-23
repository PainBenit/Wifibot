
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    robot.doConnect();
}

MainWindow::~MainWindow()
{
    delete ui;
    robot.disconnect();
}



void MainWindow::on_pushButton_clicked()
{
    robot.MoveForward();
}


void MainWindow::on_pushButton_2_clicked()
{
    robot.TurnRight();
}




void MainWindow::on_pushButton_4_clicked()
{
    robot.TurnLeft();
}




void MainWindow::on_pushButton_3_clicked()
{
    robot.MoveBackward();
}

