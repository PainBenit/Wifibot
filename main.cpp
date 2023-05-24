
#include "myrobot.h"
#include "myrobot.cpp"
#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    w.show();
    w.initialise();
    return a.exec();
}
