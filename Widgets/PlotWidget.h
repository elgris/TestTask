#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>

namespace Ui {
class PlotWidget;
}

class PointsCollection;

class PlotWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit PlotWidget(QWidget *parent, PointsCollection * points);
    explicit PlotWidget(PointsCollection * points);
    ~PlotWidget();

protected:
    /**
     * @brief Draw the plot
     * @param event
     */
    void paintEvent(QPaintEvent *event);

private:
    Ui::PlotWidget *ui;
    PointsCollection * _points;
};

#endif // PLOTWIDGET_H
