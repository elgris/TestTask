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

protected:
    void resizeEvent (QResizeEvent * event);

private:
    double _minX;
    double _maxX;
    double _minY;
    double _maxY;

    PlotItem * _plotItem;

    Ui::PlotWidget *ui;

    /**
     * @brief Draw chart's axis
     */
    void drawAxis();

    /**
     * @brief Update drawing scene's scale to make sure it fits
     * widget's size
     */
    void updateSceneScale();
};

#endif // PLOTWIDGET_H
