#pragma once

#include <QWidget>
#include "ui_tspprinter.h"
#include "tsp_template.h"

class TspPrinter : public QWidget
{
	Q_OBJECT

public:
	TspPrinter(std::vector<Point2D> d, std::vector<cityID> r, QWidget *parent = nullptr);
	~TspPrinter();

protected:
	Ui::TspPrinterClass ui;

	void paintEvent(QPaintEvent* event) override;
	std::vector<Point2D> data;
	std::vector<cityID> route;
};
