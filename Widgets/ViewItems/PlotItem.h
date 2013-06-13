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

    void addPoint(double x, double y);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QRectF boundingRect() const;

private:
    QRectF _boundingRect;
    QVector<QPointF> _points;
    
};

#endif // PLOTITEM_H
