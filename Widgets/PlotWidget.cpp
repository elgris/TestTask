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
    y = -y;
    if(_maxY < y) {
        _maxY = y;
    }
    if(_minY > y) {
        _minY = y;
    }

    _plotItem->addPoint(x, y);
    updateSceneRect();
    updateSceneScale();

}

void PlotWidget::resetPlot()
{
    QGraphicsScene * scene = ui->graphicsView->scene();
    scene->clear();

    _minY = 0;
    _maxY = 0;

    updateSceneRect();


//    int axisXVerticalPos = _maxY / 2;
//    scene->addLine(QLineF(_minX, 0, _maxX, 0));

//    int axisYHorizontalPos = _maxX / 2;
//    scene->addLine(QLineF(0, 0, 0, _maxY));

    _plotItem = new PlotItem();
    scene->addItem(_plotItem);
    updateSceneScale();
}

void PlotWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(ui->graphicsView);
    painter.drawLine(QLineF(_minX, 0, _maxX, 0));
    painter.drawLine(QLineF(0, _minY, 0, _maxY));
}

void PlotWidget::updateSceneRect()
{
    double rectWidth = _maxX - _minX;
    double rectHeight = _maxY - _minY;
    double sceneX = _minX - PlotWidget::WINDOW_GAP * rectWidth;
    double sceneY = _minY - PlotWidget::WINDOW_GAP * rectHeight;
    double sceneWidth = (1 + PlotWidget::WINDOW_GAP) * rectWidth;
    double sceneHeight = (1 + PlotWidget::WINDOW_GAP) * rectHeight;

    ui->graphicsView->scene()->setSceneRect(sceneX, sceneY, sceneWidth, sceneHeight);
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
    scene->update();
}
