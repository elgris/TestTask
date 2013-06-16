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

    inline void setMinX(double x) { this->_minX = x; updateSceneRect(); }
    inline void setMaxX(double x) { this->_maxX = x; updateSceneRect(); }
    inline void setMinY(double y) { this->_minY = y; updateSceneRect(); }
    inline void setMaxY(double y) { this->_maxY = y; updateSceneRect(); }

    /**
     * @brief Reset plot and draw its' axis
     */
    void resetPlot();

protected:
    void resizeEvent (QResizeEvent * event);
    void paintEvent(QPaintEvent *event);

private:
    double _minX;
    double _maxX;
    double _minY;
    double _maxY;

    static const double WINDOW_GAP = 0.05;

    PlotItem * _plotItem;

    Ui::PlotWidget *ui;

    /**
     * @brief Update drawing scene's scale to make sure it fits
     * widget's size
     */
    void updateSceneScale();

    /**
     * @brief Dynamic update of scene size
     */
    void updateSceneRect();
};

#endif // PLOTWIDGET_H
