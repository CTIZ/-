#include "mode.h"

Mode::Mode(QObject *parent) :
    QThread(parent)
{
}
QString ld[4];
void Mode::run(){
    ThreadFlag=true;
    while(ThreadFlag){
        QSqlQuery q;
        q.exec("select * from ld");
        while(q.next()){
            ld[0]=q.value(1).toString().mid(0,2);
            ld[1]=q.value(1).toString().mid(2,1);
            ld[2]=q.value(1).toString().mid(3);
            if(ld[0]=="温度"){
                if(ld[1]==">"){
                    if(temp_value>ld[2].toInt()){
                        if(air_state!=SWITCH_ON){
                            air_state=SWITCH_ON;
                            emit mod(INFRARED_SERVE,SWITCH_ON,1,ld[2]);
                            msleep(500);
                        }
                    }else if(temp_value<ld[2].toInt()){
                        if(air_state!=SWITCH_OFF){
                            air_state=SWITCH_OFF;
                            emit mod(INFRARED_SERVE,SWITCH_ON,1,ld[2]);
                            msleep(500);
                        }
                    }
                }
            }else if(ld[0]=="烟雾"){
                if(ld[1]==">"){
                    if(smoke_value>ld[2].toInt()){
                        if(fan_state!=SWITCH_ON){
                            emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL,ld[2]);
                            msleep(500);
                        }
                    }else if(smoke_value<ld[2].toInt()){
                        if(fan_state!=SWITCH_OFF){
                            emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL,ld[2]);
                            msleep(500);
                        }
                    }
                }
            }else if(ld[0]=="光照"){
                if(ld[1]==">"){
                    if(ill_value>ld[2].toInt()){
                        if(curtain_state!=CHANNEL_3){
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_3,ld[2]);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL,ld[2]);
                            msleep(500);
                        }
                    }else if(ill_value<ld[2].toInt()){
                        if(curtain_state!=CHANNEL_1){
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1,ld[2]);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL,ld[2]);
                            msleep(500);
                        }
                    }
                }
            }
        }
        sleep(1);
    }
}
void Mode::ThreadQuit(){
    ThreadFlag=false;
    this->wait(1);
    this->quit();
}
