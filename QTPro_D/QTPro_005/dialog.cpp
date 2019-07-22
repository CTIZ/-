#include "dialog.h"
#include "ui_dialog.h"

volatile float temp_value;
volatile float hum_value;
volatile float ill_value;
volatile float air_value;
volatile unsigned int co2_value;
volatile unsigned int gas_value;
volatile unsigned int pm_value;
volatile unsigned int smoke_value;
volatile unsigned int human_state;

volatile unsigned int fan_state;
volatile unsigned int lamp_state;
volatile unsigned int warning_state;
volatile unsigned int curtain_state;
volatile unsigned int rfid_state;

volatile unsigned int air_state;
volatile unsigned int tv_state;
volatile unsigned int dvd_state;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    VarInit();

    Server=new TcpServer();
    Server->listen(QHostAddress::Any,6001);
    connect(Server,SIGNAL(evt_configBoardId()),this,SLOT(BoardInit()));

    myTcp=new TcpClientThread();
    myTcp->serverIP=sql.sqlQuery(QString("select serverIp from tb_gatewayInfo")).toString();
    myTcp->start();
    connect(myTcp,SIGNAL(evt_socket_receive(QString,uint,uint,uint)),this,SLOT(app_control(QString,uint,uint,uint)));
    t1=new QTimer(this);
    connect(t1,SIGNAL(timeout()),this,SLOT(see()));
    t1->start(10000);

    Serial=new SerialThread();
    Serial->start();
    connect(Serial,SIGNAL(data(QByteArray)),this,SLOT(getStr(QByteArray)));

    SerialHandle=new SerialDataHandle();
    connect(SerialHandle,SIGNAL(evt_deviceState(QString,QString,QString)),this,SLOT(upload(QString,QString,QString)));
    t2=new QTimer(this);
    connect(t2,SIGNAL(timeout()),this,SLOT(ReadNodeData()));
    t2->start(500);
}
void Dialog::VarInit(){
    ReadNodeNum=0;
    tv=5;
    dvd=11;
    air=1;
    Modes=0;

    mod=new Mode(this);

    fan_state=SWITCH_OFF;
    lamp_state=SWITCH_OFF;
    warning_state=SWITCH_OFF;
    curtain_state=SWITCH_OFF;
    rfid_state=SWITCH_OFF;

    air_state=SWITCH_OFF;
    tv_state=SWITCH_OFF;
    dvd_state=SWITCH_OFF;
}
void Dialog::see(){
    if(!myTcp->getTcpClientFlag())
        myTcp->start();
}
void Dialog::BoardInit(){
    SerialHandle->init();
}
void Dialog::getStr(QByteArray str){
    SerialHandle->receive(str);
}
void Dialog::ReadNodeData(){
    ReadNodeNum++;
    if(ReadNodeNum<=16){
        unsigned int pCmd[3];
        pCmd[0]=0;
        pCmd[1]=0;
        pCmd[2]=ReadNodeNum;
        QByteArray ba=SerialHandle->sendingDataHandle(READNODE,0,pCmd,3);
        Serial->send(ba);
    }else{
        ReadNodeNum=0;
        t2->stop();

        t3=new QTimer(this);
        connect(t3,SIGNAL(timeout()),this,SLOT(GetNodeData()));
        t3->start(500);
    }
}
void Dialog::GetNodeData(){
    ReadNodeNum++;
    if(ReadNodeNum<=16){
        unsigned int pCmd[2];
        pCmd[0]=0;
        pCmd[1]=0;
        QByteArray ba=SerialHandle->sendingDataHandle(GETSTATE,ReadNodeNum,pCmd,2);
        Serial->send(ba);
    }else{
        ReadNodeNum=0;
        t3->stop();
    }
}
void Dialog::upload(const QString &type, const QString &cmdCode, const QString &value){
    if(myTcp->getTcpClientFlag())
        myTcp->upload(type,cmdCode,value);
    if(type==TEMP_SERVE){
        ui->lab_temp->setText(value);
        temp_value=value.toFloat();
    }else if(type==HUM_SERVE){
        ui->lab_hum->setText(value);
        hum_value=value.toFloat();
    }else if(type==ILL_SERVE){
        ui->lab_ill->setText(value);
        ill_value=value.toFloat();
    }else if(type==AP_SERVE){
        ui->lab_air->setText(value);
        air_value=value.toFloat();
    }else if(type==GAS_SERVE){
        ui->lab_gas->setText(value);
        gas_value=value.toInt();
    }else if(type==CO2_SERVE){
        ui->lab_co2->setText(value);
        co2_value=value.toInt();
    }else if(type==SMK_SERVE){
        ui->lab_smoke->setText(value);
        smoke_value=value.toInt();
    }else if(type==PM25_SERVE){
        ui->lab_pm->setText(value);
        pm_value=value.toInt();
    }else if(type==HI_SERVE){
        if(value==ON){
            ui->lab_inf->setText("有人");
        }else{
            ui->lab_inf->setText("无人");
        }
        human_state=value.toInt();
    }else if(type==FAN_SERVE){
        if(value==OFF){
            ui->btn_fan->setStyleSheet("background-image: url(:/4210.png);");
            fan_state=SWITCH_OFF;
        }else{
            ui->btn_fan->setStyleSheet("background-image: url(:/4211.png);");
            fan_state=SWITCH_ON;
        }
    }else if(type==LAMP_SERVE){
        if(value==OFF){
            ui->btn_lamp->setStyleSheet("background-image: url(:/4210.png);");
            lamp_state=SWITCH_OFF;
        }else{
            ui->btn_lamp->setStyleSheet("background-image: url(:/4211.png);");
            lamp_state=SWITCH_ON;
        }
    }else if(type==WL_SERVE){
        if(value==OFF){
            ui->btn_warning->setStyleSheet("background-image: url(:/4210.png);");
            warning_state=SWITCH_OFF;
        }else{
            ui->btn_warning->setStyleSheet("background-image: url(:/4211.png);");
            warning_state=SWITCH_ON;
        }
    }else if(type==CT_SERVE){
        if(value==ON){
            curtain_state=CHANNEL_1;
        }else if(value==STOP){
            curtain_state=CHANNEL_2;
        }else if(value==CLOSE){
            curtain_state=CHANNEL_3;
        }
    }else if(type==DC_SERVE){
        rfid_state=SWITCH_OFF;
        ui->btn_rfid->setStyleSheet("background-image: url(:/4210.png);");
    }
}
void Dialog::app_control(QString type, unsigned int command, unsigned int cmdCode, unsigned int channel){
    unsigned int pCmd[9];
    pCmd[0]=0;
    pCmd[1]=0;
    pCmd[3]=0xee;
    pCmd[4]=0x03;
    pCmd[5]=0;
    if(type==INFRARED_SERVE){
        pCmd[2]=0x0B;
        pCmd[6]=cmdCode;
        pCmd[7]=(channel&0xf);
        pCmd[8]=(channel>>8)&0xf;
    }else if(type==DC_SERVE){
        pCmd[2]=0x0A;
        pCmd[6]=cmdCode;
        pCmd[7]=command;
        pCmd[8]=channel;
    }else if(type==CT_SERVE){
        CurtainCmd(channel);
        return;
    }else{
        pCmd[2]=0x01;
        pCmd[6]=cmdCode;
        pCmd[7]=command;
        pCmd[8]=channel;
    }
    deceive_control(SerialHandle->sensorTypeToBoardIdMap[type],pCmd,9);
}
void Dialog::deceive_control(unsigned int board_number, unsigned int *pCmd, unsigned int len){
    QByteArray ba=SerialHandle->sendingDataHandle(CONTROL,board_number,pCmd,len);
    Serial->send(ba);
}
void Dialog::FanCmd(unsigned int command){
    unsigned int pCmd[9];
    pCmd[0]=0;
    pCmd[1]=0;
    pCmd[2]=0x01;
    pCmd[3]=0xee;
    pCmd[4]=0x03;
    pCmd[5]=0;
    pCmd[6]=SWITCH;
    pCmd[7]=command;
    pCmd[8]=CHANNEL_ALL;
    deceive_control(SerialHandle->sensorTypeToBoardIdMap[FAN_SERVE],pCmd,9);
}
void Dialog::LampCmd(unsigned int command){
    unsigned int pCmd[9];
    pCmd[0]=0;
    pCmd[1]=0;
    pCmd[2]=0x01;
    pCmd[3]=0xee;
    pCmd[4]=0x03;
    pCmd[5]=0;
    pCmd[6]=SWITCH;
    pCmd[7]=command;
    pCmd[8]=CHANNEL_ALL;
    deceive_control(SerialHandle->sensorTypeToBoardIdMap[LAMP_SERVE],pCmd,9);
}
void Dialog::WarningCmd(unsigned int command){
    unsigned int pCmd[9];
    pCmd[0]=0;
    pCmd[1]=0;
    pCmd[2]=0x01;
    pCmd[3]=0xee;
    pCmd[4]=0x03;
    pCmd[5]=0;
    pCmd[6]=SWITCH;
    pCmd[7]=command;
    pCmd[8]=CHANNEL_ALL;
    deceive_control(SerialHandle->sensorTypeToBoardIdMap[WL_SERVE],pCmd,9);
}
void Dialog::RfidCmd(unsigned int command){
    unsigned int pCmd[9];
    pCmd[0]=0;
    pCmd[1]=0;
    pCmd[2]=0x0A;
    pCmd[3]=0xee;
    pCmd[4]=0x03;
    pCmd[5]=0;
    pCmd[6]=SWITCH;
    pCmd[7]=command;
    pCmd[8]=CHANNEL_1;
    deceive_control(SerialHandle->sensorTypeToBoardIdMap[DC_SERVE],pCmd,9);
}
void Dialog::CurtainCmd(unsigned int channel){
    unsigned int pCmd[9];
    pCmd[0]=0;
    pCmd[1]=0;
    pCmd[2]=0x01;
    pCmd[3]=0xee;
    pCmd[4]=0x03;
    pCmd[5]=0;
    pCmd[6]=SWITCH;
    pCmd[7]=SWITCH_ON;
    pCmd[8]=channel;
    deceive_control(SerialHandle->sensorTypeToBoardIdMap[CT_SERVE],pCmd,9);
    QTimer::singleShot(500,this,SLOT(CurtainSleep()));
}
void Dialog::CurtainSleep(){
    unsigned int pCmd[9];
    pCmd[0]=0;
    pCmd[1]=0;
    pCmd[2]=0x01;
    pCmd[3]=0xee;
    pCmd[4]=0x03;
    pCmd[5]=0;
    pCmd[6]=SWITCH;
    pCmd[7]=SWITCH_OFF;
    pCmd[8]=CHANNEL_ALL;
    deceive_control(SerialHandle->sensorTypeToBoardIdMap[CT_SERVE],pCmd,9);
}
void Dialog::InfraredEmit(unsigned int channel){
    unsigned int pCmd[9];
    pCmd[0]=0;
    pCmd[1]=0;
    pCmd[2]=0x0B;
    pCmd[3]=0xee;
    pCmd[4]=0x03;
    pCmd[5]=0;
    pCmd[6]=SWITCH;
    pCmd[7]=(channel&0xf);
    pCmd[8]=(channel>>8)&0xf;
    deceive_control(SerialHandle->sensorTypeToBoardIdMap[INFRARED_SERVE],pCmd,9);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::mylog(QString action){
    QFile f("log.txt");
    if(f.open(QIODevice::Append)){
        QTextStream in(&f);
        in<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ")<<action<<endl;
        f.close();
    }
}

void Dialog::on_btn_lamp_clicked()
{
    if(lamp_state!=SWITCH_ON){
        LampCmd(SWITCH_ON);
        mylog("射灯开启");
    }else{
        LampCmd(SWITCH_OFF);
        mylog("射灯关闭");
    }
}

void Dialog::on_btn_rfid_clicked()
{
    if(rfid_state!=SWITCH_ON){
        RfidCmd(SWITCH_ON);
        mylog("门禁开启");
    }else{
        RfidCmd(SWITCH_OFF);
        mylog("门禁关闭");
    }
}

void Dialog::on_btn_fan_clicked()
{
    if(fan_state!=SWITCH_ON){
        FanCmd(SWITCH_ON);
        mylog("风扇开启");
    }else{
        FanCmd(SWITCH_OFF);
        mylog("风扇关闭");
    }
}

void Dialog::on_btn__clicked()
{

}

void Dialog::on_btn_warning_clicked()
{
    if(warning_state!=SWITCH_ON){
        WarningCmd(SWITCH_ON);
        mylog("报警灯开启");
    }else{
        WarningCmd(SWITCH_OFF);
        mylog("报警灯关闭");
    }
}

void Dialog::on_btn_tv_on_clicked()
{
    if(tv_state!=SWITCH_ON){
        tv_state=SWITCH_ON;
        InfraredEmit(tv);
        mylog("电视开启");
    }
}

void Dialog::on_btn_tv_off_clicked()
{
    if(tv_state!=SWITCH_OFF){
        tv_state=SWITCH_OFF;
        InfraredEmit(tv);
        mylog("电视关闭");
    }
}

void Dialog::on_btn_dvd_on_clicked()
{
    if(dvd_state!=SWITCH_ON){
        dvd_state=SWITCH_ON;
        InfraredEmit(dvd);
        mylog("DVD开启");
    }
}

void Dialog::on_btn_dvd_off_clicked()
{
    if(dvd_state!=SWITCH_OFF){
        dvd_state=SWITCH_OFF;
        InfraredEmit(dvd);
        mylog("DVD关闭");
    }
}

void Dialog::on_pushButton_10_clicked()
{

}

void Dialog::on_pushButton_11_clicked()
{

}

void Dialog::on_btn_air_on_clicked()
{
    if(air_state!=SWITCH_ON){
        air_state=SWITCH_ON;
        InfraredEmit(air);
        mylog("空调开启");
    }
}

void Dialog::on_btn_air_off_clicked()
{
    if(air_state!=SWITCH_OFF){
        air_state=SWITCH_OFF;
        InfraredEmit(air);
        mylog("空调关闭");
    }
}

void Dialog::on_btn_curtain_on_clicked()
{
    if(curtain_state!=CHANNEL_1){
        CurtainCmd(CHANNEL_1);
        mylog("窗帘开启");
    }
}

void Dialog::on_btn_curtain_stop_clicked()
{
    if(curtain_state!=CHANNEL_2){
        CurtainCmd(CHANNEL_2);
        mylog("窗帘停");
    }
}

void Dialog::on_btn_curtain_off_clicked()
{
    if(curtain_state!=CHANNEL_3){
        CurtainCmd(CHANNEL_3);
        mylog("窗帘关闭");
    }
}

void Dialog::on_chk_log_clicked(bool checked)
{
    if(checked){
        myLog3 a;
        a.exec();
        ui->chk_log->setChecked(0);
    }
}
int ld[4];
void Dialog::on_btn_ld_clicked()
{
    if(Modes==0){
        if(!mod->isRunning()){
            ld[0]=ui->ld1->currentIndex();
            ld[2]=ui->ld3->text().toInt();
            connect(mod,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
            mod->start();
            Modes=1;
            ui->btn_ld->setStyleSheet("background-image: url(:/4211.png);");
        }
    }else{
        if(mod->isRunning()){
            disconnect(mod,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
            mod->ThreadQuit();
            Modes=0;
            ui->btn_ld->setStyleSheet("background-image: url(:/4210.png);");
        }
    }
}

void Dialog::on_btn_ld2_d_clicked()
{
    ld[1]=0;
    ui->btn_ld2_d->setStyleSheet("background-image: url(:/4234.png);");
    ui->btn_ld2_x->setStyleSheet("background-image: url(:/4233.png);");
}

void Dialog::on_btn_ld2_x_clicked()
{
    ld[1]=1;
    ui->btn_ld2_d->setStyleSheet("background-image: url(:/4233.png);");
    ui->btn_ld2_x->setStyleSheet("background-image: url(:/4234.png);");
}
void Dialog::on_btn_ld4_k_clicked()
{
    ld[3]=0;
    ui->btn_ld4_k->setStyleSheet("background-image: url(:/4234.png);");
    ui->btn_ld4_g->setStyleSheet("background-image: url(:/4233.png);");
}

void Dialog::on_btn_ld4_g_clicked()
{
    ld[3]=1;
    ui->btn_ld4_k->setStyleSheet("background-image: url(:/4233.png);");
    ui->btn_ld4_g->setStyleSheet("background-image: url(:/4234.png);");
}
bool chk[10]={false,false,false,false,false,false,false,false,false,false};
void Dialog::on_btn_ld5_tv_clicked()
{
    if(chk[0]){
        ui->btn_ld5_tv->setStyleSheet("background-image: url(:/4233.png);");
        chk[0]=false;
    }else{
        ui->btn_ld5_tv->setStyleSheet("background-image: url(:/4234.png);");
        chk[0]=true;
    }
}

void Dialog::on_btn_ld5_dvd_clicked()
{
    if(chk[1]){
        ui->btn_ld5_dvd->setStyleSheet("background-image: url(:/4233.png);");
        chk[1]=false;
    }else{
        ui->btn_ld5_dvd->setStyleSheet("background-image: url(:/4234.png);");
        chk[1]=true;
    }
}

void Dialog::on_pushButton_14_clicked()
{
    if(chk[2]){
        chk[2]=false;
    }else{
        chk[2]=true;
    }
}

void Dialog::on_btn_ld5_air_clicked()
{
    if(chk[3]){
        ui->btn_ld5_air->setStyleSheet("background-image: url(:/4233.png);");
        chk[3]=false;
    }else{
        ui->btn_ld5_air->setStyleSheet("background-image: url(:/4234.png);");
        chk[3]=true;
    }
}

void Dialog::on_btn_ld5_rfid_clicked()
{
    if(chk[4]){
        ui->btn_ld5_rfid->setStyleSheet("background-image: url(:/4233.png);");
        chk[4]=false;
    }else{
        ui->btn_ld5_rfid->setStyleSheet("background-image: url(:/4234.png);");
        chk[4]=true;
    }
}

void Dialog::on_btn_ld5_fan_clicked()
{
    if(chk[5]){
        ui->btn_ld5_fan->setStyleSheet("background-image: url(:/4233.png);");
        chk[5]=false;
    }else{
        ui->btn_ld5_fan->setStyleSheet("background-image: url(:/4234.png);");
        chk[5]=true;
    }
}

void Dialog::on_pushButton_18_clicked()
{
    if(chk[6]){
        chk[6]=false;
    }else{
        chk[6]=true;
    }
}

void Dialog::on_btn_ld5_warning_clicked()
{
    if(chk[7]){
        ui->btn_ld5_warning->setStyleSheet("background-image: url(:/4233.png);");
        chk[7]=false;
    }else{
        ui->btn_ld5_warning->setStyleSheet("background-image: url(:/4234.png);");
        chk[7]=true;
    }
}

void Dialog::on_btn_ld5_lamp_clicked()
{
    if(chk[8]){
        ui->btn_ld5_lamp->setStyleSheet("background-image: url(:/4233.png);");
        chk[8]=false;
    }else{
        ui->btn_ld5_lamp->setStyleSheet("background-image: url(:/4234.png);");
        chk[8]=true;
    }
}

void Dialog::on_btn_ld5_curtain_clicked()
{
    if(chk[9]){
        ui->btn_ld5_curtain->setStyleSheet("background-image: url(:/4233.png);");
        chk[9]=false;
    }else{
        ui->btn_ld5_curtain->setStyleSheet("background-image: url(:/4234.png);");
        chk[9]=true;
    }
}
void Dialog::ModeHandle(QString type, unsigned int command, unsigned int channel){
    if(type==FAN_SERVE){
        FanCmd(command);
    }else if(type==LAMP_SERVE){
        LampCmd(command);
    }else if(type==WL_SERVE){
        WarningCmd(command);
    }else if(type==DC_SERVE){
        RfidCmd(command);
    }else if(type==CT_SERVE){
        CurtainCmd(channel);
    }else if(type==INFRARED_SERVE){
        InfraredEmit(channel);
    }
}
