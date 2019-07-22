#ifndef MODE5_H
#define MODE5_H

#include <QThread>
#include "VariableDefinition.h"
#include "QDateTime"
#include "sql.h"

extern volatile unsigned int fan_state;
extern volatile unsigned int lamp_state;
extern volatile unsigned int warning_state;
extern volatile unsigned int curtain_state;
extern volatile float ill_value;
extern volatile float temp_value;
extern volatile unsigned int pm_value;


class Mode5 : public QThread
{
    Q_OBJECT
public:
    explicit Mode5(QObject *parent = 0);
    void ThreadQuit();
private:
    void run();
    bool ThreadFlag;
signals:
    void mod(QString type,unsigned int command,unsigned int channel);
public slots:
    
};

#endif // MODE5_H
