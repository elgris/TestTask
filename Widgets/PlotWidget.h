#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>

namespace Ui {
class PlotWidget;
}

class PlotItem;

class PlotWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit PlotWidget(QWidget *parent = 0);
    ~PlotWidget();

    void addPoint(double x, double y);

    inline void setMinX(double x) { this->_minX = x; }
    inline void setMaxX(double x) { this->_maxX = x; }
    inline void setMinY(double y) { this->_minY = y; }
    inline void setMaxY(double y) { this->_maxY = y; }

    /**
     * @brief Reset plot and draw its' axis
     */
    void resetPlot();

protected:
    void resizeEvent (QResizeEvent * event);

private:
    double _minX;
    double _maxX;
    double _minY;
    double _maxY;

    int _initialWidth;
    int _initialHeight;

    PlotItem * _plotItem;

    Ui::PlotWidget *ui;

    /**
     * @brief Update drawing scene's scale to make sure it fits
     * widget's size
     */
    void updateSceneScale();

    /**
     * @brief Normalize value for OX axis
     * (Adjust it according current min, max and center values)
     * @param value
     */
    double normalizeXValue(double value);

    /**
     * @brief Normalize value for OY axis
     * (Adjust it according current min, max and center values)
     * @param value
     */
    double normalizeYValue(double value);
};

#endif // PLOTWIDGET_H
