#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QThread>
#include "serialportreceive.h"
#include "qextserialport.h"
class SerialThread : public QThread
{
    Q_OBJECT
public:
    explicit SerialThread(QObject *parent = 0);
    int send(QByteArray str);
private:
    void run();
    SerialPortReceive *SerialReceive;
    QextSerialPort *myCom;
signals:
    void serialFinished(QByteArray str);
    
public slots:
    void onReadyRead();
    
};

#endif // SERIALTHREAD_H
