#ifndef METERWINDOW_H
#define METERWINDOW_H

#include <sys/types.h>
#include "myudp.h"
#include <QMainWindow>
#include <QtGui>
#include <thread>
#include <qthread.h>


namespace Ui {
class MyUDP;
class MeterWindow;
}

class MeterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MeterWindow(QWidget *parent = 0);
    //MyUDP *myudp;
    ~MeterWindow();
    testFunction();
    Ui::MeterWindow *ui;

private slots:
    void on_actionConnect_triggered();

private:

};

#endif // METERWINDOW_H
