#ifndef MODE3_H
#define MODE3_H

#include <QThread>
#include "VariableDefinition.h"
extern volatile unsigned int human_state;
extern volatile unsigned int lamp_state;
extern volatile unsigned int warning_state;
class Mode3 : public QThread
{
    Q_OBJECT
public:
    explicit Mode3(QObject *parent = 0);
    void ThreadQuit();
private:
    void run();
    bool ThreadFlag;
signals:
    void mod(QString type,unsigned int command,unsigned int channel);
public slots:
    
};

#endif // MODE3_H
