#include "mode3.h"

Mode3::Mode3(QObject *parent) :
    QThread(parent)
{
}
void Mode3::run(){
    ThreadFlag=false;
    while(1){
        switch(ld[0]){
        case 0://温度
            switch(ld[1]){
            case 0://>
                if(temp_value>ld[2]){
                    switch(ld[3]){
                    case 0://风扇
                        switch(ld[4]){
                        case 0://开
                            if(fan_state!=SWITCH_ON){
                                emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(fan_state!=SWITCH_OFF){
                                emit mod(FAN_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }

                        break;
                    case 1://报警灯
                        switch(ld[4]){
                        case 0://开
                            if(warning_state!=SWITCH_ON){
                                emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(warning_state!=SWITCH_OFF){
                                emit mod(WL_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 2://射灯
                        switch(ld[4]){
                        case 0://开
                            if(lamp_state!=SWITCH_ON){
                                emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(lamp_state!=SWITCH_OFF){
                                emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 3://门禁
                        switch(ld[4]){
                        case 0://开
                            if(rfid_state!=SWITCH_ON){
                                emit mod(DC_SERVE,SWITCH_ON,CHANNEL_1);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(rfid_state!=SWITCH_OFF){
                                emit mod(DC_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 4://窗帘
                        switch(ld[4]){
                        case 0://开
                            if(curtain_state!=CHANNEL_1){
                                emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
                                msleep(500);
                                emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(curtain_state!=CHANNEL_3){
                                emit mod(CT_SERVE,SWITCH_ON,CHANNEL_3);
                                msleep(500);
                                emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    }
                }
                break;
            case 1://<
                if(temp_value<ld[2]){
                    switch(ld[3]){
                    case 0://风扇
                        switch(ld[4]){
                        case 0://开
                            if(fan_state!=SWITCH_ON){
                                emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(fan_state!=SWITCH_OFF){
                                emit mod(FAN_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }

                        break;
                    case 1://报警灯
                        switch(ld[4]){
                        case 0://开
                            if(warning_state!=SWITCH_ON){
                                emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(warning_state!=SWITCH_OFF){
                                emit mod(WL_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 2://射灯
                        switch(ld[4]){
                        case 0://开
                            if(lamp_state!=SWITCH_ON){
                                emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(lamp_state!=SWITCH_OFF){
                                emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 3://门禁
                        switch(ld[4]){
                        case 0://开
                            if(rfid_state!=SWITCH_ON){
                                emit mod(DC_SERVE,SWITCH_ON,CHANNEL_1);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(rfid_state!=SWITCH_OFF){
                                emit mod(DC_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 4://窗帘
                        switch(ld[4]){
                        case 0://开
                            if(curtain_state!=CHANNEL_1){
                                emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
                                msleep(500);
                                emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(curtain_state!=CHANNEL_3){
                                emit mod(CT_SERVE,SWITCH_ON,CHANNEL_3);
                                msleep(500);
                                emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    }
                }
                break;
            }

            break;
        case 1://光照
            switch(ld[1]){
            case 0://>
                if(ill_value>ld[2]){
                    switch(ld[3]){
                    case 0://风扇
                        switch(ld[4]){
                        case 0://开
                            if(fan_state!=SWITCH_ON){
                                emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(fan_state!=SWITCH_OFF){
                                emit mod(FAN_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }

                        break;
                    case 1://报警灯
                        switch(ld[4]){
                        case 0://开
                            if(warning_state!=SWITCH_ON){
                                emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(warning_state!=SWITCH_OFF){
                                emit mod(WL_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 2://射灯
                        switch(ld[4]){
                        case 0://开
                            if(lamp_state!=SWITCH_ON){
                                emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(lamp_state!=SWITCH_OFF){
                                emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 3://门禁
                        switch(ld[4]){
                        case 0://开
                            if(rfid_state!=SWITCH_ON){
                                emit mod(DC_SERVE,SWITCH_ON,CHANNEL_1);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(rfid_state!=SWITCH_OFF){
                                emit mod(DC_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 4://窗帘
                        switch(ld[4]){
                        case 0://开
                            if(curtain_state!=CHANNEL_1){
                                emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
                                msleep(500);
                                emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(curtain_state!=CHANNEL_3){
                                emit mod(CT_SERVE,SWITCH_ON,CHANNEL_3);
                                msleep(500);
                                emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    }
                }
                break;
            case 1://<
                if(ill_value<ld[2]){
                    switch(ld[3]){
                    case 0://风扇
                        switch(ld[4]){
                        case 0://开
                            if(fan_state!=SWITCH_ON){
                                emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(fan_state!=SWITCH_OFF){
                                emit mod(FAN_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }

                        break;
                    case 1://报警灯
                        switch(ld[4]){
                        case 0://开
                            if(warning_state!=SWITCH_ON){
                                emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(warning_state!=SWITCH_OFF){
                                emit mod(WL_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 2://射灯
                        switch(ld[4]){
                        case 0://开
                            if(lamp_state!=SWITCH_ON){
                                emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(lamp_state!=SWITCH_OFF){
                                emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 3://门禁
                        switch(ld[4]){
                        case 0://开
                            if(rfid_state!=SWITCH_ON){
                                emit mod(DC_SERVE,SWITCH_ON,CHANNEL_1);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(rfid_state!=SWITCH_OFF){
                                emit mod(DC_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 4://窗帘
                        switch(ld[4]){
                        case 0://开
                            if(curtain_state!=CHANNEL_1){
                                emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
                                msleep(500);
                                emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(curtain_state!=CHANNEL_3){
                                emit mod(CT_SERVE,SWITCH_ON,CHANNEL_3);
                                msleep(500);
                                emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    }
                }
                break;
            }
            break;
        case 2://湿度
            switch(ld[1]){
            case 0://>
                if(hum_value>ld[2]){
                    switch(ld[3]){
                    case 0://风扇
                        switch(ld[4]){
                        case 0://开
                            if(fan_state!=SWITCH_ON){
                                emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(fan_state!=SWITCH_OFF){
                                emit mod(FAN_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }

                        break;
                    case 1://报警灯
                        switch(ld[4]){
                        case 0://开
                            if(warning_state!=SWITCH_ON){
                                emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(warning_state!=SWITCH_OFF){
                                emit mod(WL_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 2://射灯
                        switch(ld[4]){
                        case 0://开
                            if(lamp_state!=SWITCH_ON){
                                emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(lamp_state!=SWITCH_OFF){
                                emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 3://门禁
                        switch(ld[4]){
                        case 0://开
                            if(rfid_state!=SWITCH_ON){
                                emit mod(DC_SERVE,SWITCH_ON,CHANNEL_1);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(rfid_state!=SWITCH_OFF){
                                emit mod(DC_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 4://窗帘
                        switch(ld[4]){
                        case 0://开
                            if(curtain_state!=CHANNEL_1){
                                emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
                                msleep(500);
                                emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(curtain_state!=CHANNEL_3){
                                emit mod(CT_SERVE,SWITCH_ON,CHANNEL_3);
                                msleep(500);
                                emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    }
                }
                break;
            case 1://<
                if(hum_value<ld[2]){
                    switch(ld[3]){
                    case 0://风扇
                        switch(ld[4]){
                        case 0://开
                            if(fan_state!=SWITCH_ON){
                                emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(fan_state!=SWITCH_OFF){
                                emit mod(FAN_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }

                        break;
                    case 1://报警灯
                        switch(ld[4]){
                        case 0://开
                            if(warning_state!=SWITCH_ON){
                                emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(warning_state!=SWITCH_OFF){
                                emit mod(WL_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 2://射灯
                        switch(ld[4]){
                        case 0://开
                            if(lamp_state!=SWITCH_ON){
                                emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(lamp_state!=SWITCH_OFF){
                                emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 3://门禁
                        switch(ld[4]){
                        case 0://开
                            if(rfid_state!=SWITCH_ON){
                                emit mod(DC_SERVE,SWITCH_ON,CHANNEL_1);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(rfid_state!=SWITCH_OFF){
                                emit mod(DC_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 4://窗帘
                        switch(ld[4]){
                        case 0://开
                            if(curtain_state!=CHANNEL_1){
                                emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
                                msleep(500);
                                emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(curtain_state!=CHANNEL_3){
                                emit mod(CT_SERVE,SWITCH_ON,CHANNEL_3);
                                msleep(500);
                                emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
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
