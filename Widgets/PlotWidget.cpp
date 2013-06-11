#include "PlotWidget.h"
#include "ui_PlotWidget.h"
#include <QPainter>

PlotWidget::PlotWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotWidget)
{
    ui->setupUi(this);
}

PlotWidget::~PlotWidget()
{
    delete ui;
}


void PlotWidget::paintEvent(QPaintEvent * event) {
    drawAxis();
}

void PlotWidget::drawAxis() {
    QPainter painter(this);

    int axisXVerticalPos = this->height() >> 1;
    painter.drawLine(0, axisXVerticalPos, this->width(), axisXVerticalPos);

    int axisYHorizontalPos = this->width() >> 1;
    painter.drawLine(axisYHorizontalPos, 0, axisYHorizontalPos, this->height());
}
