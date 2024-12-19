#include "tspprinter.h"
#include <QPainter>

TspPrinter::TspPrinter(TSPVerboseResult data, QWidget* parent)
	: data(data), QWidget(parent)
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
    double scalex = (data.area.width()) / (width() - 2);
    double scaley = data.area.height() / (height() - 2);

    // Draw the lines
    painter.setPen(QPen(Qt::black, 2));
    for (size_t i = 0; i < data.route.size() - 1; i++) {
        painter.drawLine(data.node_coord_section[data.route[i]].m_x / scalex, data.node_coord_section[data.route[i]].m_y / scaley, data.node_coord_section[data.route[i+1]].m_x / scalex, data.node_coord_section[data.route[i+1]].m_y / scaley);
    }

    // Draw the points
    painter.setPen(QPen(Qt::red, 3));
    for (int i = 0; i < data.node_coord_section.size(); i++) {
        painter.drawPoint(data.node_coord_section[i].m_x / scalex, data.node_coord_section[i].m_y / scaley);
    }

    painter.setPen(QPen(Qt::black, 1));
    painter.setFont(QFont("Arial", 10));
    //painter.drawText(rect(), Qt::AlignCenter, QString::fromStdString(name))

}
