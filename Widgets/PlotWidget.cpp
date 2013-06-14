#include "PlotWidget.h"
#include "ui_PlotWidget.h"
#include "ViewItems/PlotItem.h"
#include <QPainter>

PlotWidget::PlotWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotWidget)
{
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);

    resetPlot();
}

PlotWidget::~PlotWidget()
{
    delete ui;
}

void PlotWidget::addPoint(double x, double y)
{
//    _plotItem->addPoint(x, y);

    _plotItem->addPoint(
        normalizeXValue(x),
        normalizeYValue(y)
    );

    ui->graphicsView->update();
    ui->graphicsView->repaint();
    ui->graphicsView->invalidateScene(_plotItem->boundingRect());
}

void PlotWidget::resetPlot()
{
    QGraphicsScene * scene = ui->graphicsView->scene();
    scene->clear();

    _minX = 0;
    _minY = 0;
    _initialWidth = this->width();
    _initialHeight = this->height();
    _maxX = _initialWidth;
    _maxY = _initialHeight;

    int axisXVerticalPos = _maxY / 2;
    scene->addLine(QLineF(0, axisXVerticalPos, _maxX, axisXVerticalPos));

    int axisYHorizontalPos = _maxX / 2;
    scene->addLine(QLineF(axisYHorizontalPos, 0, axisYHorizontalPos, _maxY));

    _plotItem = new PlotItem();
    scene->addItem(_plotItem);
    updateSceneScale();
}

void PlotWidget::resizeEvent(QResizeEvent * event)
{
    updateSceneScale();

    QWidget::resizeEvent(event);
}

void PlotWidget::updateSceneScale()
{
    QGraphicsScene * scene = ui->graphicsView->scene();
    ui->graphicsView->fitInView(scene->sceneRect());
}

double PlotWidget::normalizeXValue(double value)
{
    if(_initialWidth > 0) {
        double valuePerUnit = (_maxX - _minX) / _initialWidth;
        value *= valuePerUnit;
        value += _initialWidth >> 1; // move coord to center of the plot
    }

    return value;
}

double PlotWidget::normalizeYValue(double value)
{
    if(_initialHeight > 0) {
        double valuePerUnit = (_maxY - _minY) / _initialHeight;
        value *= -valuePerUnit; // make OY coord "Cortesian"-like
        value += _initialHeight >> 1; // move coord to center of the plot
    }

    return value;
}
