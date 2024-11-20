#include "mainwindow.h"
#include "QtWidgets/QApplication"
#include "serialdatareader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
