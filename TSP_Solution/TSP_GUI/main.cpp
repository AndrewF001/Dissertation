#include "TSP_GUI.h"
#include <QtWidgets/QApplication>
#include "tsp_library_realtime.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TSP_GUI w;
    w.show();
    return a.exec();
}
