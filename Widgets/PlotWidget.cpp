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

    _plotItem = new PlotItem();
    ui->graphicsView->setScene(scene);
    scene->addItem(_plotItem);

    drawAxis();
    updateSceneScale();
}

PlotWidget::~PlotWidget()
{
    delete ui;
}

void PlotWidget::addPoint(double x, double y)
{
    _plotItem->addPoint(x, y);
    update();
}

void PlotWidget::resizeEvent(QResizeEvent * event)
{
    updateSceneScale();

    QWidget::resizeEvent(event);
}

void PlotWidget::drawAxis()
{
    QGraphicsScene * scene = ui->graphicsView->scene();

    int axisXVerticalPos = this->height() >> 1;
    scene->addLine(QLineF(0, axisXVerticalPos, this->width(), axisXVerticalPos));

    int axisYHorizontalPos = this->width() >> 1;
    scene->addLine(QLineF(axisYHorizontalPos, 0, axisYHorizontalPos, this->height()));
}

void PlotWidget::updateSceneScale()
{
    QGraphicsScene * scene = ui->graphicsView->scene();
    ui->graphicsView->fitInView(scene->sceneRect());
}
