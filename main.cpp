#include "secondwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    secondWindow *s = new secondWindow();
    s->show();


    return a.exec();
}
