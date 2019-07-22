#ifndef MODE3_H
#define MODE3_H

#include <QThread>
#include "VariableDefinition.h"
extern volatile unsigned int fan_state;
extern volatile unsigned int lamp1_state;
extern volatile unsigned int lamp2_state;
extern volatile unsigned int smoke_value;
class Mode3 : public QThread
{
    Q_OBJECT
public:
    explicit Mode3(QObject *parent = 0);
    void ThreadQuit();
private:
    bool ThreadFlag;
    void run();
signals:
    void mod(QString type,unsigned int command,unsigned int channel);
public slots:
    
};

#endif // MODE3_H
