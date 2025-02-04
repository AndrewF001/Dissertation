#include "TSP_GUI.h"
#include <QVBoxLayout>

TSP_GUI::TSP_GUI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

TSP_GUI::~TSP_GUI()
{}

void TSP_GUI::setData(const std::vector<TSPVerboseResultDynamic>& data) {
    int size = static_cast<int>(std::sqrt(data.size()) + 0.5);
    int i = 0;

    for (const auto& d : data) {
        auto div = std::div(i++, size);
        auto printer = std::make_unique<TspPrinter>(d);
        ui.gridLayout->addWidget(printer.get(), div.quot, div.rem);
        m_printers.push_back(std::move(printer));
    }
}