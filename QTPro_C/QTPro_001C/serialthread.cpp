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
        ServerReceive=new SerialPortReceive(this);
        connect(ServerReceive,SIGNAL(byteFinish(QByteArray)),this,SIGNAL(serialFinished(QByteArray)));
        qDebug("打开串口成功");
    }else{
        qDebug("打开串口成功");
    }
    this->exec();
}
void SerialThread::onReadyRead(){
    QByteArray temp=myCom->readAll();
    while(ServerReceive->dataHandleFlag==1)
        msleep(1);
    ServerReceive->dataHandle(temp);
}
int SerialThread::send(QByteArray str){
    int byte=-1;
    myCom->flush();
    byte=myCom->write(str);
    return byte;
}
