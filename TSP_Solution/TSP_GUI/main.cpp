#include "TSP_GUI.h"
#include <QtWidgets/QApplication>
#include <memory>

#include "test_selection.h"


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    TSP_GUI w;

    auto output = TSP_Selection::menu({}, 1, false);

	if (output != nullptr)
        w.setData(output.get()->getEntries()[0]);
    else
		std::cout << "No output\n";

    w.show();
    return a.exec();
}
