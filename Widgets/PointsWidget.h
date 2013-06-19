#ifndef POINTSWIDGET_H
#define POINTSWIDGET_H

#include <QWidget>

namespace Ui {
class PointsWidget;
}
class PointsCollection;
class PointsWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit PointsWidget(QWidget *parent, PointsCollection *points);
    ~PointsWidget();
public slots:
    void previousPageClicked();
    void nextPageClicked();
    /**
     * @brief Refresh currently dislayed page with data from points collection
     */
    void updatePage();
protected:
    /**
     * @brief Event handler to update current page on widget's show
     * @param event
     */
    void showEvent(QShowEvent * event);
private:
    Ui::PointsWidget *ui;
    PointsCollection *_points;

    int _perPage;       // number of entries per page
    int _pageNumber;    // number of current page

    /**
     * @brief Update state (caption and 'enabled' state) of 'Previous Page' button
     */
    void updatePreviousPageButton();

    /**
     * @brief Update state (caption and 'enabled' state) of 'Next Page' button
     */
    void updateNextPageButton();

    /**
     * @brief Calculate available number of pages
     * @return
     */
    int getPagesNumber();
};

#endif // POINTSWIDGET_H
