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
}

PlotWidget::PlotWidget(PointsCollection *points) :
    PlotWidget(NULL, points)
{ }

PlotWidget::~PlotWidget()
{
    delete ui;
}

void PlotWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // move center of coordinate system to desired point
    painter.translate(this->width() >> 1, this->height() >> 1);
    // direct OY axis up
    painter.scale(1, -1);

    painter.drawPolyline(_points->getPoints().data(), _points->getPoints().size());
}
