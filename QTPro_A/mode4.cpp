#include "mode4.h"

Mode4::Mode4(QObject *parent) :
    QThread(parent)
{

}
void Mode4::mySql(QString qj){
    QSqlQuery q;
    q.exec("select * from user ld cgq='"+ld[0]+"' and tj='"+ld[1]+"' and value='"+ld[2]+"' and qj='"+qj+"'");
    int num=q.value(4).toInt();
    if(q.next()){
        q.exec("update ld set num='"+(num+1)+"' where cgq='"+ld[0]+"' and tj='"+ld[1]+"' and value='"+ld[2]+"' and qj='"+qj+"'");
    }else{
        q.exec("insert into ld values('"+ld[0]+"','"+ld[1]+"','"+ld[2]+"','"+qj+"','0')");
    }
    emit AppendText(QDateTime::CurrentTime.ToString("yyyy-MM-dd hh:mm:ss"),ld[0]+ld[1]+ld[2],qj);
}


void Mode4::run(){
    QSqlQuery q;
    q.exec("create table ld(cgq varchar(40),tj varchar(40),value varchar(40),qj varchar(40),num int)");
    ThreadFlag=false;
    while(1){
        if(ld[0]=="光照"){
            if(ld[1]=="<"){
                if(ill_value<ld[2].toInt()){
                    if(chk[0]){//报警灯
                        if(warning_state!=SWITCH_ON){
                            mySql("开报警灯");
                            emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else{
                        if(warning_state!=SWITCH_OFF){
                            mySql("关报警灯");
                            emit mod(WL_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[1]){//风扇
                        if(fan_state!=SWITCH_ON){
                            mySql("开风扇");
                            emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else{
                        if(fan_state!=SWITCH_OFF){
                            mySql("关风扇");
                            emit mod(FAN_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[2]){//窗帘
                        if(curtain_state!=CHANNEL_1){
                            mySql("开窗帘");
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else{
                        if(curtain_state!=CHANNEL_3){
                            mySql("关窗帘");
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_3);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[3]){//射灯
                        if(lamp_state!=SWITCH_ON){
                            mySql("开射灯");
                            emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else{
                        if(lamp_state!=SWITCH_OFF){
                            mySql("关射灯");
                            emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                }
            }else if(ld[1]==">="){
                if(ill_value>=ld[2].toInt()){
                    if(chk[0]){//报警灯
                        if(warning_state!=SWITCH_ON){
                            mySql("开报警灯");
                            emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else{
                        if(warning_state!=SWITCH_OFF){
                            mySql("关报警灯");
                            emit mod(WL_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[1]){//风扇
                        if(fan_state!=SWITCH_ON){
                            mySql("开风扇");
                            emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else{
                        if(fan_state!=SWITCH_OFF){
                            mySql("关风扇");
                            emit mod(FAN_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[2]){//窗帘
                        if(curtain_state!=CHANNEL_1){
                            mySql("开窗帘");
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else{
                        if(curtain_state!=CHANNEL_3){
                            mySql("关窗帘");
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_3);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[3]){//射灯
                        if(lamp_state!=SWITCH_ON){
                            mySql("开射灯");
                            emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else{
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
                    if(chk[0]){//报警灯
                        if(warning_state!=SWITCH_ON){
                            mySql("开报警灯");
                            emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else{
                        if(warning_state!=SWITCH_OFF){
                            mySql("关报警灯");
                            emit mod(WL_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[1]){//风扇
                        if(fan_state!=SWITCH_ON){
                            mySql("开风扇");
                            emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else{
                        if(fan_state!=SWITCH_OFF){
                            mySql("关风扇");
                            emit mod(FAN_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[2]){//窗帘
                        if(curtain_state!=CHANNEL_1){
                            mySql("开窗帘");
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else{
                        if(curtain_state!=CHANNEL_3){
                            mySql("关窗帘");
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_3);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[3]){//射灯
                        if(lamp_state!=SWITCH_ON){
                            mySql("开射灯");
                            emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else{
                        if(lamp_state!=SWITCH_OFF){
                            mySql("关射灯");
                            emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                }
            }else if(ld[1]==">="){
                if(temp_value>=ld[2].toInt()){
                    if(chk[0]){//报警灯
                        if(warning_state!=SWITCH_ON){
                            mySql("开报警灯");
                            emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else{
                        if(warning_state!=SWITCH_OFF){
                            mySql("关报警灯");
                            emit mod(WL_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[1]){//风扇
                        if(fan_state!=SWITCH_ON){
                            mySql("开风扇");
                            emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else{
                        if(fan_state!=SWITCH_OFF){
                            mySql("关风扇");
                            emit mod(FAN_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[2]){//窗帘
                        if(curtain_state!=CHANNEL_1){
                            mySql("开窗帘");
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else{
                        if(curtain_state!=CHANNEL_3){
                            mySql("关窗帘");
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_3);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[3]){//射灯
                        if(lamp_state!=SWITCH_ON){
                            mySql("开射灯");
                            emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else{
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
                    if(chk[0]){//报警灯
                        if(warning_state!=SWITCH_ON){
                            mySql("开报警灯");
                            emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else{
                        if(warning_state!=SWITCH_OFF){
                            mySql("关报警灯");
                            emit mod(WL_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[1]){//风扇
                        if(fan_state!=SWITCH_ON){
                            mySql("开风扇");
                            emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else{
                        if(fan_state!=SWITCH_OFF){
                            mySql("关风扇");
                            emit mod(FAN_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[2]){//窗帘
                        if(curtain_state!=CHANNEL_1){
                            mySql("开窗帘");
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else{
                        if(curtain_state!=CHANNEL_3){
                            mySql("关窗帘");
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_3);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[3]){//射灯
                        if(lamp_state!=SWITCH_ON){
                            mySql("开射灯");
                            emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else{
                        if(lamp_state!=SWITCH_OFF){
                            mySql("关射灯");
                            emit mod(LAMP_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                }
            }else if(ld[1]==">="){
                if(pm_value>=ld[2].toInt()){
                    if(chk[0]){//报警灯
                        if(warning_state!=SWITCH_ON){
                            mySql("开报警灯");
                            emit mod(WL_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else{
                        if(warning_state!=SWITCH_OFF){
                            mySql("关报警灯");
                            emit mod(WL_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[1]){//风扇
                        if(fan_state!=SWITCH_ON){
                            mySql("开风扇");
                            emit mod(FAN_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else{
                        if(fan_state!=SWITCH_OFF){
                            mySql("关风扇");
                            emit mod(FAN_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[2]){//窗帘
                        if(curtain_state!=CHANNEL_1){
                            mySql("开窗帘");
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_1);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else{
                        if(curtain_state!=CHANNEL_3){
                            mySql("关窗帘");
                            emit mod(CT_SERVE,SWITCH_ON,CHANNEL_3);
                            msleep(500);
                            emit mod(CT_SERVE,SWITCH_OFF,CHANNEL_ALL);
                            msleep(500);
                        }
                    }
                    if(chk[3]){//射灯
                        if(lamp_state!=SWITCH_ON){
                            mySql("开射灯");
                            emit mod(LAMP_SERVE,SWITCH_ON,CHANNEL_ALL);
                            msleep(500);
                        }
                    }else{
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
void Mode4::ThreadQuit(){
    ThreadFlag=true;
    this->wait(3);
    this->quit();
}
