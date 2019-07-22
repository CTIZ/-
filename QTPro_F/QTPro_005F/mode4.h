#ifndef MODE4_H
#define MODE4_H

#include <QThread>
#include "VariableDefinition.h"
extern volatile unsigned int lamp1_state;
extern volatile unsigned int lamp2_state;
extern volatile unsigned int warning_state;
extern volatile unsigned int human_state;
class Mode4 : public QThread
{
    Q_OBJECT
public:
    explicit Mode4(QObject *parent = 0);
    void ThreadQuit();
private:
    void run();
    bool ThreadFlag;
signals:
    void mod(QString type,unsigned int command,unsigned int channel);
public slots:
    
};

#endif // MODE4_H
