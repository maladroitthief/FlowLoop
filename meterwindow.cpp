#include "meterwindow.h"
#include "ui_meterwindow.h"

MeterWindow::MeterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MeterWindow){
    ui->setupUi(this);
}
MeterWindow::~MeterWindow(){
    delete ui;

}
void MeterWindow::on_actionConnect_triggered(){
    MyUDP *myudp = new MyUDP(*ui);
}
