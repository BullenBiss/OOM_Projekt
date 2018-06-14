
#include "mainwindow.h"
#include "game.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    game g;
    g.initiate();
    g.gameUpdate();
    return a.exec();
}
