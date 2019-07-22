#include "mode2.h"

Mode2::Mode2(QObject *parent) :
    QThread(parent)
{
}
void Mode2::run(){
    ThreadFlag=false;
    if(lamp1_state!=SWITCH_OFF||lamp2_state!=SWITCH_OFF){
        emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
        msleep(500);
    }
    while(1){
        if(temp_value<20){
            if(air_state!=SWITCH_ON){
                air_state=SWITCH_ON;
                emit mod(INFRARED_SERVE,SWITCH_ON,5);
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
