#include "PointsWidget.h"
#include "ui_PointsWidget.h"

PointsWidget::PointsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PointsWidget)
{
    ui->setupUi(this);
}

PointsWidget::~PointsWidget()
{
    delete ui;
}

void PointsWidget::previousPageClicked()
{
}

void PointsWidget::nextPageClicked()
{
}

