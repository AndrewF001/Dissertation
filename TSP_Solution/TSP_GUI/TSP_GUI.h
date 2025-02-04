#pragma once

#include <memory>
#include <QtWidgets/QMainWindow>
#include "ui_TSP_GUI.h"
#include "tspprinter.h"

class TSP_GUI : public QMainWindow
{
    Q_OBJECT

public:
    TSP_GUI(QWidget *parent = nullptr);
    ~TSP_GUI();
    void setData(const std::vector<TSPVerboseResultDynamic>& data);

private:
    Ui::TSP_GUIClass ui;
	std::vector<std::unique_ptr<TspPrinter>> m_printers;
};
