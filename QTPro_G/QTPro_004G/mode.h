#ifndef MODE_H
#define MODE_H

#include <QThread>
#include "VariableDefinition.h"
#include "sql.h"
extern volatile float temp_value;
extern volatile float ill_value;
extern volatile unsigned int smoke_value;
extern volatile unsigned int curtain_state;
extern volatile unsigned int fan_state;
extern volatile unsigned int air_state;
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
    void mod(QString type,unsigned int command,unsigned int channel,QString value);
    
public slots:
    
};

#endif // MODE_H
