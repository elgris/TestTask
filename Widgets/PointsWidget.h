#ifndef POINTSWIDGET_H
#define POINTSWIDGET_H

#include <QWidget>

namespace Ui {
class PointsWidget;
}

class PointsWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit PointsWidget(QWidget *parent = 0);
    ~PointsWidget();
public slots:
    void previousPageClicked();
    void nextPageClicked();
private:
    Ui::PointsWidget *ui;
};

#endif // POINTSWIDGET_H
