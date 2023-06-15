
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //On fait en sorte que lorsqu'on recoit des donnees du robot on mette a jour la fenetre d'affichage
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
    updateIR(data);
    updateSpeed(data);
}

void MainWindow::on_Haut_clicked()
{
    //On regarde si il y a un obstable devant le robot si oui on le stop sinon on le laisse avancer
    unsigned char* tabIR = updateIR(robot.DataReceived);
    if(tabIR[0]>180 || tabIR[2]>180)
    {
        robot.Stop();
    }
    else
    {
        robot.MoveForward();
    }
}


void MainWindow::on_Droite_clicked()
{
    robot.TurnRight();
}

void MainWindow::on_Gauche_clicked()
{
    robot.TurnLeft();
}

void MainWindow::on_Bas_clicked()
{
    //On regarde si il y a un obstable derriere le robot si oui on le stop sinon on le laisse reculer
    unsigned char* tabIR = updateIR(robot.DataReceived);
    if(tabIR[1]>180 /*|| tabIR[3]>180*/)
    {
        robot.Stop();
    }
    else
    {
         robot.MoveBackward();
    }
}

void MainWindow::on_Batterie_valueChanged(QByteArray data)
{
    //on recupere la partie des donnee envoye par le robot correspondant a la batterie
    //ce que l'on recoie varie entre 0 et 255 on convertie cela en pourcentage avant de l'afficher
    unsigned char a = (unsigned char)data[2];
    float curBat = float(a)/255*100;
    ui->Batterie->setValue(curBat);
}


void MainWindow::updateSpeed(QByteArray data)
{

    float diametre = 0.135;
    long odometryL = ((long)data[8]<<24)+((long)data[7]<<16)+((long)data[6]<<8)+((long)data[5]);
    long odometryR = ((long)data[16]<<24)+((long)data[15]<<16)+((long)data[14]<<8)+((long)data[13]);


    // Affichage après une conversion
    ui->OdometryLeft->setText(QString::number(odometryL));
    ui->OdometryRight->setText(QString::number(odometryR));

    int SpeedL=(int)((data[1] << 8) + data[0]);
    int SpeedR=(int)((data[10] << 8) + data[9]);

    ui->SpeedL->display(SpeedL);
    ui->SpeedR->display(SpeedR);



}

unsigned char* MainWindow::updateIR(QByteArray data)
{
    //On recupere les donnees correspondant aux 4 capteurs Infra-Rouge
    unsigned char IRL1 = (unsigned char)data[3];
    unsigned char IRL2 = (unsigned char)data[4];
    unsigned char IRR1 = (unsigned char)data[11];
    unsigned char IRR2 = (unsigned char)data[12];

    unsigned char tabIR[4];
    tabIR[0] = IRL1;
    tabIR[1] = IRL2;
    tabIR[2] = IRR1;
    tabIR[3] = IRR2;

    if(tabIR[0]>180 || tabIR[1]>180 || tabIR[2]>180 /*|| tabIR[3]>180*/ )
    {
         robot.Stop();
    }


       //On recoie des valeurs comprises entre 30 et 180 ce qui correspont a des distances comprises entre 1m50cm et 20cm Donc on a tente de faire une conversion mais ca n'a pas marche a cause du fait que les valeurs ne soit pas lineaire
       /*float pas = 130/150;
        float dIRL1 = 20 + 130-(float(IRL1)*pas);
       float dIRL2 = 20 + float(IRL2)*pas;
       float dIRR1 = 20 + float(IRR1)*pas;
       float dIRR2 = 20 + float(IRR2)*pas;*/

       ui->L1->display(IRL1);
       ui->L2->display(IRL2);
       ui->R1->display(IRR1);
       ui->R2->display(IRR2);


    return tabIR;
}

void MainWindow::on_Connexion_clicked()
{
    robot.doConnect();
}


void MainWindow::on_Deconnexion_clicked()
{
    robot.disConnect();
}


void MainWindow::on_Stop_clicked()
{
    robot.Stop();
}
