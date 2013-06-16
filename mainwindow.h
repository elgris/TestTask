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
    void startClicked();
    void pauseClicked();
    void valueProcessed(double, double, double);
    void processingFinished();

private:
    Ui::MainWindow *ui;
    PlotControlWidget *_plotControlWidget;
    PlotWidget * _plotWidget;
    PlotBuilder *_plotBuilder;

    static const QString LABEL_PAUSE;
    static const QString LABEL_START;
    static const QString LABEL_CONTINUE;
    static const QString LABEL_PROCESSING;

    /**
     * @brief Sets up Plot builder and all signal-slot connections
     */
    void setupPlotBuilder();

    /**
     * @brief Loads available functions
     * @todo: this piece of code can use dynamic loading (from some resource),
     * but for now it just uses hardcoded functions. For test is enough
     */
    QVector<Function *> * loadFunctions();
};

#endif // MAINWINDOW_H
