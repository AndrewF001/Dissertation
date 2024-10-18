#include "TSP_GUI.h"
#include <QtWidgets/QApplication>
#include "Runtime_TSP_Library.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TSP_GUI w;
    w.show();
    return a.exec();
}
