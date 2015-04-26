#ifndef ACTIONCONTROL_H
#define ACTIONCONTROL_H

#include <Winsock2.h>
#include <stdio.h>
#include <iostream>

#include <QObject>
#include <QUdpSocket>
#include "ui_meterwindow.h"
#include <QString>

#pragma comment(lib,"ws2_32.lib")
#define BUFLEN 512
#define PORT 27181
#define LOOPS 3
#define REGNUM 62
#define SERVER "192.168.1.121"

class actioncontrol : public QThread{
    Q_OBJECT
public:
    actioncontrol();
    int startserver();
    void run();
    void getUI(Ui::MeterWindow ui);
    void dprint(QPlainTextEdit* box, QString s);

    Ui::MeterWindow *nui;
};

#endif // ACTIONCONTROL_H
