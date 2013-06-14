#ifndef PLOTITEM_H
#define PLOTITEM_H

#include <QGraphicsItem>

namespace Ui {
class PlotItem;
}

class PlotItem : public QGraphicsItem
{
public:
    explicit PlotItem();

    /**
     * @brief Add point to the plot.
     * Plot will build line from latter point to this new point
     * @param x
     * @param y
     */
    void addPoint(double x, double y);

    /**
     * @brief Clear all plot's points
     */
    void clearPoints() ;

    /**
     * @brief Pure virtual method of QGraphicsItem
     * @param painter
     * @param option
     * @param widget
     */
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * @brief Pure virtual method of QGraphicsItem
     * @return
     */
    virtual QRectF boundingRect() const;

private:
    QRectF _boundingRect;
    std::vector<QPointF> _points;
    
};

#endif // PLOTITEM_H
