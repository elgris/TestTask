#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>

namespace Ui {
class PlotWidget;
}

class PlotWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit PlotWidget(QWidget *parent = 0);
    ~PlotWidget();

    inline void setMinX(double x) { this->_minX = x; }
    inline void setMaxX(double x) { this->_maxX = x; }
    inline void setMinY(double y) { this->_minY = y; }
    inline void setMaxY(double y) { this->_maxY = y; }

protected:
    void paintEvent(QPaintEvent *event);

private:
    double _minX;
    double _maxX;
    double _minY;
    double _maxY;

    Ui::PlotWidget *ui;

    void drawAxis();
};

#endif // PLOTWIDGET_H
