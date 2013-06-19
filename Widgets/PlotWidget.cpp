#include "PlotWidget.h"
#include "ui_PlotWidget.h"
#include "../Models/PointsCollection.h"
#include <QPainter>
#include <QDragEnterEvent>

PlotWidget::PlotWidget(QWidget *parent, PointsCollection *points) :
    QWidget(parent),
    ui(new Ui::PlotWidget),
    _points(points)
{
    ui->setupUi(this);

    // redraw the plot on points collection change
    connect(points, SIGNAL(collectionChanged()), this, SLOT(update()));
    connect(ui->valueXCenter, SIGNAL(valueChanged(double)), this, SLOT(update()));
    connect(ui->valueYCenter, SIGNAL(valueChanged(double)), this, SLOT(update()));

    ui->valueXCenter->setValue(this->width() >> 1);
    ui->valueYCenter->setValue(this->height() >> 1);
}

PlotWidget::~PlotWidget()
{
    delete ui;
}

void PlotWidget::centerCoordinatesClicked()
{
    int pointsNumber = _points->getPoints().size();

    if(pointsNumber > 0) {
        QPointF middlePoint = _points->getPoints().at(pointsNumber >> 1);
        int xCenter = (this->width() >> 1) - middlePoint.x();
        int yCenter = (this->height() >> 1) - middlePoint.y();
        ui->valueXCenter->setValue(xCenter);
        ui->valueYCenter->setValue(yCenter);
    }
}

void PlotWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QColor(0,0,0));

    // move center of coordinate system to desired point
    painter.translate(ui->valueXCenter->value(), ui->valueYCenter->value());
    // direct OY axis up
    painter.scale(1, -1);

    painter.drawPolyline(_points->getPoints().data(), _points->getPoints().size());
}
