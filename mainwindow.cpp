#include "mainwindow.h"
#include "wifibot.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi((QMainWindow *)this);
    Camera = new QNetworkAccessManager();
}

void MainWindow::updateInfos(dataInType* dataL, dataInType* dataR){
    updateBatteryLevel();
    updateSpeedLabel();
    updateIRSensorLabel();
    updateCurrentLabel();
    updateOdomeryLabel();

}

void MainWindow::updateBatteryLevel(){
    QString danger = "QProgressBar::chunk {background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #FF0350,stop: 0.4999 #FF0020,stop: 0.5 #FF0019,stop: 1 #FF0000 );border-bottom-right-radius: 5px;border-bottom-left-radius: 5px;border: .px solid black;}";
    QString safe= "QProgressBar::chunk {background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #78d,stop: 0.4999 #46a,stop: 0.5 #45a,stop: 1 #238 );border-bottom-right-radius: 7px;border-bottom-left-radius: 7px;border: 1px solid black;}";

    ui->progressBar->setValue( robot->dataL->BatLevel*0.1*100/12.7);

        if (ui->progressBar->value() < 25)
             ui->progressBar->setStyleSheet(danger);
        else {
             ui->progressBar->setStyleSheet(safe);
    }


}

void MainWindow::updateSendTest(){
    updateSentLabel("Bonjour");
}
void MainWindow::updateSpeedLabel(){


    //Changing QLCDNumber speedLeft color
    int speedL = robot->dataL->SpeedFront/100;
    ui->speedLeft->display(speedL);
        if (speedL >70 && speedL <100){

             ui->speedLeft->setStyleSheet("background-color: yellow;  color: white;");

        }else if(speedL >100){

             ui->speedLeft->setStyleSheet("background-color: red; color: white;");
        }else {

             ui->speedLeft->setStyleSheet("background-color: black; color: white;");
        }

    //Change QLCDNumber speedRight color
     int speedR = robot->dataR->SpeedFront/100;
    ui->speedRight->display(speedR);
        if (speedR > 70 && speedR < 100){

             ui->speedRight->setStyleSheet("background-color: orange; color: white;");

        }else if(speedR >100){

             ui->speedRight->setStyleSheet("background-color: orange; color: white;");
        }else {

             ui->speedRight->setStyleSheet("background-color: black; color: white;");
        }
}

void MainWindow::updateIRSensorLabel(){


     //IR1 sensor left side
     int IR1L =robot->dataL->IR*3.3/255;
    ui->IRS1Left->display(IR1L);

            if (IR1L >=1){

                 ui->IRS1Left->setStyleSheet("background-color: red; color: white;");

            }else {

                 ui->IRS1Left->setStyleSheet("background-color: black; color: white;");
            }
    //IR1 sensor Right side
        int IR1R = robot->dataL->IR*3.3/255;
        ui->IRS1Right->display(IR1R);
            if (IR1R >=1 ){

                 ui->IRS1Right->setStyleSheet("background-color: red; color: white;");

            }else {

                 ui->IRS1Right->setStyleSheet("background-color: black; color: white;");
            }

   //IR2 sensor left side
        int IR2L = robot->dataL->IR2*3.3/255;

      ui->IRS2Left->display(IR2L);
        if (IR2L >= 1 ){

             ui->IRS2Left->setStyleSheet("background-color: red; color: white;");
        }else {

             ui->IRS2Left->setStyleSheet("background-color: black; color: white;");
        }


    //IR2 sensor left side
    int IR2R= robot->dataR->IR2*3.3/255;

    ui->IRS2Right->display(IR2R);
        if (IR2R>=1){

             ui->IRS2Right->setStyleSheet("background-color: red; color: white;");
        }else {

             ui->IRS2Right->setStyleSheet("background-color: black; color: white;");
        }

}

void MainWindow::updateOdomeryLabel(){

    int odometryL=robot->dataL->odometry/400;
    ui->odometryLeft->display(odometryL);
        if (odometryL >100){

             ui->odometryLeft->setStyleSheet("background-color: red; color: white;");

        }else {

             ui->odometryLeft->setStyleSheet("background-color: black; color: white;");
        }


        int odometryR=robot->dataR->odometry/400;

        ui->odometryRight->display(odometryR);

            if ( odometryR >100){

                 ui->odometryRight->setStyleSheet("background-color: red; color: white;");
            }else {

                 ui->odometryRight->setStyleSheet("background-color: black; color: white;");
            }

}


void MainWindow::updateCurrentLabel(){

 //   to do
            //change the control based on value to control baset on sensors !!!!!!!!!!!!!!!!!!!!!!!!!
    int currentL =robot->dataL->Current/10;
    ui->CurrentLeft->display(currentL);

        if (currentL > 1 && currentL <5){

             ui->CurrentLeft->setStyleSheet("background-color: orange; color: white;");

        }else if(currentL > 5 ){

             ui->CurrentLeft->setStyleSheet("background-color: red; color: white;");
        }else {

             ui->CurrentLeft->setStyleSheet("background-color: black; color: white;");
        }

    double currentR= robot->dataR->Current/10;
    ui->CurrentRight->display(currentR);

      if (currentR >1 && currentR < 5){

        ui->CurrentRight->setStyleSheet("background-color: orange; color: white;");

      }else if(currentR >5){

         ui->CurrentRight->setStyleSheet("background-color: red; color: white;");
    }else {

         ui->CurrentRight->setStyleSheet("background-color: black; color: white;");
    }

}

void MainWindow::updateReceivedTest(){
    updateReceivedLabel("Bonjour reçu");
}
void MainWindow::updateSentTrame(QByteArray* sentData){
    QString bytesText = QString::fromStdString(sentData->toStdString()) ;
    updateSentLabel(bytesText);
    qDebug() << bytesText;
}
void MainWindow::updateReceivedTrame(QByteArray* receivedData){
    QString bytesText = QString::fromStdString(receivedData->toStdString());
    updateReceivedLabel(bytesText);
    qDebug() << bytesText;
}


void MainWindow::updateSentLabel(QString newText){
    //ui->sent->setText(newText);
}
void MainWindow::updateReceivedLabel(QString newText){
    //ui->received->setText(newText);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_upBoutton_clicked()
{
    qDebug() << "Move forward";
    robot->moveForward();
}


void MainWindow::on_rightBoutton_clicked()
{
    robot->moveRight();
}

void MainWindow::on_LeftBoutton_clicked()
{
    robot->moveLeft();
}

void MainWindow::on_connectBoutton_clicked()
{
    robot->doConnect(ui->ipAddressEdit->text(),15020);
}

void MainWindow::on_disconnectBoutton_clicked()
{
    robot->disConnect();
}

void MainWindow::on_downBouton_clicked()
{
    robot->moveBack();
}

void MainWindow::on_speedSlider_valueChanged(int value)
{
    robot->setSpeed(value);
}


void MainWindow::on_pushButton5_clicked(){
    this->Camera->get(QNetworkRequest(QUrl("http://"+ui->ipAddressEdit->text()+":8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-200")));
}

void MainWindow::on_pushButton4_clicked(){
    this->Camera->get(QNetworkRequest(QUrl("http://"+ui->ipAddressEdit->text()+":8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=200")));
}

void MainWindow::on_pushButton2_clicked(){
    this->Camera->get(QNetworkRequest(QUrl("http://"+ui->ipAddressEdit->text()+":8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=200")));
}
void MainWindow::on_pushButton3_clicked(){
    this->Camera->get(QNetworkRequest(QUrl("http://"+ui->ipAddressEdit->text()+":8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-200")));
}

void MainWindow::video(){
    this->view = new QWebEngineView();
    //this->view->setLayout(ui->vLayout);
    this->view->load(QUrl("http://"+ui->ipAddressEdit->text()+":8080/?action=stream"));
    this->view->show();
    this->Camera->get(QNetworkRequest(QUrl("http://192.168.1.11:8080/?action=command&dest=0&plugin=0&id=10094855&group=1&value=1")));
    this->view->show();
}

void MainWindow::screenshot(){
    QPixmap capt =QPixmap();
    capt = QPixmap::grabWidget(this->view);
    QString format = "png";
    QString initialPath = QDir::currentPath() + tr("/sans_nom.") + format;

        QString name = QFileDialog::getSaveFileName((QWidget*)this, tr("Save As"),
                                   initialPath,
                                   tr("%1 Files (*.%2);;All Files (*)")
                                   .arg(format.toUpper())
                                   .arg(format));
        if (!name.isEmpty()){
            capt.save(name, format.toUtf8());
        }
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if( event->key() == Qt::Key_Z){
        on_upBoutton_clicked();
    }
    if( event->key() == Qt::Key_Q){
        on_LeftBoutton_clicked();
    }
    if( event->key() == Qt::Key_D){
        on_rightBoutton_clicked();
    }
    if( event->key() == Qt::Key_S){
        on_downBouton_clicked();
    }
    if( event->key() == Qt::Key_O){
        on_pushButton5_clicked();
    }
    if( event->key() == Qt::Key_K){
        on_pushButton2_clicked();
    }
    if( event->key() == Qt::Key_L){
        on_pushButton4_clicked();
    }
    if( event->key() == Qt::Key_M){
        on_pushButton3_clicked();
    }
    if( event->key() == Qt::Key_X){
        video();
    }
    if( event->key() == Qt::Key_C){
        screenshot();
    }
}




void MainWindow::on_screenShotBouton_clicked()
{
    screenshot();
}

void MainWindow::on_pushButton_clicked()
{
    ui->speedSlider->setValue(0);
}

void MainWindow::on_radioButton_clicked()
{
    video();
}
