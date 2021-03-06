#ifndef POINTSCOLLECTION_H
#define POINTSCOLLECTION_H

#include <QObject>
#include <QPointF>
#include <QVector>


/**
 * @brief Collection that aggregates calculated points
 */
class PointsCollection : public QObject
{
    Q_OBJECT
public:
    explicit PointsCollection(QObject *parent = 0);

    /**
     * @brief Get points stored in collection
     * @return
     */
    const QVector<QPointF> & getPoints() const { return _points; }

    /**
     * @brief Set bunch of points to collection.
     * collectionChanged() will be fired only once
     * @param points
     */
    void setPoints(QVector<QPointF> & points);
    
signals:
    void collectionChanged();

public slots:
    void addPoint(double x, double y);
    void addPoint(const QPointF & point);
    void clear();

private:
    QVector<QPointF> _points;
};

#endif // POINTSCOLLECTION_H
