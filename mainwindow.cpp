
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&robot, SIGNAL(updateUI(QByteArray)), this, SLOT(updateWindow(QByteArray)));

}

MainWindow::~MainWindow()
{
    delete ui;
    robot.disconnect();

}

void MainWindow::initialise()
{
    robot.doConnect();


}

void MainWindow::updateWindow(QByteArray data) {
    on_Batterie_valueChanged(data);
    updateSpeed(data);

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

    float maxVolt = 10.1;
    float minVolt = 1.28;
    float scale = 4;

   unsigned char a = (unsigned char)data[2];
    float curVolt = a * scale / 100;
   float curBat =  ((curVolt-minVolt)/(maxVolt-minVolt))*100;
    ui->Batterie->setValue(curBat);
}


void MainWindow::updateSpeed(QByteArray data)
{
    long odometryL = ((long)data[8]<<24)+((long)data[7]<<16)+((long)data[6]<<8)+((long)data[5]);
    long odometryR = ((long)data[16]<<24)+((long)data[15]<<16)+((long)data[14]<<8)+((long)data[13]);

}

void MainWindow::updateIR(QByteArray data)
{
    unsigned char IRL1 = (unsigned char)data[3];
    unsigned char IRL2 = (unsigned char)data[4];
    unsigned char IRR1 = (unsigned char)data[11];
    unsigned char IRR2 = (unsigned char)data[12];

}






