#include "serialthread.h"

SerialThread::SerialThread(QObject *parent) :
    QThread(parent)
{
    moveToThread(this);
}
void SerialThread::run(){
    myCom=new QextSerialPort("/dev/ttyUSB0",QextSerialPort::EventDriven);
    myCom->setBaudRate(BAUD115200);
    myCom->setDataBits(DATA_8);
    myCom->setFlowControl(FLOW_OFF);
    myCom->setParity(PAR_NONE);
    myCom->setStopBits(STOP_1);
    if(myCom->open(QIODevice::ReadWrite)){
        connect(myCom,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
        SerialPort=new SerialPortReceive();
        connect(SerialPort,SIGNAL(byteFinish(QByteArray)),this,SIGNAL(data(QByteArray)));
        qDebug("ok");
    }else{
        qDebug("error");
    }
    this->exec();
}
void SerialThread::onReadyRead(){
    QByteArray temp=myCom->readAll();
    while(SerialPort->dataHandleFlag==1)
        msleep(1);
    SerialPort->dataHandle(temp);
}
int SerialThread::send(QByteArray str){
    int byte=-1;
    myCom->flush();
    byte=myCom->write(str);
    return byte;
}
