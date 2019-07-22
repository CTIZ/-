#include "mode2.h"

Mode2::Mode2(QObject *parent) :
    QThread(parent)
{
}
void Mode2::run(){
    ThreadFlag=true;
    if(lamp1_state!=SWITCH_ON||lamp2_state!=SWITCH_ON){
        emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
        msleep(500);
    }
    if(curtain_state!=CHANNEL_3){
        emit mod(CT_SERVE,SWITCH_ON,CHANNEL_3);
        msleep(500);
        emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
        msleep(500);
    }
    if(warning_state!=SWITCH_OFF){
        emit mod(WL_SERVE,SWITCH_OFF,CHANNEL_ALL);
        msleep(500);
    }
    while(ThreadFlag){
        if(smoke_value>150){
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
void Mode2::ThreadQuit(){
    ThreadFlag=false;
    this->wait(3);
    this->quit();
}
