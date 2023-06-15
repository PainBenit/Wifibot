
#include "myrobot.h"
#include "myrobot.cpp"
#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    //creation d'un objet QApplication et d'un objet MainWindow
    QApplication a(argc, argv);
    MainWindow w;


    //affichage de la fenetre
    w.show();
    w.initialise();

    return a.exec();
}
