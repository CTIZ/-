#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QThread>
#include "qextserialport.h"
#include "serialportreceive.h"

class SerialThread : public QThread
{
    Q_OBJECT
public:
    explicit SerialThread(QObject *parent = 0);
    int send(QByteArray str);
private:
    QextSerialPort *myCom;
    SerialPortReceive *SerialPort;
    void run();
signals:
    void data(const QByteArray &);
    
public slots:
    void onReadyRead();
    
};

#endif // SERIALTHREAD_H
