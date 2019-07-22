#ifndef MODE2_H
#define MODE2_H

#include <QThread>
#include "VariableDefinition.h"
extern volatile unsigned int fan_state;
extern volatile unsigned int lamp1_state;
extern volatile unsigned int lamp2_state;
extern volatile unsigned int smoke_value;
class Mode2 : public QThread
{
    Q_OBJECT
public:
    explicit Mode2(QObject *parent = 0);
    void ThreadQuit();
private:
    void run();
    bool ThreadFlag;
signals:
    void mod(QString type,unsigned int command,unsigned int channel);
    
public slots:
    
};

#endif // MODE2_H
