#ifndef MODE1_H
#define MODE1_H

#include <QThread>
#include "VariableDefinition.h"
extern volatile unsigned int fan_state;
extern volatile unsigned int lamp_state;
extern volatile unsigned int curtain_state;
extern volatile unsigned int pm_value;
class Mode1 : public QThread
{
    Q_OBJECT
public:
    explicit Mode1(QObject *parent = 0);
    void ThreadQuit();
private:
    void run();
    bool ThreadFlag;
signals:
    void mod(QString type,unsigned int command,unsigned int channel);
    
public slots:
    
};

#endif // MODE1_H
