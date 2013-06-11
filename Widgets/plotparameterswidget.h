#ifndef PLOTPARAMETERSWIDGET_H
#define PLOTPARAMETERSWIDGET_H

#include <QWidget>

namespace Ui {
class PlotParametersWidget;
}

class PlotParametersWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit PlotParametersWidget(int parametersNumber, QWidget *parent = 0);
    ~PlotParametersWidget();
    
private:
    Ui::PlotParametersWidget *ui;
    int _parametersNumber;

    /**
     * @brief Draws number of inputs with labels
     */
    void setupParameterInputs();
};

#endif // PLOTPARAMETERSWIDGET_H
