#ifndef PLOT_H
#define PLOT_H
#include <QVector>
#include "mainwindow.h"
#include "ui_mainwindow.h"

class Plot
{
public:
    Plot(QVector<double>,QVector<double>,double,double,Ui::MainWindow);
};

#endif // PLOT_H
