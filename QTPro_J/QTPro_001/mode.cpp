#include "mode.h"

Mode::Mode(QObject *parent) :
    QThread(parent)
{
}
void Mode::run(){
    ThreadFlag=false;
    while(1){
        switch(Modes){
        case 0://模式1
            switch(ld1[0]){
            case 0://温度
                switch(ld1[1]){
                case 0://>
                    if(temp_value>ld1[2]){
                        switch(ld1[3]){
                        case 0://报警灯
                            switch(ld1[4]){
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
                        case 1://风扇
                            switch(ld1[4]){
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
                        case 2://射灯
                            switch(ld1[4]){
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
                        case 3://窗帘
                            switch(ld1[4]){
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
                    if(temp_value<ld1[2]){
                        switch(ld1[3]){
                        case 0://报警灯
                            switch(ld1[4]){
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
                        case 1://风扇
                            switch(ld1[4]){
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
                        case 2://射灯
                            switch(ld1[4]){
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
                        case 3://窗帘
                            switch(ld1[4]){
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
                switch(ld1[1]){
                case 0://>
                    if(ill_value>ld1[2]){
                        switch(ld1[3]){
                        case 0://报警灯
                            switch(ld1[4]){
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
                        case 1://风扇
                            switch(ld1[4]){
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
                        case 2://射灯
                            switch(ld1[4]){
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
                        case 3://窗帘
                            switch(ld1[4]){
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
                    if(ill_value<ld1[2]){
                        switch(ld1[3]){
                        case 0://报警灯
                            switch(ld1[4]){
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
                        case 1://风扇
                            switch(ld1[4]){
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
                        case 2://射灯
                            switch(ld1[4]){
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
                        case 3://窗帘
                            switch(ld1[4]){
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

            break;
        case 1://模式2
            switch(ld2[0]){
            case 0://温度
                switch(ld2[1]){
                case 0://>
                    if(temp_value>ld2[2]){
                        switch(ld2[3]){
                        case 0://报警灯
                            switch(ld2[4]){
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
                        case 1://风扇
                            switch(ld2[4]){
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
                        case 2://射灯
                            switch(ld2[4]){
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
                        case 3://窗帘
                            switch(ld2[4]){
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
                    if(temp_value<ld2[2]){
                        switch(ld2[3]){
                        case 0://报警灯
                            switch(ld2[4]){
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
                        case 1://风扇
                            switch(ld2[4]){
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
                        case 2://射灯
                            switch(ld2[4]){
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
                        case 3://窗帘
                            switch(ld2[4]){
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
                switch(ld2[1]){
                case 0://>
                    if(ill_value>ld2[2]){
                        switch(ld2[3]){
                        case 0://报警灯
                            switch(ld2[4]){
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
                        case 1://风扇
                            switch(ld2[4]){
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
                        case 2://射灯
                            switch(ld2[4]){
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
                        case 3://窗帘
                            switch(ld2[4]){
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
                    if(ill_value<ld2[2]){
                        switch(ld2[3]){
                        case 0://报警灯
                            switch(ld2[4]){
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
                        case 1://风扇
                            switch(ld2[4]){
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
                        case 2://射灯
                            switch(ld2[4]){
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
                        case 3://窗帘
                            switch(ld2[4]){
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

            break;
        case 2://模式3
            switch(ld3[0]){
            case 0://温度
                switch(ld3[1]){
                case 0://>
                    if(temp_value>ld3[2]){
                        switch(ld3[3]){
                        case 0://报警灯
                            switch(ld3[4]){
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
                        case 1://风扇
                            switch(ld3[4]){
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
                        case 2://射灯
                            switch(ld3[4]){
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
                        case 3://窗帘
                            switch(ld3[4]){
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
                    if(temp_value<ld3[2]){
                        switch(ld3[3]){
                        case 0://报警灯
                            switch(ld3[4]){
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
                        case 1://风扇
                            switch(ld3[4]){
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
                        case 2://射灯
                            switch(ld3[4]){
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
                        case 3://窗帘
                            switch(ld3[4]){
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
                switch(ld3[1]){
                case 0://>
                    if(ill_value>ld3[2]){
                        switch(ld3[3]){
                        case 0://报警灯
                            switch(ld3[4]){
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
                        case 1://风扇
                            switch(ld3[4]){
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
                        case 2://射灯
                            switch(ld3[4]){
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
                        case 3://窗帘
                            switch(ld3[4]){
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
                    if(ill_value<ld3[2]){
                        switch(ld3[3]){
                        case 0://报警灯
                            switch(ld3[4]){
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
                        case 1://风扇
                            switch(ld3[4]){
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
                        case 2://射灯
                            switch(ld3[4]){
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
                        case 3://窗帘
                            switch(ld3[4]){
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

            break;
        case 3://模式4
            switch(ld4[0]){
            case 0://温度
                switch(ld4[1]){
                case 0://>
                    if(temp_value>ld4[2]){
                        switch(ld4[3]){
                        case 0://报警灯
                            switch(ld4[4]){
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
                        case 1://风扇
                            switch(ld4[4]){
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
                        case 2://射灯
                            switch(ld4[4]){
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
                        case 3://窗帘
                            switch(ld4[4]){
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
                    if(temp_value<ld4[2]){
                        switch(ld4[3]){
                        case 0://报警灯
                            switch(ld4[4]){
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
                        case 1://风扇
                            switch(ld4[4]){
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
                        case 2://射灯
                            switch(ld4[4]){
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
                        case 3://窗帘
                            switch(ld4[4]){
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
                switch(ld4[1]){
                case 0://>
                    if(ill_value>ld4[2]){
                        switch(ld4[3]){
                        case 0://报警灯
                            switch(ld4[4]){
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
                        case 1://风扇
                            switch(ld4[4]){
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
                        case 2://射灯
                            switch(ld4[4]){
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
                        case 3://窗帘
                            switch(ld4[4]){
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
                    if(ill_value<ld4[2]){
                        switch(ld4[3]){
                        case 0://报警灯
                            switch(ld4[4]){
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
                        case 1://风扇
                            switch(ld4[4]){
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
                        case 2://射灯
                            switch(ld4[4]){
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
                        case 3://窗帘
                            switch(ld4[4]){
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

            break;
        }
        if(ThreadFlag)
            break;
        sleep(3);
    }
}

void Mode::ThreadQuit(){
    ThreadFlag=true;
    this->wait(3);
    this->quit();
}
