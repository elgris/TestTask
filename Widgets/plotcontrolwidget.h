#ifndef PLOTCONTROLWIDGET_H
#define PLOTCONTROLWIDGET_H

#include <QWidget>
#include <QVector>
#include "Models/Function.h"
namespace Ui {
class PlotControlWidget;
}

class PlotControlWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit PlotControlWidget(QWidget *parent = 0);
    ~PlotControlWidget();

public slots:
    void functionSelectionChanged(int index);

private:
    Ui::PlotControlWidget *ui;
    QVector<Function * > *_functions;

    /**
     * @brief Loads available functions and assigns them to combo box
     * @todo: this piece of code can use dynamic loading (from some resource),
     * but for now it just uses hardcoded funtions. For test is enough
     */
    void loadFunctions();

    /**
     * @brief Adds function names to combo box
     */
    void addFunctionsToCombobox();
};

#endif // PLOTCONTROLWIDGET_H
