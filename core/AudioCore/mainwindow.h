#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QVector>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void plot(QVector<double>,QVector<double>,double,double);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
