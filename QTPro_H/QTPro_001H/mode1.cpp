#include "mode1.h"

Mode1::Mode1(QObject *parent) :
    QThread(parent)
{
}
void Mode1::run(){
    ThreadFlag=false;
    //单次执行
    if(lamp1_state!=SWITCH_OFF||lamp2_state!=SWITCH_OFF){
        emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
        msleep(500);
    }
    //循环判断
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
        //符合条件，跳出while死循环
        if(ThreadFlag)
            break;
        //线程睡眠3秒
        sleep(3);
    }
}
void Mode1::ThreadQuit(){
    ThreadFlag=true;
    this->wait(3);
    this->quit();
}
