#include "mode3.h"

Mode3::Mode3(QObject *parent) :
    QThread(parent)
{
}
void Mode3::run(){
    ThreadFlag=false;
    while(1){
        if(human_state==1){
            if(warning_state!=SWITCH_ON){
                emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                msleep(500);
            }
            if(lamp_state!=SWITCH_ON){
                emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
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
