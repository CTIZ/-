#include "mode3.h"

Mode3::Mode3(QObject *parent) :
    QThread(parent)
{
}
void Mode3::run(){
    ThreadFlag=false;
    while(1){
        switch(ld[0]){
        case 0://光照
            switch(ld[1]){
            case 0://<
                if(ill_value<ld[2]){
                    if(chk[0]){//报警灯
                        if(warning_state!=SWITCH_ON){
                            emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[1]){//风扇
                        if(fan_state!=SWITCH_ON){
                            emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[2]){//窗帘
                        if(curtain_state!=CHANNEL_1){
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[3]){//射灯
                        if(lamp1_state!=SWITCH_ON||lamp2_state!=SWITCH_ON){
                            emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                }
                break;
            case 1://>=
                if(ill_value>=ld[2]){
                    if(chk[0]){//报警灯
                        if(warning_state!=SWITCH_ON){
                            emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[1]){//风扇
                        if(fan_state!=SWITCH_ON){
                            emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[2]){//窗帘
                        if(curtain_state!=CHANNEL_1){
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[3]){//射灯
                        if(lamp1_state!=SWITCH_ON||lamp2_state!=SWITCH_ON){
                            emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                }
                break;
            }

            break;
        case 1://烟雾
            switch(ld[1]){
            case 0://<
                if(smoke_value<ld[2]){
                    if(chk[0]){//报警灯
                        if(warning_state!=SWITCH_ON){
                            emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[1]){//风扇
                        if(fan_state!=SWITCH_ON){
                            emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[2]){//窗帘
                        if(curtain_state!=CHANNEL_1){
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[3]){//射灯
                        if(lamp1_state!=SWITCH_ON||lamp2_state!=SWITCH_ON){
                            emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                }
                break;
            case 1://>=
                if(smoke_value>=ld[2]){
                    if(chk[0]){//报警灯
                        if(warning_state!=SWITCH_ON){
                            emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[1]){//风扇
                        if(fan_state!=SWITCH_ON){
                            emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[2]){//窗帘
                        if(curtain_state!=CHANNEL_1){
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[3]){//射灯
                        if(lamp1_state!=SWITCH_ON||lamp2_state!=SWITCH_ON){
                            emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                }
                break;
            }
            break;
        case 2://PM2.5
            switch(ld[1]){
            case 0://<
                if(pm_value<ld[2]){
                    if(chk[0]){//报警灯
                        if(warning_state!=SWITCH_ON){
                            emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[1]){//风扇
                        if(fan_state!=SWITCH_ON){
                            emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[2]){//窗帘
                        if(curtain_state!=CHANNEL_1){
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[3]){//射灯
                        if(lamp1_state!=SWITCH_ON||lamp2_state!=SWITCH_ON){
                            emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                }
                break;
            case 1://>=
                if(pm_value>=ld[2]){
                    if(chk[0]){//报警灯
                        if(warning_state!=SWITCH_ON){
                            emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[1]){//风扇
                        if(fan_state!=SWITCH_ON){
                            emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[2]){//窗帘
                        if(curtain_state!=CHANNEL_1){
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[3]){//射灯
                        if(lamp1_state!=SWITCH_ON||lamp2_state!=SWITCH_ON){
                            emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                }
                break;
            }
            break;
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
