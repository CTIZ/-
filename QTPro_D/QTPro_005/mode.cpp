#include "mode.h"

Mode::Mode(QObject *parent) :
    QThread(parent)
{
}
void Mode::run(){
    ThreadFlag=true;
    while(ThreadFlag){
        switch(ld[0]){
        case 0://温度
            switch(ld[1]){
            case 0://>
                if(temp_value>ld[2]){
                    switch(ld[3]){
                    case 0://打开
                        if(chk[0]){//电视
                            if(tv_state!=SWITCH_ON){
                                tv_state=SWITCH_ON;
                                emit mod(INFRARED_SERVE,SWITCH_ON,5);
                                msleep(500);
                            }
                        }
                        if(chk[1]){//DVD
                            if(dvd_state!=SWITCH_ON){
                                dvd_state=SWITCH_ON;
                                emit mod(INFRARED_SERVE,SWITCH_ON,11);
                                msleep(500);
                            }
                        }
                        if(chk[3]){//空调
                            if(air_state!=SWITCH_ON){
                                air_state=SWITCH_ON;
                                emit mod(INFRARED_SERVE,SWITCH_ON,1);
                                msleep(500);
                            }
                        }
                        if(chk[4]){//门禁
                            if(rfid_state!=SWITCH_ON){
                                emit mod(DC_SERVE,SWITCH_ON,CHANNEL_1);
                                msleep(500);
                            }
                        }
                        if(chk[5]){//风扇
                            if(fan_state!=SWITCH_ON){
                                emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                        }
                        if(chk[7]){//报警灯
                            if(warning_state!=SWITCH_ON){
                                emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                        }
                        if(chk[8]){//射灯
                            if(lamp_state!=SWITCH_ON){
                                emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                        }
                        if(chk[9]){//窗帘
                            if(curtain_state!=CHANNEL_1){
                                emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
                                msleep(500);
                                emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                        }
                        break;
                    case 1://关闭
                        if(chk[0]){//电视
                            if(tv_state!=SWITCH_OFF){
                                tv_state=SWITCH_OFF;
                                emit mod(INFRARED_SERVE,SWITCH_ON,5);
                                msleep(500);
                            }
                        }
                        if(chk[1]){//DVD
                            if(dvd_state!=SWITCH_OFF){
                                dvd_state=SWITCH_OFF;
                                emit mod(INFRARED_SERVE,SWITCH_ON,11);
                                msleep(500);
                            }
                        }
                        if(chk[3]){//空调
                            if(air_state!=SWITCH_OFF){
                                air_state=SWITCH_OFF;
                                emit mod(INFRARED_SERVE,SWITCH_ON,1);
                                msleep(500);
                            }
                        }
                        if(chk[4]){//门禁
                            if(rfid_state!=SWITCH_OFF){
                                emit mod(DC_SERVE,SWITCH_OFF,CHANNEL_1);
                                msleep(500);
                            }
                        }
                        if(chk[5]){//风扇
                            if(fan_state!=SWITCH_OFF){
                                emit mod(FAN_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                        }
                        if(chk[7]){//报警灯
                            if(warning_state!=SWITCH_OFF){
                                emit mod(WL_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                        }
                        if(chk[8]){//射灯
                            if(lamp_state!=SWITCH_OFF){
                                emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                        }
                        if(chk[9]){//窗帘
                            if(curtain_state!=CHANNEL_3){
                                emit mod(CT_SERVE,SWITCH_ON,CHANNEL_3);
                                msleep(500);
                                emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                        }
                        break;
                    }
                }
                break;
            case 1://<
                if(temp_value<ld[2]){
                    switch(ld[3]){
                    case 0://打开
                        if(chk[0]){//电视
                            if(tv_state!=SWITCH_ON){
                                tv_state=SWITCH_ON;
                                emit mod(INFRARED_SERVE,SWITCH_ON,5);
                                msleep(500);
                            }
                        }
                        if(chk[1]){//DVD
                            if(dvd_state!=SWITCH_ON){
                                dvd_state=SWITCH_ON;
                                emit mod(INFRARED_SERVE,SWITCH_ON,11);
                                msleep(500);
                            }
                        }
                        if(chk[3]){//空调
                            if(air_state!=SWITCH_ON){
                                air_state=SWITCH_ON;
                                emit mod(INFRARED_SERVE,SWITCH_ON,1);
                                msleep(500);
                            }
                        }
                        if(chk[4]){//门禁
                            if(rfid_state!=SWITCH_ON){
                                emit mod(DC_SERVE,SWITCH_ON,CHANNEL_1);
                                msleep(500);
                            }
                        }
                        if(chk[5]){//风扇
                            if(fan_state!=SWITCH_ON){
                                emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                        }
                        if(chk[7]){//报警灯
                            if(warning_state!=SWITCH_ON){
                                emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                        }
                        if(chk[8]){//射灯
                            if(lamp_state!=SWITCH_ON){
                                emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                        }
                        if(chk[9]){//窗帘
                            if(curtain_state!=CHANNEL_1){
                                emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
                                msleep(500);
                                emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                        }
                        break;
                    case 1://关闭
                        if(chk[0]){//电视
                            if(tv_state!=SWITCH_OFF){
                                tv_state=SWITCH_OFF;
                                emit mod(INFRARED_SERVE,SWITCH_ON,5);
                                msleep(500);
                            }
                        }
                        if(chk[1]){//DVD
                            if(dvd_state!=SWITCH_OFF){
                                dvd_state=SWITCH_OFF;
                                emit mod(INFRARED_SERVE,SWITCH_ON,11);
                                msleep(500);
                            }
                        }
                        if(chk[3]){//空调
                            if(air_state!=SWITCH_OFF){
                                air_state=SWITCH_OFF;
                                emit mod(INFRARED_SERVE,SWITCH_ON,1);
                                msleep(500);
                            }
                        }
                        if(chk[4]){//门禁
                            if(rfid_state!=SWITCH_OFF){
                                emit mod(DC_SERVE,SWITCH_OFF,CHANNEL_1);
                                msleep(500);
                            }
                        }
                        if(chk[5]){//风扇
                            if(fan_state!=SWITCH_OFF){
                                emit mod(FAN_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                        }
                        if(chk[7]){//报警灯
                            if(warning_state!=SWITCH_OFF){
                                emit mod(WL_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                        }
                        if(chk[8]){//射灯
                            if(lamp_state!=SWITCH_OFF){
                                emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                        }
                        if(chk[9]){//窗帘
                            if(curtain_state!=CHANNEL_3){
                                emit mod(CT_SERVE,SWITCH_ON,CHANNEL_3);
                                msleep(500);
                                emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                        }
                        break;
                    }
                }
                break;
            }
            break;
        }
        sleep(3);
    }
}
void Mode::ThreadQuit(){
    ThreadFlag=false;
    this->wait(3);
    this->quit();
}
