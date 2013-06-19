#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>

namespace Ui {
class PlotWidget;
}

class PointsCollection;

/**
 * @brief Widget displays plot
 * @todo Widget also contains buttons which cannot be here
 * because painting affects them - plot's lines can appear on buttons
 */
class PlotWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit PlotWidget(QWidget *parent, PointsCollection * points);
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
