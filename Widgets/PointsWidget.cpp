#include "PointsWidget.h"
#include "ui_PointsWidget.h"
#include "../Models/PointsCollection.h"
#include "math.h"

PointsWidget::PointsWidget(QWidget *parent, PointsCollection *_points) :
    QWidget(parent),
    ui(new Ui::PointsWidget),
    _perPage(100),
    _pageNumber()
{
    ui->setupUi(this);
    ui->buttonPreviousPage->setEnabled(false);
    ui->buttonNextPage->setEnabled(false);
}

PointsWidget::~PointsWidget()
{
    delete ui;
}

void PointsWidget::previousPageClicked()
{
    if(_pageNumber > 0) {
        _pageNumber--;
    }

    updatePreviousPageButton();
}

void PointsWidget::nextPageClicked()
{
    if(_pageNumber < getPagesNumber()) {
        _pageNumber++;
    }

    updateNextPageButton();
}

void PointsWidget::showEvent(QShowEvent * event)
{
    QWidget::showEvent(event);
    updatePage();
}

void PointsWidget::updatePage()
{
    ui->tableWidget->clear();

    int pages = getPagesNumber();
    if (_pageNumber > pages) {
        _pageNumber = pages;
    }

    int startPointNumber = _pageNumber * _perPage;
    int rowCount = _points->getPoints().size() - startPointNumber;

     ui->tableWidget->setRowCount(rowCount);


    for(int i = 0; i < rowCount; ++i) {
        int pointIndex = startPointNumber + i;
        QPointF point = _points->getPoints().at(pointIndex);

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(pointIndex + 1)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(point.x())));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(point.y())));
    }
}

void PointsWidget::updatePreviousPageButton()
{
    int pages = getPagesNumber();

    if(_pageNumber == 0) {
        ui->buttonPreviousPage->setEnabled(false);
        ui->buttonPreviousPage->setText(QString("Previous (%0)").arg(pages));
    } else {
        ui->buttonPreviousPage->setEnabled(true);
        ui->buttonPreviousPage->setText(QString("Previous (%0 / %1)").arg(_pageNumber - 1, pages));
    }
}

void PointsWidget::updateNextPageButton()
{
    int pages = getPagesNumber();

    if(_pageNumber == pages) {
        ui->buttonNextPage->setEnabled(false);
        ui->buttonNextPage->setText(QString("Next (%0)").arg(pages));
    } else {
        ui->buttonNextPage->setEnabled(true);
        ui->buttonNextPage->setText(QString("Next (%0 / %1)").arg(_pageNumber + 1, pages));
    }
}

int PointsWidget::getPagesNumber()
{
    QVector<QPointF> points = _points->getPoints();
    return _perPage == 0
            ? 0
            : ceil(_points->getPoints().size() / _perPage);
}

