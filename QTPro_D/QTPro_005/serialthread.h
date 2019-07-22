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
    SerialPortReceive *SerialPort;
    QextSerialPort *myCom;
signals:
    void data(const QByteArray &);
    
public slots:
    void onReadyRead();
    
};

#endif // SERIALTHREAD_H
