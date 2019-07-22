#include "mode1.h"

Mode1::Mode1(QObject *parent) :
    QThread(parent)
{
}
void Mode1::run(){
    ThreadFlag=false;
    if(lamp_state!=SWITCH_OFF){
        emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
        msleep(500);
    }
    if(curtain_state!=CHANNEL_1){
        emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
        msleep(500);
        emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
        msleep(500);
    }
    while(1){
        if(pm_value>75){
            if(fan_state!=SWITCH_ON){
                emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                msleep(500);
            }
        }
        if(ThreadFlag)
            break;
        sleep(3);
    }
}
void Mode1::ThreadQuit(){
    ThreadFlag=true;
    this->wait(3);
    this->quit();
}
