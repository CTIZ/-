#include "mode2.h"

Mode2::Mode2(QObject *parent) :
    QThread(parent)
{
}
void Mode2::run(){
    ThreadFlag=false;
    if(lamp_state!=SWITCH_ON){
        emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
        msleep(500);
    }
    while(1){
        if(ill_value>200){
            if(fan_state!=SWITCH_ON){
                emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                msleep(500);
            }
        }
        if(ill_value<150){
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
void Mode2::ThreadQuit(){
    ThreadFlag=true;
    this->wait(3);
    this->quit();
}
