#include "actioncontrol.h"
#include <stdio.h>
#include "ui_meterwindow.h"
#include <QString>

actioncontrol::actioncontrol(){

}
void actioncontrol::run(){

}
void actioncontrol::getUI(Ui::MeterWindow ui){
    nui = &ui;
}
void actioncontrol::dprint(QPlainTextEdit* box, QString s){
    box->insertPlainText(s+"\n");
}

int actioncontrol::startserver(){
    return 0;
}


