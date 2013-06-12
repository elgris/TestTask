#include "PlotControlWidget.h"
#include "ui_plotcontrolwidget.h"

#include "Models/Logarithmic.h"
#include "Models/Inverse.h"
#include "Models/Quadratic.h"
#include "Models/Trigonometric.h"
#include "PlotParametersWidget.h"

PlotControlWidget::PlotControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotControlWidget)
{
    ui->setupUi(this);
    _functions = new QVector<Function *>();

    loadFunctions();
}

PlotControlWidget::~PlotControlWidget()
{
    delete ui;
    delete _functions;
}

void PlotControlWidget::functionSelectionChanged(int index) {
    while (QLayoutItem* item = ui->plotParametersLayout->takeAt(0))
    {
        if (QWidget* widget = item->widget())
            delete widget;
        delete item;
    }
    ui->plotParametersLayout->addWidget(
                new PlotParametersWidget(
                    _functions->at(index)->getParameters().size(),
                    this
                    )
                );
}

void PlotControlWidget::loadFunctions()
{
    _functions->append(new Quadratic());
    _functions->append(new Trigonometric());
    _functions->append(new Logarithmic());
    _functions->append(new Inverse());

    addFunctionsToCombobox();
}

void PlotControlWidget::addFunctionsToCombobox()
{
    for(int i = 0; i < _functions->size(); ++i) {
        ui->comboBox->addItem(_functions->at(i)->getFunctionString());

    }
}

