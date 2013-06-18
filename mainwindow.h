#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class PlotControlWidget;
class PlotWidget;
class Function;
class PlotBuilder;
class PointsCollection;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void startProcessing();
    void pauseProcessing();
    void resumeProcessing();
    void stopProcessing();

public slots:
    /**
     * @brief Processes click() signal of the button
     * Starts calculation process
     */
    void startClicked();
    /**
     * @brief Pauses or resumes calculation
     */
    void pauseClicked();
    /**
     * @brief Receives calculated value and current progress
     */
    void valueProcessed(double, double, double);
    /**
     * @brief Stops calculation
     */
    void processingFinished();
    /**
     * @brief Save current calculation results
     */
    void saveClicked();
    /**
     * @brief Load current calculation status
     */
    void loadClicked();
private:
    Ui::MainWindow *ui;

    PlotControlWidget *_plotControlWidget;  // widget with plot control inputs
    PlotWidget * _plotWidget;   // widget draws the plot itself
    PlotBuilder *_plotBuilder;  // service that calculates function in separate thread
    PointsCollection *_points;  // collection of points that were calculated

    static const QString LABEL_PAUSE;
    static const QString LABEL_START;
    static const QString LABEL_CONTINUE;
    static const QString LABEL_PROCESSING;

    /**
     * @brief Sets up connections between components
     */
    void setupConnections();

    /**
     * @brief Loads available functions
     * @todo: this piece of code can use dynamic loading (from some resource),
     * but for now it just uses hardcoded functions. For test is enough
     */
    QVector<Function *> * loadFunctions();
};

#endif // MAINWINDOW_H
