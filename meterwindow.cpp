#include "meterwindow.h"
#include "ui_meterwindow.h"

MeterWindow::MeterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MeterWindow){
    ui->setupUi(this);
}
MeterWindow::~MeterWindow(){
    ui->loop1end->click();
    delete ui;
}
void MeterWindow::on_actionConnect_triggered(){
    MyUDP *myudp = new MyUDP();
    myudp->initialize(*ui);
    //ui->loop1start->click();
}
void MeterWindow::closeEvent(QCloseEvent *event) {
    //making sure the prove dies when closed
    ui->loop1end->click();
}
void MeterWindow::on_actionQuit_triggered(){
    ui->loop1end->click();
    QApplication::quit();
}
