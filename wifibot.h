#ifndef WIFIBOT_H
#define WIFIBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>
#include <QString>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QNetworkAccessManager>
#include <QWebEngineView>
#include <QKeyEvent>
#include <QFileDialog>
#include <vector>

#define PI_ROTATION_TIME 2
#define UNIT_MOVE_TIME 4

typedef struct Vecteur{
    double angle;
    double length;
}vecteur;
typedef struct dataInType{
    int SpeedFront;
    qint8 BatLevel;
    int IR;
    int IR2;
    double odometry;
    int Current;
    int Version;
}dataInType;

class Wifibot : public QObject {
    Q_OBJECT
public:
    dataInType *dataL, *dataR;

    explicit Wifibot(QObject *parent = nullptr);
    void doConnect(QString ipAddress, quint16 port);
    void disConnect();
    QByteArray DataToSend;
    QByteArray DataReceived;
    QMutex Mutex;
    short Crc16(unsigned char *Adresse_tab, unsigned char Taille_max);
    void moveBack();


signals:
    void readCompleted(dataInType* dataL, dataInType* dataR);
    void speedChange(int speed);
public slots :
    void connected();
    void readyRead();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void MyTimerSlot();
    void readData(QByteArray *receivedData);
    void sendData(QByteArray *sendData);
    void moveLeft();
    void moveForward();
    void moveRight();
    void move(std::vector<Vecteur> vecteurs);
    void move(Vecteur vecteur);
    void setSpeed(int speed);
    void turn(double angle);
    void goStraight(double distance);
    void stopMove();
private:
    QTcpSocket *socket;
    QTimer *TimerEnvoi;
    QTimer* TimerMoveTotal;
    QTimer* TimerMoveStep;
    int speed;
    bool forwarding;
    bool backwarding;
    bool leftwarding;
    bool rightwarding;
};

#endif // WIFIBOT_H
