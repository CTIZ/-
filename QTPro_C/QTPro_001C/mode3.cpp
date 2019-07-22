#include "mode3.h"

Mode3::Mode3(QObject *parent) :
    QThread(parent)
{
}
void Mode3::run(){
    ThreadFlag=false;
    if(lamp1_state!=SWITCH_OFF||lamp2_state!=SWITCH_OFF){
        emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
        msleep(500);
    }
    while(1){
        if(smoke_value>310){
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
        if(ThreadFlag)
            break;
        sleep(3);
    }
}
void Mode3::ThreadQuit(){
    ThreadFlag=true;
    this->wait(3);
    this->quit();
}
