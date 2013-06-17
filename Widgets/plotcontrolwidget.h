#ifndef PLOTCONTROLWIDGET_H
#define PLOTCONTROLWIDGET_H

#include <QWidget>
#include <QVector>
#include "Models/Function.h"
namespace Ui {
class PlotControlWidget;
}

class PlotParametersWidget;

class PlotControlWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit PlotControlWidget(QWidget *parent = 0);
    explicit PlotControlWidget(QWidget *parent, QVector<Function *> * functions);
    ~PlotControlWidget();

    /**
     * @brief Set functions to the widget for further control
     * @param functions
     */
    void setFunctions(QVector<Function *> * functions);
    /**
     * @brief Gets function parameters from corresponding widget
     * @return
     */
    QVector<double> getFunctionParameters();

    /**
     * @brief Gets selected function (or null if nothing selected)
     * @return
     */
    Function * getSelectedFunction();

    /**
     * @brief Gets index of selected function (-1 if nothing selected)
     * @return
     */
    int getSelectedFunctionIndex();

    /**
     * @brief Gets start value for plot drawing
     * @return
     */
    double getValueFrom() const;
    /**
     * @brief Gets end value for plot drawing
     * @return
     */
    double getValueTo() const;
    /**
     * @brief Gets step to change value for plot drawing
     * @return
     */
    double getValueStep() const;

public slots:
    void functionSelectionChanged(int index);

private:
    Ui::PlotControlWidget * ui;
    QVector<Function * > *_functions;
    PlotParametersWidget * _currentParametersWidget;

    /**
     * @brief Adds function names to combo box
     */
    void addFunctionsToCombobox();
};

#endif // PLOTCONTROLWIDGET_H
