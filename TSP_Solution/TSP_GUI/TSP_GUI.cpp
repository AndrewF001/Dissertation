#include "TSP_GUI.h"
#include <QVBoxLayout>

TSP_GUI::TSP_GUI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

TSP_GUI::~TSP_GUI()
{}

void TSP_GUI::setData(TSPVerboseResult data) {
    printer = std::make_unique<TspPrinter>(data);
	ui.gridLayout->addWidget(printer.get());
    //ui.centralWidget->setLayout(new QVBoxLayout);
    //ui.centralWidget->layout()->addWidget(printer.get());
}