#include "mainwindow.h"
#include "wifibot.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    // Initialisations
    QApplication a(argc, argv);
    MainWindow w;
    w.robot = new Wifibot(nullptr);

    //  ----> Make all connections here <-----
    QObject::connect(w.robot, &Wifibot::readCompleted, &w, &MainWindow::updateInfos);
    // ----> End connections <-----

    // Affichage de la fenêtre
    w.show();
    return a.exec();
}

