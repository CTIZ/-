#include "mode5.h"

Mode5::Mode5(QObject *parent) :
    QThread(parent)
{
}
void Mode5::run(){
    ThreadFlag=true;
    while(ThreadFlag){
        switch(ld[0]){
        case 0://温度
            switch(ld[1]){
            case 0://>
                if(temp_value>ld[2]){
                    switch(ld[3]){
                    case 0://报警灯
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
                    case 1://射灯
                        switch(ld[4]){
                        case 0://开
                            if(lamp1_state!=SWITCH_ON||lamp2_state!=SWITCH_ON){
                                emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(lamp1_state!=SWITCH_OFF||lamp2_state!=SWITCH_OFF){
                                emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 2://门禁
                        switch(ld[4]){
                        case 0://开
                            if(rfid_state!=SWITCH_ON){
                                emit mod(DC_SERVE,SWITCH_ON,CHANNEL_1);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(rfid_state!=SWITCH_OFF){
                                emit mod(DC_SERVE,SWITCH_OFF,CHANNEL_1);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 3://换气扇
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
                    }
                }
                break;
            case 1://<
                if(temp_value<ld[2]){
                    switch(ld[3]){
                    case 0://报警灯
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
                    case 1://射灯
                        switch(ld[4]){
                        case 0://开
                            if(lamp1_state!=SWITCH_ON||lamp2_state!=SWITCH_ON){
                                emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(lamp1_state!=SWITCH_OFF||lamp2_state!=SWITCH_OFF){
                                emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 2://门禁
                        switch(ld[4]){
                        case 0://开
                            if(rfid_state!=SWITCH_ON){
                                emit mod(DC_SERVE,SWITCH_ON,CHANNEL_1);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(rfid_state!=SWITCH_OFF){
                                emit mod(DC_SERVE,SWITCH_OFF,CHANNEL_1);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 3://换气扇
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
                    }
                }
                break;
            }

            break;
        case 1://光照度
            switch(ld[1]){
            case 0://>
                if(ill_value>ld[2]){
                    switch(ld[3]){
                    case 0://报警灯
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
                    case 1://射灯
                        switch(ld[4]){
                        case 0://开
                            if(lamp1_state!=SWITCH_ON||lamp2_state!=SWITCH_ON){
                                emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(lamp1_state!=SWITCH_OFF||lamp2_state!=SWITCH_OFF){
                                emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 2://门禁
                        switch(ld[4]){
                        case 0://开
                            if(rfid_state!=SWITCH_ON){
                                emit mod(DC_SERVE,SWITCH_ON,CHANNEL_1);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(rfid_state!=SWITCH_OFF){
                                emit mod(DC_SERVE,SWITCH_OFF,CHANNEL_1);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 3://换气扇
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
                    }
                }
                break;
            case 1://<
                if(ill_value<ld[2]){
                    switch(ld[3]){
                    case 0://报警灯
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
                    case 1://射灯
                        switch(ld[4]){
                        case 0://开
                            if(lamp1_state!=SWITCH_ON||lamp2_state!=SWITCH_ON){
                                emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(lamp1_state!=SWITCH_OFF||lamp2_state!=SWITCH_OFF){
                                emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 2://门禁
                        switch(ld[4]){
                        case 0://开
                            if(rfid_state!=SWITCH_ON){
                                emit mod(DC_SERVE,SWITCH_ON,CHANNEL_1);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(rfid_state!=SWITCH_OFF){
                                emit mod(DC_SERVE,SWITCH_OFF,CHANNEL_1);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 3://换气扇
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
                    case 0://报警灯
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
                    case 1://射灯
                        switch(ld[4]){
                        case 0://开
                            if(lamp1_state!=SWITCH_ON||lamp2_state!=SWITCH_ON){
                                emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(lamp1_state!=SWITCH_OFF||lamp2_state!=SWITCH_OFF){
                                emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 2://门禁
                        switch(ld[4]){
                        case 0://开
                            if(rfid_state!=SWITCH_ON){
                                emit mod(DC_SERVE,SWITCH_ON,CHANNEL_1);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(rfid_state!=SWITCH_OFF){
                                emit mod(DC_SERVE,SWITCH_OFF,CHANNEL_1);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 3://换气扇
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
                    }
                }
                break;
            case 1://<
                if(hum_value<ld[2]){
                    switch(ld[3]){
                    case 0://报警灯
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
                    case 1://射灯
                        switch(ld[4]){
                        case 0://开
                            if(lamp1_state!=SWITCH_ON||lamp2_state!=SWITCH_ON){
                                emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(lamp1_state!=SWITCH_OFF||lamp2_state!=SWITCH_OFF){
                                emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 2://门禁
                        switch(ld[4]){
                        case 0://开
                            if(rfid_state!=SWITCH_ON){
                                emit mod(DC_SERVE,SWITCH_ON,CHANNEL_1);
                                msleep(500);
                            }
                            break;
                        case 1://关
                            if(rfid_state!=SWITCH_OFF){
                                emit mod(DC_SERVE,SWITCH_OFF,CHANNEL_1);
                                msleep(500);
                            }
                            break;
                        }
                        break;
                    case 3://换气扇
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
                    }
                }
                break;
            }
            break;
        }
        sleep(3);
    }
}
void Mode5::ThreadQuit(){
    ThreadFlag=false;
    this->wait(3);
    this->quit();
}
