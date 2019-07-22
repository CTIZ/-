#include "mode1.h"

Mode1::Mode1(QObject *parent) :
    QThread(parent)
{
}
void Mode1::run(){
    ThreadFlag=false;
    if(lamp1_state!=SWITCH_OFF||lamp2_state!=SWITCH_OFF){
        emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
        msleep(500);
    }
    if(warning_state!=SWITCH_OFF){
        emit mod(WL_SERVE,SWITCH_OFF,CHANNEL_ALL);
        msleep(500);
    }
    while(1){
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
