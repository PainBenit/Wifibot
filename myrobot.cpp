// myrobot.cpp

#include "myrobot.h"
#include <QApplication>

MyRobot::MyRobot(QObject *parent) : QObject(parent) {
    DataToSend.resize(9);
    DataToSend[0] = 255;
    DataToSend[1] = 0x07;
    DataToSend[2] = 120;
    DataToSend[3] = 0;
    DataToSend[4] = 120;
    DataToSend[5] = 0;
    DataToSend[6] = 80;
    DataToSend[7] = 0x0;
    DataToSend[8] = 0x0;
    DataReceived.resize(21);
    TimerEnvoi = new QTimer();
    connect(TimerEnvoi, SIGNAL(timeout()), this, SLOT(MyTimerSlot())); //Send data to wifibot timer
}


void MyRobot::doConnect() {
    socket = new QTcpSocket(this); // socket creation
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    qDebug() << "connecting..."; // this is not blocking call
    //socket->connectToHost("LOCALHOST", 15020);

    //socket->connectToHost("192.168.10.1", 5001); //connection au simulateur port a changer

    socket->connectToHost("192.168.1.106", 15020);// connection au wifibot
    if(!socket->waitForConnected(5000)) {
        qDebug() << "Error: " << socket->errorString();
        return;
    }
    TimerEnvoi->start(75);

}

void MyRobot::disConnect() {
    TimerEnvoi->stop();
    socket->close();
}

void MyRobot::connected() {
    qDebug() << "connected..."; // Hey server, tell me about you.
}

void MyRobot::disconnected() {
    qDebug() << "disconnected...";
}

void MyRobot::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}

void MyRobot::readyRead() {
    qDebug() << "reading..."; // read the data from the socket
    DataReceived = socket->readAll();
    emit updateUI(DataReceived);
}

void MyRobot::MyTimerSlot() {
    qDebug() << "Timer...";
    while(Mutex.tryLock());
    socket->write(DataToSend);
    Mutex.unlock();
}

void MyRobot::MoveForward()
{
    //On envoie les instructions pour que le robot avance le 1er octet est toujours 255 et le 2eme est la taille du message
    //Les 2 suivant servent a definir la vitesse des roues gauches et les 2 encore suivant servent a definir la vitesse des roues droites
    //Le 7eme octet sert a definir le sens des roues
    //Les octets 8 et 9 servent au CRC
    DataToSend[0] = 255;
    DataToSend[1] = 0x07;
    DataToSend[2] = 120;
    DataToSend[3] = 0;
    DataToSend[4] = 120;
    DataToSend[5] = 0;
    DataToSend[6] = 80;
    short crc = Crc16();
    DataToSend[7] = crc & 0xff;
    DataToSend[8] = (crc >> 8) & 0xff;
    DataReceived.resize(21);

}

void MyRobot::TurnRight() {

    DataToSend[0] = 255;
    DataToSend[1] = 0x07;
    DataToSend[2] = 120;
    DataToSend[3] = 0;
    DataToSend[4] = 120;
    DataToSend[5] = 0;
    DataToSend[6] = 64;
    short crc = Crc16();
    DataToSend[7] = crc & 0xff;
    DataToSend[8] = (crc >> 8) & 0xff;
    DataReceived.resize(21);
}

void MyRobot::TurnLeft() {

    DataToSend[0] = 255;
    DataToSend[1] = 0x07;
    DataToSend[2] = 120;
    DataToSend[3] = 0;
    DataToSend[4] = 120;
    DataToSend[5] = 0;
    DataToSend[6] = 16;
    short crc = Crc16();
    DataToSend[7] = crc & 0xff;
    DataToSend[8] = (crc >> 8) & 0xff;
    DataReceived.resize(21);
}

void MyRobot::MoveBackward() {

    DataToSend[0] = 255;
    DataToSend[1] = 0x07;
    DataToSend[2] = 120;
    DataToSend[3] = 0;
    DataToSend[4] = 120;
    DataToSend[5] = 0;
    DataToSend[6] = 0;
    short crc = Crc16();
    DataToSend[7] = crc & 0xff;
    DataToSend[8] = (crc >> 8) & 0xff;
    DataReceived.resize(21);
}


void MyRobot::Stop() {

    DataToSend[0] = 255;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0;
    DataToSend[3] = 0;
    DataToSend[4] = 0;
    DataToSend[5] = 0;
    DataToSend[6] = 0;
    short crc = Crc16();
    DataToSend[7] = crc & 0xff;
    DataToSend[8] = (crc >> 8) & 0xff;
    DataReceived.resize(21);
}



short MyRobot::Crc16()
{  unsigned int Crc = 0xFFFF;
    unsigned int Polynome = 0xA001;
    unsigned int CptOctet = 0;
    unsigned int CptBit = 0;
    unsigned int Parity= 0;

    Crc = 0xFFFF;
    Polynome = 0xA001;
    for ( CptOctet= 1 ; CptOctet < 7 ; CptOctet++)
    {   Crc ^= DataToSend[CptOctet];

        for ( CptBit = 0; CptBit <= 7 ; CptBit++)
            {    Parity= Crc;
                Crc >>= 1;
                if (Parity%2 == true)
                    Crc ^= Polynome;
            }
    }
   return(Crc);
}

