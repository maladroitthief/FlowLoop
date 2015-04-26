#ifndef METERWINDOW_H
#define METERWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <thread>
#include <qthread.h>
#include "myudp.h"

namespace Ui {
class MeterWindow;
}

class MeterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MeterWindow(QWidget *parent = 0);    
    ~MeterWindow();
    testFunction();
    Ui::MeterWindow *ui;

private slots:
    void on_actionConnect_triggered();

private:

};

#endif // METERWINDOW_H
