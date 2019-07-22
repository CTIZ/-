#include "mode5.h"

Mode5::Mode5(QObject *parent) :
    QThread(parent)
{
}

void Mode5::run(){
    ThreadFlag=false;
    QSqlQuery q;
    q.exec("select * from ld");
    int num=0;
    QString ld[4];
    while(q.next()){
        if(q.value(4).ToInt()>num){
            num=q.value(4).ToInt();
            ld[0]=q.value(0);
            ld[1]=q.value(1);
            ld[2]=q.value(2);
            ld[3]=q.value(3);
        }
    }
    while(1){
        if(ld[0]=="光照"){
            if(ld[1]=="<"){
                if(ill_value<ld[2].toInt()){
                    if(ld[3]=="开报警灯"){//报警灯
                        if(warning_state!=SWITCH_ON){
                            mySql("开报警灯");
                            emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else if(ld[3]=="关报警灯"){
                        if(warning_state!=SWITCH_OFF){
                            mySql("关报警灯");
                            emit mod(WL_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(ld[3]=="开风扇"){//风扇
                        if(fan_state!=SWITCH_ON){
                            mySql("开风扇");
                            emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else if(ld[3]=="关风扇"){
                        if(fan_state!=SWITCH_OFF){
                            mySql("关风扇");
                            emit mod(FAN_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(ld[3]=="开窗帘"){//窗帘
                        if(curtain_state!=CHANNEL_1){
                            mySql("开窗帘");
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else if(ld[3]=="关窗帘"){
                        if(curtain_state!=CHANNEL_3){
                            mySql("关窗帘");
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_3);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(ld[3]=="开射灯"){//射灯
                        if(lamp_state!=SWITCH_ON){
                            mySql("开射灯");
                            emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else if(ld[3]=="关射灯"){
                        if(lamp_state!=SWITCH_OFF){
                            mySql("关射灯");
                            emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                }
            }else if(ld[1]==">="){
                if(ill_value>=ld[2].toInt()){
                    if(ld[3]=="开报警灯"){//报警灯
                        if(warning_state!=SWITCH_ON){
                            mySql("开报警灯");
                            emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else if(ld[3]=="关报警灯"){
                        if(warning_state!=SWITCH_OFF){
                            mySql("关报警灯");
                            emit mod(WL_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(ld[3]=="开风扇"){//风扇
                        if(fan_state!=SWITCH_ON){
                            mySql("开风扇");
                            emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else if(ld[3]=="关风扇"){
                        if(fan_state!=SWITCH_OFF){
                            mySql("关风扇");
                            emit mod(FAN_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(ld[3]=="开窗帘"){//窗帘
                        if(curtain_state!=CHANNEL_1){
                            mySql("开窗帘");
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else if(ld[3]=="关窗帘"){
                        if(curtain_state!=CHANNEL_3){
                            mySql("关窗帘");
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_3);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(ld[3]=="开射灯"){//射灯
                        if(lamp_state!=SWITCH_ON){
                            mySql("开射灯");
                            emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else if(ld[3]=="关射灯"){
                        if(lamp_state!=SWITCH_OFF){
                            mySql("关射灯");
                            emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                }
            }
        }else if(ld[0]=="温度"){
            if(ld[1]=="<"){
                if(temp_value<ld[2].toInt()){
                    if(ld[3]=="开报警灯"){//报警灯
                        if(warning_state!=SWITCH_ON){
                            mySql("开报警灯");
                            emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else if(ld[3]=="关报警灯"){
                        if(warning_state!=SWITCH_OFF){
                            mySql("关报警灯");
                            emit mod(WL_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(ld[3]=="开风扇"){//风扇
                        if(fan_state!=SWITCH_ON){
                            mySql("开风扇");
                            emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else if(ld[3]=="关风扇"){
                        if(fan_state!=SWITCH_OFF){
                            mySql("关风扇");
                            emit mod(FAN_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(ld[3]=="开窗帘"){//窗帘
                        if(curtain_state!=CHANNEL_1){
                            mySql("开窗帘");
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else if(ld[3]=="关窗帘"){
                        if(curtain_state!=CHANNEL_3){
                            mySql("关窗帘");
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_3);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(ld[3]=="开射灯"){//射灯
                        if(lamp_state!=SWITCH_ON){
                            mySql("开射灯");
                            emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else if(ld[3]=="关射灯"){
                        if(lamp_state!=SWITCH_OFF){
                            mySql("关射灯");
                            emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                }
            }else if(ld[1]==">="){
                if(temp_value>=ld[2].toInt()){
                    if(ld[3]=="开报警灯"){//报警灯
                        if(warning_state!=SWITCH_ON){
                            mySql("开报警灯");
                            emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else if(ld[3]=="关报警灯"){
                        if(warning_state!=SWITCH_OFF){
                            mySql("关报警灯");
                            emit mod(WL_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(ld[3]=="开风扇"){//风扇
                        if(fan_state!=SWITCH_ON){
                            mySql("开风扇");
                            emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else if(ld[3]=="关风扇"){
                        if(fan_state!=SWITCH_OFF){
                            mySql("关风扇");
                            emit mod(FAN_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(ld[3]=="开窗帘"){//窗帘
                        if(curtain_state!=CHANNEL_1){
                            mySql("开窗帘");
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else if(ld[3]=="关窗帘"){
                        if(curtain_state!=CHANNEL_3){
                            mySql("关窗帘");
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_3);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(ld[3]=="开射灯"){//射灯
                        if(lamp_state!=SWITCH_ON){
                            mySql("开射灯");
                            emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else if(ld[3]=="关射灯"){
                        if(lamp_state!=SWITCH_OFF){
                            mySql("关射灯");
                            emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                }
            }
        }else if(ld[0]=="PM2.5"){
            if(ld[1]=="<"){
                if(pm_value<ld[2].toInt()){
                    if(ld[3]=="开报警灯"){//报警灯
                        if(warning_state!=SWITCH_ON){
                            mySql("开报警灯");
                            emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else if(ld[3]=="关报警灯"){
                        if(warning_state!=SWITCH_OFF){
                            mySql("关报警灯");
                            emit mod(WL_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(ld[3]=="开风扇"){//风扇
                        if(fan_state!=SWITCH_ON){
                            mySql("开风扇");
                            emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else if(ld[3]=="关风扇"){
                        if(fan_state!=SWITCH_OFF){
                            mySql("关风扇");
                            emit mod(FAN_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(ld[3]=="开窗帘"){//窗帘
                        if(curtain_state!=CHANNEL_1){
                            mySql("开窗帘");
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else if(ld[3]=="关窗帘"){
                        if(curtain_state!=CHANNEL_3){
                            mySql("关窗帘");
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_3);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(ld[3]=="开射灯"){//射灯
                        if(lamp_state!=SWITCH_ON){
                            mySql("开射灯");
                            emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else if(ld[3]=="关射灯"){
                        if(lamp_state!=SWITCH_OFF){
                            mySql("关射灯");
                            emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                }
            }else if(ld[1]==">="){
                if(pm_value>=ld[2].toInt()){
                    if(ld[3]=="开报警灯"){//报警灯
                        if(warning_state!=SWITCH_ON){
                            mySql("开报警灯");
                            emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else if(ld[3]=="关报警灯"){
                        if(warning_state!=SWITCH_OFF){
                            mySql("关报警灯");
                            emit mod(WL_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(ld[3]=="开风扇"){//风扇
                        if(fan_state!=SWITCH_ON){
                            mySql("开风扇");
                            emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else if(ld[3]=="关风扇"){
                        if(fan_state!=SWITCH_OFF){
                            mySql("关风扇");
                            emit mod(FAN_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(ld[3]=="开窗帘"){//窗帘
                        if(curtain_state!=CHANNEL_1){
                            mySql("开窗帘");
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else if(ld[3]=="关窗帘"){
                        if(curtain_state!=CHANNEL_3){
                            mySql("关窗帘");
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_3);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(ld[3]=="开射灯"){//射灯
                        if(lamp_state!=SWITCH_ON){
                            mySql("开射灯");
                            emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else if(ld[3]=="关射灯"){
                        if(lamp_state!=SWITCH_OFF){
                            mySql("关射灯");
                            emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                }
            }
        }
        if(ThreadFlag)
            break;
        sleep(3);
    }
}
void Mode5::ThreadQuit(){
    ThreadFlag=true;
    this->wait(3);
    this->quit();
}
