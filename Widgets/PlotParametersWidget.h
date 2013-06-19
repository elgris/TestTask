#ifndef PLOTPARAMETERSWIDGET_H
#define PLOTPARAMETERSWIDGET_H

#include <QWidget>
#include <QVector>

namespace Ui {
class PlotParametersWidget;
}

/**
 * @brief Widget for setting polt parameters.
 * Perform dynamic generation of input fields
 * (dependending on number of function's arguments)
 */
class PlotParametersWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit PlotParametersWidget(int parametersNumber, QWidget *parent = 0);
    ~PlotParametersWidget();

    /**
     * @brief Returns current parameters
     * @return
     */
    QVector<double> getPlotParameters() const;

    /**
     * @brief Set parameter values into inputs
     * @param parameters
     */
    void setFunctionParameters(const QVector<double> & parameters);
    
private:
    Ui::PlotParametersWidget *ui;
    int _parametersNumber;

    /**
     * @brief Draws number of inputs with labels
     */
    void setupParameterInputs();
};

#endif // PLOTPARAMETERSWIDGET_H
