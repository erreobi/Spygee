#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("BonoboTeam");
    QCoreApplication::setApplicationName("Spygee");

    MainWindow w;
    w.show();

    return a.exec();
}
