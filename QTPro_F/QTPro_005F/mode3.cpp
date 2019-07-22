#include "mode3.h"

Mode3::Mode3(QObject *parent) :
    QThread(parent)
{
}
void Mode3::run(){
    ThreadFlag=true;
    if(lamp1_state!=SWITCH_OFF||lamp2_state!=SWITCH_OFF){
        emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
        msleep(500);
    }
    if(curtain_state!=CHANNEL_3){
        emit mod(CT_SERVE,SWITCH_ON,CHANNEL_3);
        msleep(500);
        emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
        msleep(500);
    }
    if(dvd_state!=SWITCH_OFF){
        dvd_state=SWITCH_OFF;
        emit mod(INFRARED_SERVE,SWITCH_ON,3);
        msleep(500);
    }
    if(tv_state!=SWITCH_OFF){
        tv_state=SWITCH_OFF;
        emit mod(INFRARED_SERVE,SWITCH_ON,2);
        msleep(500);
    }
    if(air_state!=SWITCH_OFF){
        air_state=SWITCH_OFF;
        emit mod(INFRARED_SERVE,SWITCH_ON,1);
        msleep(500);
    }
    while(ThreadFlag){
        sleep(3);
    }
}
void Mode3::ThreadQuit(){
    ThreadFlag=false;
    this->wait(3);
    this->quit();
}
