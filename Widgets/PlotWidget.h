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
public slots:
    /**
     * @brief Slot controls clicking on buttonCenterCoordinates
     * Moves position of center of coordinates system to middle point of points collection
     */
    void centerCoordinatesClicked();
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
