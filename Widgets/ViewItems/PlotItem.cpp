#include "PlotItem.h"
#include <QPainter>

PlotItem::PlotItem()
{
}

void PlotItem::addPoint(double x, double y)
{
    double rectXMin = _boundingRect.x();
    double rectXMax = rectXMin + _boundingRect.width();
    double rectYMin = _boundingRect.y();
    double rectYMax = rectXMin + _boundingRect.height();
    if(x < rectXMin) {
        _boundingRect.setX(x);
    }
    if(x > rectXMax) {
        _boundingRect.setWidth(x - rectXMin);
    }
    if(y < rectYMin) {
        _boundingRect.setY(y);
    }
    if(y > rectYMax) {
        _boundingRect.setHeight(y - rectYMin);
    }
    _points.append(QPointF(x, y));
}

void PlotItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPolyline(_points.data(), _points.size());
}

QRectF PlotItem::boundingRect() const
{
    return _boundingRect;
}
