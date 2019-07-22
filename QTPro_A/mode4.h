#ifndef MODE4_H
#define MODE4_H

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
extern bool chk[4];
extern QString ld[3];

class Mode4 : public QThread
{
    Q_OBJECT
public:
    explicit Mode4(QObject *parent = 0);
    void ThreadQuit();
private:
    void run();
    bool ThreadFlag;
private slots:
    void mySql(QString qj);

signals:
    void mod(QString type,unsigned int command,unsigned int channel);
    void AppendText(QString time,QString tj,QString qj);
    
public slots:

    
};

#endif // MODE4_H
