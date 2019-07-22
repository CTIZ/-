#include "mode1.h"

Mode1::Mode1(QObject *parent) :
    QThread(parent)
{
}
void Mode1::run(){
    ThreadFlag=true;
    if(lamp1_state!=SWITCH_OFF||lamp2_state!=SWITCH_OFF){
        emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
        msleep(500);
    }
    if(curtain_state!=CHANNEL_1){
        emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
        msleep(500);
        emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
        msleep(500);
    }
    if(warning_state!=SWITCH_OFF){
        emit mod(WL_SERVE,SWITCH_OFF,CHANNEL_ALL);
        msleep(500);
    }
    while(ThreadFlag){
        if(gas_value>100){
            if(fan_state!=SWITCH_ON){
                emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                msleep(500);
            }
        }else{
            if(fan_state!=SWITCH_OFF){
                emit mod(FAN_SERVE,SWITCH_OFF,CHANNEL_ALL);
                msleep(500);
            }
        }
        sleep(3);
    }
}
void Mode1::ThreadQuit(){
    ThreadFlag=false;
    this->wait(3);
    this->quit();
}
