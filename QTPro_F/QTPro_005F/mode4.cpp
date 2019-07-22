#include "mode4.h"

Mode4::Mode4(QObject *parent) :
    QThread(parent)
{
}
void Mode4::run(){
    ThreadFlag=true;
    while(ThreadFlag){
        if(human_state==1){
            if(lamp1_state!=SWITCH_ON||lamp2_state!=SWITCH_ON){
                emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                msleep(500);
            }
            if(lamp1_state!=SWITCH_OFF||lamp2_state!=SWITCH_OFF){
                emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
                msleep(500);
            }
            if(warning_state!=SWITCH_ON){
                emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                msleep(500);
            }
        }else{
            if(lamp1_state!=SWITCH_OFF||lamp2_state!=SWITCH_OFF){
                emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
                msleep(500);
            }
            if(warning_state!=SWITCH_OFF){
                emit mod(WL_SERVE,SWITCH_OFF,CHANNEL_ALL);
                msleep(500);
            }
        }
    }
}
void Mode4::ThreadQuit(){
    ThreadFlag=false;
    this->wait(1);
    this->quit();
}
