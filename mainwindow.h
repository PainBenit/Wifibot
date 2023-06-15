#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "wifibot.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateSentLabel(QString newText);
    void updateReceivedLabel(QString newText);
    Wifibot *robot;
    QNetworkAccessManager *Camera;
    QWebEngineView  *view;
    void video();
    void screenshot();
    void keyPressEvent(QKeyEvent *event);


    void updateBatteryLevel();
    void updateIRSensorLabel();
    void updateSpeedLabel();
    void updateCurrentLabel();
    void updateOdomeryLabel();
public slots:
    void updateSendTest();
    void updateReceivedTest();
    void updateSentTrame(QByteArray *sentData);
    void updateReceivedTrame(QByteArray *receivedData);

    void updateInfos(dataInType* dataL, dataInType* dataR);
private slots:
    void on_upBoutton_clicked();

    void on_rightBoutton_clicked();

    void on_LeftBoutton_clicked();

    void on_connectBoutton_clicked();

    void on_disconnectBoutton_clicked();

    void on_downBouton_clicked();

    void on_speedSlider_valueChanged(int value);

    void on_pushButton3_clicked();

    void on_pushButton2_clicked();

    void on_pushButton4_clicked();

    void on_pushButton5_clicked();

    void on_screenShotBouton_clicked();

    void on_pushButton_clicked();

    void on_radioButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
