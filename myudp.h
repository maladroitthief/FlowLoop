#ifndef MYUDP_H
#define MYUDP_H

#include <QObject>
#include "ui_meterwindow.h"
#include <cmath>
#include <QUdpSocket>
#include <QString>
#include <QMap>
#include <QThread>
#include <QHostAddress>
#include <QtNetwork>
#include "meterwindow.h"

namespace Ui {
class MeterWindow;
class MyUDP;
}

class MyUDP : public QObject{
    Q_OBJECT
public:
    explicit MyUDP(QObject *parent = 0);
    Ui::MyUDP *myudp;
    QHostAddress localIP;
    void initialize(Ui::MeterWindow ui);
    void setEdit();
    void delay();
    void delay(int i);
    void sendmsg(QByteArray s);
    void readData();
    void readSVP();
    void displayData();
    QString format(char const* c);
    void run();
    void getUI(Ui::MeterWindow ui);
    void dprint(QPlainTextEdit* box, QString s);
    Ui::MeterWindow *nui;
    QPlainTextEdit *box;
    QPushButton *start,*stop,*svp;
    bool proving = false;
    QLineEdit   *loop1f0,*loop1f1,*loop1f2,*loop1f3,*loop1f4,*loop1f5,*loop1f6,*loop1f7,*loop1f8,*loop1f9
                ,*loop1r0,*loop1r1,*loop1r2,*loop1r3,*loop1r4,*loop1r5,*loop1r6,*loop1r7,*loop1r8,*loop1r9
                ,*loop1e0,*loop1e1,*loop1e2,*loop1e3,*loop1e4,*loop1e5,*loop1e6,*loop1e7,*loop1e8,*loop1e9
                ,*loop1p0,*loop1p1,*loop1p2,*loop1p3,*loop1p4,*loop1p5,*loop1p6,*loop1p7,*loop1p8,*loop1p9
                ,*loop1a0,*loop1a1,*loop1a2,*loop1a3,*loop1a4,*loop1a5,*loop1a6,*loop1a7,*loop1a8,*loop1a9
                ,*loop1b0,*loop1b1,*loop1b2,*loop1b3,*loop1b4,*loop1b5,*loop1b6,*loop1b7,*loop1b8,*loop1b9
                ,*prover1,*prover2,*timer
                ,*loop1at0,*loop1at1,*loop1at2,*loop1at3,*loop1at4,*loop1at5,*loop1at6,*loop1at7,*loop1at8,*loop1at9
                ,*loop1bt0,*loop1bt1,*loop1bt2,*loop1bt3,*loop1bt4,*loop1bt5,*loop1bt6,*loop1bt7,*loop1bt8,*loop1bt9;
    QMap<QString,QString> msg;
    QString latch=      "01C2001000008000";
    QString latchclr=   "01C2001000000000";
    QString svpstart0=  "01C2001000004000";
    QString svpstart1=  "01C2001000000000";
    QString svplatch=   "01C200100000C000";
    QString svplatchclr="01C2001000004000";
    QString clearset=   "01C2041001000000";
    QString clearclr=   "01C2041000000000";
    QString prove=      "01C2001000004000";
    QString waddr=      "01C20410";
    QString raddr=      "82420410";
    QString address[84]={
        "00000000","00020000","00040000","00060000","00080000","000A0000","000C0000","000E0000",
        "00100000","00120000","00140000","00160000","00180000","001A0000","001C0000","001E0000",
        "00200000","00220000","00240000","00260000","00280000","002A0000","002C0000","002E0000",
        "00300000","00320000","00340000","00360000","00380000","003A0000","003C0000","003E0000",
        "00400000","00420000","00440000","00460000","00480000","004A0000","004C0000","004E0000",
        "00500000","00520000","00540000","00560000","00580000","005A0000","005C0000","005E0000",
        "00600000","00620000","00640000","00660000","00680000","006A0000","006C0000","006E0000",
        "00700000","00720000","00740000","00760000","00780000","007A0000","007C0000","007E0000",
        "00800000","00820000","00840000","00860000","00880000","008A0000","008C0000","008E0000",
        "00900000","00920000","00940000","00960000","00980000","009A0000","009C0000","009E0000",
        "00A00000","00A20000","00A40000","00A60000"};
    QLineEdit *edits[83]={ loop1f0,loop1f1,loop1f2,loop1f3,loop1f4,loop1f5,loop1f6,loop1f7,loop1f8,loop1f9
                          ,loop1r0,loop1r1,loop1r2,loop1r3,loop1r4,loop1r5,loop1r6,loop1r7,loop1r8,loop1r9
                          ,loop1e0,loop1e1,loop1e2,loop1e3,loop1e4,loop1e5,loop1e6,loop1e7,loop1e8,loop1e9
                          ,loop1p0,loop1p1,loop1p2,loop1p3,loop1p4,loop1p5,loop1p6,loop1p7,loop1p8,loop1p9
                          ,loop1a0,loop1a1,loop1a2,loop1a3,loop1a4,loop1a5,loop1a6,loop1a7,loop1a8,loop1a9
                          ,loop1b0,loop1b1,loop1b2,loop1b3,loop1b4,loop1b5,loop1b6,loop1b7,loop1b8,loop1b9
                          ,prover1,prover2,timer
                          ,loop1at0,loop1at1,loop1at2,loop1at3,loop1at4,loop1at5,loop1at6,loop1at7,loop1at8,loop1at9
                          ,loop1bt0,loop1bt1,loop1bt2,loop1bt3,loop1bt4,loop1bt5,loop1bt6,loop1bt7,loop1bt8,loop1bt9};
    QString keys[84]={
        "01","03","05","07","09","0b","0d","0f",
        "11","13","15","17","19","1b","1d","1f",
        "21","23","25","27","29","2b","2d","2f",
        "31","33","35","37","39","3b","3d","3f",
        "41","43","45","47","49","4b","4d","4f",
        "51","53","55","57","59","5b","5d","5f",
        "61","63","65","67","69","6b","6d","6f",
        "71","73","75","77","79","7b","7d","7f",
        "81","83","85","87","89","8b","8d","8f",
        "91","93","95","97","99","9b","9d","9f",
        "a1","a3","a5","a7"};
    QMap<QString,QLineEdit> loop1edits = {};
    ~MyUDP();
signals:

public slots:
    void signalRead();
    void runProve();
    void stopProve();
    void svpProve();
private slots:


private:
    QUdpSocket *socket;
};

#endif // MYUDP_H
