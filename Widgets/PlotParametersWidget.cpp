#include "PlotParametersWidget.h"
#include "ui_PlotParametersWidget.h"
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QSpacerItem>

PlotParametersWidget::PlotParametersWidget(int parametersNumber, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotParametersWidget),
    _parametersNumber(parametersNumber)
{
    ui->setupUi(this);
    setupParameterInputs();
    ui->verticalLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

PlotParametersWidget::~PlotParametersWidget()
{
    delete ui;
}

QVector<double> PlotParametersWidget::getPlotParameters() const
{
    QVector<double> params;

    for(int i = 0; i < ui->formLayout->rowCount(); ++i) {
        QDoubleSpinBox * input = (QDoubleSpinBox *)(ui->formLayout->itemAt(i, QFormLayout::FieldRole)->widget());
        params.append(input->value());
    }

    return params;
}

void PlotParametersWidget::setFunctionParameters(const QVector<double> &parameters)
{
    for(int i = 0;
        (i < ui->formLayout->rowCount()) && (i < parameters.size());
        ++i) {
        QDoubleSpinBox * input = (QDoubleSpinBox *)(ui->formLayout->itemAt(i, QFormLayout::FieldRole)->widget());
        input->setValue(parameters.at(i));
    }
}

void PlotParametersWidget::setupParameterInputs()
{
    for(int i = 0; i < _parametersNumber; ++i) {
        QLabel * label = new QLabel(this);
        label->setText(QChar('A' + i));
        label->setLayoutDirection(Qt::LeftToRight);
        ui->formLayout->setWidget(i, QFormLayout::LabelRole, label);

        QDoubleSpinBox * input = new QDoubleSpinBox(this);
        input->setMinimum(-100);
        input->setMaximum(100);
        input->setSingleStep(0.1);
        ui->formLayout->setWidget(i, QFormLayout::FieldRole, input);
    }
}
