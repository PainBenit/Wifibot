#include "mainwindow.h"
#include "wifibot.h"
#include <math.h>
#define SPEED_DIVISION_FACTOR .8
Wifibot::Wifibot(QObject *parent) : QObject(parent)
{
    dataL = (dataInType*) malloc(sizeof(dataInType));
    dataR = (dataInType*) malloc(sizeof(dataInType));
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0x0;
    DataToSend[3] = 0x0;
    DataToSend[4] = 0x0;
    DataToSend[5] = 0x0;
    DataToSend[6] = 0x50;
    DataToSend[7] = 0x0;
    DataToSend[8] = 0x0;

    DataReceived.resize(21);
    //Initialisation des vitesse
    setSpeed(120);

    TimerEnvoi = new QTimer();
    connect(TimerEnvoi, SIGNAL(timeout()), this, SLOT(MyTimerSlot())); //Send data to wifibot timer
    forwarding = false;
    backwarding = false;
    leftwarding = false;
    backwarding = false;
}

void Wifibot::setSpeed(int value){
    speed = value;
    if(forwarding){
        moveForward();
    }else if (backwarding) {
       moveBack();
    }else if (leftwarding) {
       moveLeft();
    }else  if (rightwarding){
        moveRight();
    }
}

void Wifibot::turn(double angle)
{
    TimerMoveTotal = new QTimer();
    TimerMoveTotal->start(50*PI_ROTATION_TIME*angle/M_PI);
    TimerMoveStep = new QTimer();
    TimerMoveTotal->start(50);
    connect(TimerMoveStep, SIGNAL(timeout()), this, SLOT(moveLeft()));
    connect(TimerMoveTotal, SIGNAL(timeout()), this, SLOT(stopMove()));
}

void Wifibot::goStraight(double distance)
{
    TimerMoveTotal = new QTimer();
    TimerMoveTotal->start(50*UNIT_MOVE_TIME*distance);
    TimerMoveStep = new QTimer();
    TimerMoveTotal->start(50);
    connect(TimerMoveStep, SIGNAL(timeout()), this, SLOT(moveForward()));
    connect(TimerMoveTotal, SIGNAL(timeout()), this, SLOT(stopMove()));
}

void Wifibot::stopMove(){
     TimerMoveStep->stop();
     TimerMoveTotal->stop();

     delete TimerMoveStep;
     delete TimerMoveTotal;
}
void Wifibot::moveForward()
{
    qDebug() << speed;
    DataToSend[2] = speed;
    DataToSend[3] = 0;
    DataToSend[4] = speed;
    DataToSend[5] = 0;
    DataToSend[6] = 80;
    forwarding = true;
    leftwarding = false;
    backwarding = false;
    rightwarding = false;

}

void Wifibot::moveBack()
{
    DataToSend[2] = speed;
    DataToSend[3] = 0;
    DataToSend[4] = speed;
    DataToSend[5] = 0;
    DataToSend[6] = 0;
    forwarding = false;
    leftwarding = false;
    backwarding = true;
    rightwarding = false;
}

void Wifibot::moveRight()
{
    DataToSend[2] = speed;
    DataToSend[3] = 0;
    DataToSend[4] = speed;
    DataToSend[5] = 0;
    DataToSend[6] = 64;
    forwarding = false;
    leftwarding = true;
    backwarding = false;
    rightwarding = false;
}

void Wifibot::move(std::vector<Vecteur> vecteurs)
{
    for(auto vecteur: vecteurs){
        move(vecteur);
    }
}

void Wifibot::move(Vecteur vecteur){
    qDebug() << "call move vector";
    turn(vecteur.angle);
    goStraight(vecteur.length);
}
void Wifibot::moveLeft()
{
    DataToSend[2] = speed;
    DataToSend[3] = 0;
    DataToSend[4] = speed;
    DataToSend[5] = 0;
    DataToSend[6] = 16;
    forwarding = false;
    leftwarding = false;
    backwarding = false;
    rightwarding = true;
}

void Wifibot::doConnect(QString ipAddress, quint16 port)
{
    socket = new QTcpSocket(this); // socket creation
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    qDebug() << "connecting...";            // this is not blocking call
    socket->connectToHost(ipAddress, port); // connection to wifibot
    // we need to wait...
    if (!socket->waitForConnected(5000))
    {
        qDebug() << "Error: " << socket->errorString();
        return;
    }
    TimerEnvoi->start(75);


    //Test move
//    std::vector<Vecteur> vecteurs;
//    Vecteur vec1 = {0, 5};
//    Vecteur vec2 = {M_PI, 5};
//    vecteurs.push_back(vec1);
//    vecteurs.push_back(vec2);
//    move(vecteurs);
}

void Wifibot::disConnect()
{
    TimerEnvoi->stop();
    socket->close();
}

void Wifibot::connected()
{
    qDebug() << "connected...";
}

void Wifibot::disconnected()
{
    qDebug() << "disconnected...";
}

void Wifibot::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

void Wifibot::readyRead()
{
    qDebug() << "reading..."; // read the data from the socket

       DataReceived = socket->readAll();
   //DataReceived.setByteOrder (QDataStream : : LittleEndian ) ;

    dataL->SpeedFront = int(((DataReceived[1] << 8) + DataReceived[0]));

    if (dataL->SpeedFront > 32767)
        dataL->SpeedFront = dataL->SpeedFront - 65536;
    dataL->BatLevel = DataReceived[2];
    dataL->IR = DataReceived[3];
    dataL->IR2 = DataReceived[4];
    dataL->odometry = long(DataReceived[8] << 24) + long(DataReceived[7] << 16) + long(DataReceived[6] << 8) + long(DataReceived[5]);
    dataR->SpeedFront = int(DataReceived[10] << 8 + DataReceived[9]);

    if (dataR->SpeedFront > 32767)
        dataR->SpeedFront = dataR->SpeedFront - 65536;
    dataR->BatLevel = 0;
    dataR->IR = DataReceived[11];
    dataR->IR2 = DataReceived[12];
    dataR->odometry = ((((long)DataReceived[16] << 24)) + (((long)DataReceived[15] << 16)) + (((long)DataReceived[14] << 8)) + ((long)DataReceived[13]));
    dataL->Current = DataReceived[17];
    dataR->Current = DataReceived[17];
    dataL->Version = DataReceived[18];
    dataR->Version = DataReceived[18];
    qDebug() << DataReceived[0] << DataReceived[1] << DataReceived[2];
   emit readCompleted(dataL, dataR);
}

void Wifibot::MyTimerSlot()
{
    qDebug() << "Timer...";
    while (Mutex.tryLock());
    unsigned char *ptr = (unsigned char *)DataToSend.data();
    short crc = Crc16(ptr + 1, 6);
    DataToSend[7] = (char)crc;        // low byte
    DataToSend[8] = (char)(crc >> 8); // heigh byte

    socket->write(DataToSend);
    Mutex.unlock();
}
void Wifibot::readData(QByteArray *receivedData){
}

void Wifibot::sendData(QByteArray *sentData){
}

short Wifibot::Crc16(unsigned char *Adresse_tab, unsigned char Taille_max)
{
    unsigned int Crc = 0xFFFF;
    unsigned int Polynome = 0xA001;
    unsigned int CptOctet = 0;
    unsigned int CptBit = 0;
    unsigned int Parity = 0;
    Crc = 0xFFFF;
    Polynome = 0xA001;
    for (CptOctet = 0; CptOctet < Taille_max; CptOctet++)
    {
        Crc ^= *(Adresse_tab + CptOctet);
        for (CptBit = 0; CptBit <= 7; CptBit++)
        {
            Parity = Crc;
            Crc >>= 1;
            if (Parity % 2 == true)
                Crc ^= Polynome;
        }
    }
    return (Crc);
}
