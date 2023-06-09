
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&robot, SIGNAL(updateUI(QByteArray)), this, SLOT(updateWindow(QByteArray data)));

}

MainWindow::~MainWindow()
{
    delete ui;
    robot.disconnect();

}

void MainWindow::initialise()
{
    robot.doConnect();
    /*connect(&robot, SIGNAL(updateUI(QByteArray)), this, SLOT(on_Battery_valueChanged()));*/

}

void MainWindow::updateWindow(QByteArray data) {
    on_Batterie_valueChanged(data);

}
void MainWindow::on_pushButton_clicked()
{
    robot.MoveForward();
}


void MainWindow::on_pushButton_2_clicked()
{
    qDebug()<<"Droite";
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


void MainWindow::on_Batterie_valueChanged(QByteArray data)
{
   unsigned char battery = (unsigned char)data[2];
    ui->Batterie->setValue(battery);
}

