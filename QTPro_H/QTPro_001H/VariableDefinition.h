#ifndef VARIABLEDEFINITION_H
#define VARIABLEDEFINITION_H

/******************************串口通信部分要用到的定义**************************************************/
/************************************************
设备类型定义
 ***********************************************/
#define RELAY           0XEE01          //继电器
#define BODYINFRARED    0XEE02          //人体红外
#define SMOKE           0XEE03          //烟雾
#define CO2             0XEE04          //二氧化碳
#define GAS             0XEE05          //燃气
#define PRESSURE        0XEE06          //气压
#define THI             0XEE07          //温湿度
#define ILL             0XEE08          //光照
#define PM25            0XEE09          //PM2.5
#define RFID            0XEE0A          //门禁
#define INFRARED        0XEE0B          //红外转发
/**************************************************/
/************************************************
 操作码定义
 ***********************************************/
#define CONTROL             0X06    //控制设备
#define GETSTATE            0X07    //获取状态
#define READNODE            0X0B    //读取节点
#define DEVICETEST          0XFF    //握手测试
/**************************************************/
//cmdCode 定义
#define SWITCH              0x01  //开关
#define INFRAREDSTUDY       0x02  //红外学习
#define INFRAREDEXIT        0x00  //红外退出学习
#define RFID_APP            0x01  //app开门
#define RFID_CARD           0x02  //刷卡开门
#define RFID_KEY            0x04  //外部按键开门

//cmd 定义
#define SWITCH_ON           0x01  //开
#define SWITCH_OFF          0x00  //关

//电压继电器控制开关
#define RELAY_OFF                     0x00
#define RELAY_ON                      0x07
//节点型继电器
#define CURTAIN_ON                    0x01
#define CURTAIN_STOP                  0x02
#define CURTAIN_OFF                   0x04
//门禁控制
#define OPEN_DOOR                     0x01
//红外设备控制
#define AIR_OPEN                      0x01 //开空调
#define AIR_CLOSE                     0x02 //关空调
#define TV_OPEN                       0x03 //开电视
#define TV_CLOSE                      0x04 //关电视
#define DVD_OPEN                      0x05 //开DVD
#define DVD_CLOSE                     0x06 //关DVD

//继电器设备通道定义
#define CHANNEL_1                    0x01   //通道1
#define CHANNEL_2                    0x02   //通道2
#define CHANNEL_3                    0x04   //通道3
#define CHANNEL_ALL                  0x07   //所有通道
/**************************************模式定义**********************************************/
#define ILL_MODE    0
#define TEMP_MODE   1
#define SAFE_MODE   2
#define OUT_MODE    3
#define SLEEP_MODE  4
#define WAKE_MODE   5
/*********************************与服务器通信部分定义********************************************/
#define TEMP_SERVE             "0"           //温度
#define HUM_SERVE              "1"           //湿度
#define ILL_SERVE              "2"           //光照
#define SMK_SERVE              "3"           //烟雾
#define GAS_SERVE              "4"           //燃气
#define PM25_SERVE             "5"           //PM2.5
#define CO2_SERVE              "6"           //二氧化碳
#define AP_SERVE               "7"           //气压
#define HI_SERVE               "8"           //人体红外
#define FAN_SERVE              "9"           //风扇
#define LAMP_SERVE             "10"          //射灯
#define WL_SERVE               "11"          //报警灯
#define CT_SERVE               "12"          //窗帘
#define INFRARED_SERVE         "13"          //红外发射
#define DC_SERVE               "15"          //门禁控制
//上传状态
#define ON                "1"
#define OFF               "0"
#define STOP              "2"
#define CLOSE             "4"

/****************************************************************************************/
#endif // VARIABLEDEFINITION_H
