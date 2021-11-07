//Title: Chat Client over TCP SOCKET
//Project aim: learning Qt
//by: SajadSojoudi@gmail.com

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
