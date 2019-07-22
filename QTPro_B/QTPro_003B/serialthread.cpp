#include "serialthread.h"

SerialThread::SerialThread(QObject *parent) :
    QThread(parent)
{
    moveToThread(this);
}
void SerialThread::run(){
    myCom=new QextSerialPort("/dev/"+zh,QextSerialPort::EventDriven);
    myCom->setBaudRate(BaudRateType(zhi[0]));
    myCom->setDataBits(DataBitsType(zhi[1]));
    myCom->setFlowControl(FLOW_OFF);
    myCom->setParity(ParityType(zhi[2]));
    myCom->setStopBits(STOP_1);
    if(myCom->open(QIODevice::ReadWrite)){
        connect(myCom,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
        SerialReceive=new SerialPortReceive();
        connect(SerialReceive,SIGNAL(byteFinish(QByteArray)),this,SIGNAL(serialFinished(QByteArray)));
        qDebug("ok");
    }else{
        qDebug("error");
    }
    this->exec();
}
void SerialThread::onReadyRead(){
    QByteArray temp=myCom->readAll();
    while(SerialReceive->dataHandleFlag==1)
        msleep(500);
    SerialReceive->dataHandle(temp);
}
int SerialThread::send(QByteArray str){
    int byte=-1;
    myCom->flush();
    byte=myCom->write(str);
    return byte;
}
