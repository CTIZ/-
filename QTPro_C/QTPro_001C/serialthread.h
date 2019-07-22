#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QThread>
#include "serialportreceive.h"
#include "qextserialport.h"
//外部变量，配置参数
extern QString zh;
extern int zhi[3];

class SerialThread : public QThread
{
    Q_OBJECT
public:
    explicit SerialThread(QObject *parent = 0);
    int send(QByteArray str);
private:
    SerialPortReceive *ServerReceive;
    QextSerialPort *myCom;
    void run();
signals:
    void serialFinished(const QByteArray &);
    
public slots:
    void onReadyRead();
    
};

#endif // SERIALTHREAD_H
