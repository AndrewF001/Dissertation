#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TSP_GUI.h"

class TSP_GUI : public QMainWindow
{
    Q_OBJECT

public:
    TSP_GUI(QWidget *parent = nullptr);
    ~TSP_GUI();

private:
    Ui::TSP_GUIClass ui;
};
