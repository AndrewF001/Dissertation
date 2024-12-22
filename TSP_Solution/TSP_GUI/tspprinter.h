#pragma once

#include <QWidget>
#include "ui_tspprinter.h"
#include "tsp_template.h"

class TspPrinter : public QWidget
{
	Q_OBJECT

public:
	TspPrinter(TSPVerboseResultDynamic data, QWidget *parent = nullptr);
	~TspPrinter();

protected:
	Ui::TspPrinterClass ui;

	void paintEvent(QPaintEvent* event) override;
	TSPVerboseResultDynamic data;
};
