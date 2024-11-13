#include "tspprinter.h"
#include <QPainter>

TspPrinter::TspPrinter(std::vector<Point2D> d, std::vector<cityID> r, QWidget* parent)
	: data(d), route(r), QWidget(parent)
{
	ui.setupUi(this);
}

TspPrinter::~TspPrinter()
{}

void TspPrinter::paintEvent(QPaintEvent * event) {
    Q_UNUSED(event);

    QPainter painter(this);

    // Draw the border, fix later
    painter.drawLine(1, 1, width(), 1);
    painter.drawLine(1, 1, 1, height());
    painter.drawLine(1, height() - 1, width(), height() - 1);
    painter.drawLine(width() - 1, 1, width() - 1, height());

    // Scale factor
    double scalex = static_cast<double>(100000) / width();
    double scaley = static_cast<double>(100000) / height();

    // Draw the lines
    painter.setPen(QPen(Qt::black, 2));
    for (size_t i = 0; i < route.size() - 1; i++) {
        painter.drawLine(data[route[i]].x / scalex, data[route[i]].y / scaley, data[route[i + 1]].x / scalex, data[route[i + 1]].y / scaley);
    }

    // Draw the points
    painter.setPen(QPen(Qt::red, 3));
    for (int i = 0; i < data.size(); i++) {
        painter.drawPoint(data[i].x / scalex, data[i].y / scaley);
    }

    painter.setPen(QPen(Qt::black, 1));
    painter.setFont(QFont("Arial", 10));
    //painter.drawText(rect(), Qt::AlignCenter, QString::fromStdString(name))

}
