#ifndef MODE_H
#define MODE_H

#include <QThread>
#include "VariableDefinition.h"
extern volatile float temp_value;
extern volatile float hum_value;
extern volatile unsigned int fan_state;
extern volatile unsigned int lamp_state;
extern volatile unsigned int warning_state;
extern volatile unsigned int curtain_state;
extern volatile unsigned int rfid_state;

extern volatile unsigned int air_state;
extern volatile unsigned int tv_state;
extern volatile unsigned int dvd_state;

extern int ld[4];
extern bool chk[10];

class Mode : public QThread
{
    Q_OBJECT
public:
    explicit Mode(QObject *parent = 0);
    void ThreadQuit();
private:
    void run();
    bool ThreadFlag;
signals:
    void mod(QString type,unsigned int command,unsigned int channel);
    
public slots:
    
};

#endif // MODE_H
