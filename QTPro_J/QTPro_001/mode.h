#ifndef MODE_H
#define MODE_H

#include <QThread>
#include "VariableDefinition.h"
extern volatile unsigned int fan_state;
extern volatile unsigned int lamp_state;
extern volatile unsigned int warning_state;
extern volatile unsigned int curtain_state;
extern volatile float ill_value;
extern volatile float temp_value;
extern int Modes;
extern int ld1[5];
extern int ld2[5];
extern int ld3[5];
extern int ld4[5];
class Mode : public QThread
{
    Q_OBJECT
public:
    explicit Mode(QObject *parent = 0);
    void ThreadQuit();
private:
    bool ThreadFlag;
    void run();

signals:
    void mod(QString type,unsigned int command,unsigned int channel);
    
public slots:
    
};

#endif // MODE_H
