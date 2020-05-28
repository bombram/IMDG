#include "mainwindow.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication qAp(argc, argv);
    MainWindow w;
    w.show();
    return qAp.exec();
}
