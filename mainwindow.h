#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class PlotControlWidget;
class PlotWidget;
class Function;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void startClicked();
    void stopClicked();
    void pauseClicked();

private:
    Ui::MainWindow *ui;
    PlotControlWidget *_plotControlWidget;
    PlotWidget * _plotWidget;

    /**
     * @brief Loads available functions
     * @todo: this piece of code can use dynamic loading (from some resource),
     * but for now it just uses hardcoded functions. For test is enough
     */
    QVector<Function *> * loadFunctions();
};

#endif // MAINWINDOW_H
