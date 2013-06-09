#include "plotparameterswidget.h"
#include "ui_plotparameterswidget.h"

PlotParametersWidget::PlotParametersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotParametersWidget)
{
    ui->setupUi(this);
}

PlotParametersWidget::~PlotParametersWidget()
{
    delete ui;
}
