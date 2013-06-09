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
    explicit PlotParametersWidget(QWidget *parent = 0);
    ~PlotParametersWidget();
    
private:
    Ui::PlotParametersWidget *ui;
};

#endif // PLOTPARAMETERSWIDGET_H
