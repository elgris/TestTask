#ifndef PLOTCONTROLWIDGET_H
#define PLOTCONTROLWIDGET_H

#include <QWidget>

namespace Ui {
class PlotControlWidget;
}

class PlotControlWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit PlotControlWidget(QWidget *parent = 0);
    ~PlotControlWidget();
    
private:
    Ui::PlotControlWidget *ui;
};

#endif // PLOTCONTROLWIDGET_H
