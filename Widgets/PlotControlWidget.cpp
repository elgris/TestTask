#include "PlotControlWidget.h"
#include "ui_PlotControlWidget.h"

#include "PlotParametersWidget.h"
#include <stdexcept>

PlotControlWidget::PlotControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotControlWidget)
{
    ui->setupUi(this);
}

PlotControlWidget::PlotControlWidget(QWidget *parent, QVector<Function *> * functions) :
    QWidget(parent),
    ui(new Ui::PlotControlWidget),
    _currentParametersWidget(NULL)
{
    ui->setupUi(this);
    setFunctions(functions);
}

PlotControlWidget::~PlotControlWidget()
{
    delete ui;
    delete _functions;
}

void PlotControlWidget::setFunctions(QVector<Function *> * functions)
{
    _functions = functions;

    ui->comboBox->clear();

    for(int i = 0; i < _functions->size(); ++i) {
        ui->comboBox->addItem(_functions->at(i)->getFunctionString());
    }
}

QVector<double> PlotControlWidget::getFunctionParameters()
{
    if(_currentParametersWidget != NULL) {
        return _currentParametersWidget->getPlotParameters();
    }

    return QVector<double>();
}

Function * PlotControlWidget::getSelectedFunction()
{
    int selectedFuncIndex = getSelectedFunctionIndex();

    Function * function = NULL;

    if(selectedFuncIndex < _functions->size() && selectedFuncIndex >= 0) {
        function = _functions->at(selectedFuncIndex);
    }

    return function;
}

int PlotControlWidget::getSelectedFunctionIndex() const
{
    return ui->comboBox->currentIndex();
}

bool PlotControlWidget::setFunctionIndex(int index)
{
    if (index < 0 || index >= _functions->size()) {
        return false;
    }

    ui->comboBox->setCurrentIndex(index);
    return true;
}

void PlotControlWidget::setFunctionParameters(const QVector<double> &parameters)
{
    if(_currentParametersWidget != NULL) {
        _currentParametersWidget->setFunctionParameters(parameters);
    }
}

double PlotControlWidget::getValueFrom() const
{
    return ui->valueFrom->value();
}

double PlotControlWidget::getValueTo() const
{
    return ui->valueTo->value();
}

double PlotControlWidget::getValueStep() const
{
    return ui->valueStep->value();
}

void PlotControlWidget::setValueFrom(double value)
{
    return ui->valueFrom->setValue(value);
}

void PlotControlWidget::setValueTo(double value)
{
    return ui->valueTo->setValue(value);
}

void PlotControlWidget::setValueStep(double value)
{
    return ui->valueStep->setValue(value);
}
void PlotControlWidget::functionSelectionChanged(int index)
{
    if(_currentParametersWidget != NULL) {
        ui->plotParametersLayout->removeWidget(_currentParametersWidget);
        delete _currentParametersWidget;
    }

    _currentParametersWidget = new PlotParametersWidget(
        _functions->at(index)->getParameters().size(),
        this);

    ui->plotParametersLayout->addWidget(_currentParametersWidget);
}
