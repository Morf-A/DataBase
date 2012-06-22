#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   MainWindow w;
   w.resize(1300,450);
   w.show();


    return a.exec();
}
