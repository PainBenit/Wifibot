
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
    robot.disconnect();
}

void MainWindow::initialise()
{
    robot.doConnect();
    connect(&robot, SIGNAL(updateUI(const QByteArray)),this,SLOT(on_Batterie_valueChanged(const QByteArray)));
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


void MainWindow::on_Batterie_valueChanged(int value)
{
    ui->Batterie->setValue(robot.DataReceived[2]);
}

