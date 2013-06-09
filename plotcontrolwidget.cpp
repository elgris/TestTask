#include "plotcontrolwidget.h"
#include "ui_plotcontrolwidget.h"

PlotControlWidget::PlotControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotControlWidget)
{
    ui->setupUi(this);
}

PlotControlWidget::~PlotControlWidget()
{
    delete ui;
}
