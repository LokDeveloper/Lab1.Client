#include "mainwindow.h"
#include "secondwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow();
    //secondWindow *s = new secondWindow();
    //s->show();
    w->show();

    return a.exec();
}
