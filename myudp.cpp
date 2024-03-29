#include "myudp.h"

MyUDP::MyUDP(QObject *parent) : QObject(parent){

}
void MyUDP::initialize(Ui::MeterWindow ui){
    //assigning pointers for interacting with gui
    nui = &ui;
    box = nui->debugWindow;
    start = nui->loop1start;
    stop = nui->loop1end;
    svp = nui->loop1svp;
    connect(start,SIGNAL(clicked()),this,SLOT(runProve()));
    connect(svp,SIGNAL(clicked()),this,SLOT(svpProve()));
    connect(stop,SIGNAL(clicked()),this,SLOT(stopProve()));
    //setting the static IP
    localIP.setAddress("192.168.1.88");
    //pointing to all the windows
    this->setEdit();
    //creating the socket at IP and port 1280(source port)
    socket = new QUdpSocket(this);
    if(socket->bind(localIP,1280)){
        box->insertPlainText("Bind Success\n");
    }
    else
        box->insertPlainText("Bind failed\n");
    connect(socket, SIGNAL(readyRead()),this, SLOT(signalRead()));
    //read and write commands
    QString read = "83420011";
    QString write = "83c20011";
    QString init = "0000c00001feff00ffffff00";
    //initializing DDR
    this->sendmsg((write+init).toStdString().c_str());
    box->insertPlainText("Initializing DDR bits...\n");
    this->sendmsg(read.toStdString().c_str());
    //waiting a bit for a response
    this->delay();
    QByteArray datagram;
    while (socket->hasPendingDatagrams()){
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size());
        datagram = datagram.toHex();
    }
    //confirming if correct values were returned
    if(init.compare(datagram.data())){
        box->insertPlainText("Success.\n");
        start->setEnabled(true);
        svp->setEnabled(true);
    }
    else
        box->insertPlainText("Failure.\n");
}
void MyUDP::runProve(){
    //running a prove
    start->setEnabled(false);
    svp->setEnabled(false);
    stop->setEnabled(true);
    proving=true;
    this->sendmsg(clearset.toStdString().c_str());
    this->delay();
    this->sendmsg(clearclr.toStdString().c_str());
    while(proving){
        this->readData();
    }
}
void MyUDP::svpProve(){
    //small volume proving
    start->setEnabled(false);
    svp->setEnabled(false);
    stop->setEnabled(true);
    proving=true;
    //clear the existing data
    this->sendmsg(clearset.toStdString().c_str());
    this->sendmsg(clearclr.toStdString().c_str());
    this->sendmsg(svpstart0.toStdString().c_str());
    this->sendmsg(svpstart1.toStdString().c_str());
    while(proving){
        this->readSVP();
    }
}
void MyUDP::stopProve(){
    //halting a prove
    start->setEnabled(true);
    svp->setEnabled(true);
    stop->setEnabled(false);
    proving=false;
}
void MyUDP::readSVP(){
    msg.clear();
    this->sendmsg(svplatch.toStdString().c_str());
    this->sendmsg(svplatchclr.toStdString().c_str());
    for(int i=0;i<82;i++){
        //sending the write address and the read
        this->sendmsg((waddr+address[i]).toStdString().c_str());
        this->sendmsg(raddr.toStdString().c_str());
    }
    this->delay(100);
    this->displayData();
}
void MyUDP::readData(){
    //latch registers
    msg.clear();
    this->sendmsg(latch.toStdString().c_str());
    this->sendmsg(latchclr.toStdString().c_str());
    for(int i=0;i<82;i++){
        //sending the write address and the read
        this->sendmsg((waddr+address[i]).toStdString().c_str());
        this->sendmsg(raddr.toStdString().c_str());
    }
    this->delay(100);
    this->displayData();
}
void MyUDP::displayData(){
    //this handles forward,reverse,and error counts
    for(int i=0;i<30;i++){
        edits[i]->setText(format(msg.value(keys[i]).toStdString().c_str()));
    }
    //this handles A and B counts
    //a edge=counts
    //a count=
    for(int i=40;i<60;i++){
        edits[i]->setText(format(msg.value(keys[i-10]).toStdString().c_str()));
    }
    //A timer and B timer
    for(int i=63;i<83;i++){
        edits[i]->setText(format(msg.value(keys[i-13]).toStdString().c_str()));
    }
    //Prover Timers
    for(int i=60;i<62;i++){
        edits[i]->setText(format(msg.value(keys[i+10]).toStdString().c_str()));
    }
    //Master Timer
    edits[62]->setText(format(msg.value(keys[82]).toStdString().c_str()));
    //this handles phase angle
    for(int i=30;i<40;i++){
        double p,f,r,e;
        p=format(msg.value(keys[i+42]).toStdString().c_str()).toDouble();
        f=format(msg.value(keys[i-30]).toStdString().c_str()).toDouble();
        r=format(msg.value(keys[i-20]).toStdString().c_str()).toDouble();
        e=format(msg.value(keys[i-10]).toStdString().c_str()).toDouble();
        if(f!=0&&r!=0&&e!=0)
            edits[i]->setText(QString::number(fmod((p/(f+r+e))*180,360.0)));
        else
            edits[i]->setText("0");
    }
}
QString MyUDP::format(char const* c){
    //taking the char*, converting to a QString, parsing the data
    QString s=(QString)c;
    QString t=s.mid(12,2)+s.mid(10,2)+s.mid(8,2)+s.mid(4,2);
    QByteArray b=t.toStdString().c_str();
    bool k;
    return QString::number(t.toInt(&k,16));
}
void MyUDP::sendmsg(QByteArray s){
    //creating a datagram and converting it from hex to ascii
    QByteArray datagram;
    datagram = QByteArray::fromHex(s);
    //attempting to write datagram
    socket->writeDatagram(datagram.data(), datagram.size(), QHostAddress("192.168.1.121"), 27181);
}
void MyUDP::signalRead(){
    //box->insertPlainText("Recieving Message\n");
    //while datagrams are pending, read them, convert to hex, print to debug
    while (socket->hasPendingDatagrams()){
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size());
        datagram = datagram.toHex();
        msg.insert(QString::fromStdString(datagram.data()).mid(2,2),QString::fromStdString(datagram.data()));
        //box->insertPlainText(QString::fromStdString(datagram.data()).mid(2,2));
        //box->insertPlainText(tr("\nReceived datagram: \"%1\"\n").arg(datagram.data()));
    }
}
void MyUDP::getUI(Ui::MeterWindow ui){
    //pointing to the ui
    nui = &ui;
    box = nui->debugWindow;
}
void MyUDP::dprint(QPlainTextEdit* box, QString s){
    //printing to the debug window
    box->insertPlainText(s+"\n");
}
void MyUDP::setEdit(){
    edits[0]=nui->loop1f0;
    edits[1]=nui->loop1f1;
    edits[2]=nui->loop1f2;
    edits[3]=nui->loop1f3;
    edits[4]=nui->loop1f4;
    edits[5]=nui->loop1f5;
    edits[6]=nui->loop1f6;
    edits[7]=nui->loop1f7;
    edits[8]=nui->loop1f8;
    edits[9]=nui->loop1f9;
    edits[10]=nui->loop1r0;
    edits[11]=nui->loop1r1;
    edits[12]=nui->loop1r2;
    edits[13]=nui->loop1r3;
    edits[14]=nui->loop1r4;
    edits[15]=nui->loop1r5;
    edits[16]=nui->loop1r6;
    edits[17]=nui->loop1r7;
    edits[18]=nui->loop1r8;
    edits[19]=nui->loop1r9;
    edits[20]=nui->loop1e0;
    edits[21]=nui->loop1e1;
    edits[22]=nui->loop1e2;
    edits[23]=nui->loop1e3;
    edits[24]=nui->loop1e4;
    edits[25]=nui->loop1e5;
    edits[26]=nui->loop1e6;
    edits[27]=nui->loop1e7;
    edits[28]=nui->loop1e8;
    edits[29]=nui->loop1e9;
    edits[30]=nui->loop1p0;
    edits[31]=nui->loop1p1;
    edits[32]=nui->loop1p2;
    edits[33]=nui->loop1p3;
    edits[34]=nui->loop1p4;
    edits[35]=nui->loop1p5;
    edits[36]=nui->loop1p6;
    edits[37]=nui->loop1p7;
    edits[38]=nui->loop1p8;
    edits[39]=nui->loop1p9;
    edits[40]=nui->loop1a0;
    edits[41]=nui->loop1a1;
    edits[42]=nui->loop1a2;
    edits[43]=nui->loop1a3;
    edits[44]=nui->loop1a4;
    edits[45]=nui->loop1a5;
    edits[46]=nui->loop1a6;
    edits[47]=nui->loop1a7;
    edits[48]=nui->loop1a8;
    edits[49]=nui->loop1a9;
    edits[50]=nui->loop1b0;
    edits[51]=nui->loop1b1;
    edits[52]=nui->loop1b2;
    edits[53]=nui->loop1b3;
    edits[54]=nui->loop1b4;
    edits[55]=nui->loop1b5;
    edits[56]=nui->loop1b6;
    edits[57]=nui->loop1b7;
    edits[58]=nui->loop1b8;
    edits[59]=nui->loop1b9;
    edits[60]=nui->loop1t0;
    edits[61]=nui->loop1t1;
    edits[62]=nui->loop1timer;
    edits[63]=nui->loop1at0;
    edits[64]=nui->loop1at1;
    edits[65]=nui->loop1at2;
    edits[66]=nui->loop1at3;
    edits[67]=nui->loop1at4;
    edits[68]=nui->loop1at5;
    edits[69]=nui->loop1at6;
    edits[70]=nui->loop1at7;
    edits[71]=nui->loop1at8;
    edits[72]=nui->loop1at9;
    edits[73]=nui->loop1bt0;
    edits[74]=nui->loop1bt1;
    edits[75]=nui->loop1bt2;
    edits[76]=nui->loop1bt3;
    edits[77]=nui->loop1bt4;
    edits[78]=nui->loop1bt5;
    edits[79]=nui->loop1bt6;
    edits[80]=nui->loop1bt7;
    edits[81]=nui->loop1bt8;
    edits[82]=nui->loop1bt9;
}
void MyUDP::delay(int i){
    QTime dieTime= QTime::currentTime().addMSecs(i);
    while(QTime::currentTime() < dieTime)
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
void MyUDP::delay(){
    QTime dieTime= QTime::currentTime().addMSecs(500);
    while(QTime::currentTime() < dieTime)
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

MyUDP::~MyUDP(){

}
