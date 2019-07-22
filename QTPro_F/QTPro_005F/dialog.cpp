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
volatile unsigned int lamp1_state;
volatile unsigned int lamp2_state;
volatile unsigned int warning_state;
volatile unsigned int curtain_state;
volatile unsigned int rfid_state;

volatile unsigned int air_state;
volatile unsigned int dvd_state;
volatile unsigned int tv_state;

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

    t4=new QTimer(this);
    connect(t4,SIGNAL(timeout()),this,SLOT(Mode()));
    t4->start(1000);
}
void Dialog::VarInit(){
    ReadNodeNum=0;
    Modes=Modes_z=0;
    dvd=3;
    air=1;
    tv=2;

    mod1=new Mode1(this);
    mod2=new Mode2(this);
    mod3=new Mode3(this);
    mod4=new Mode4(this);
    mod5=new Mode5(this);

    fan_state=SWITCH_OFF;
    lamp1_state=SWITCH_OFF;
    lamp2_state=SWITCH_OFF;
    warning_state=SWITCH_OFF;
    curtain_state=SWITCH_OFF;
    rfid_state=SWITCH_OFF;

    air_state=SWITCH_OFF;
    dvd_state=SWITCH_OFF;
    tv_state=SWITCH_OFF;
}
void Dialog::BoardInit(){
    SerialHandle->init();
}
void Dialog::getStr(QByteArray str){
    SerialHandle->receive(str);
}
void Dialog::see(){
    if(!myTcp->getTcpClientFlag())
        myTcp->start();
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
void Dialog::data_update(){
    QString human;
    if(human_state==1)
        human="有人";
    else
        human="无人";
    ui->textEdit->setText("温度："+QString::number(temp_value)
                          +"\n湿度："+QString::number(hum_value)
                          +"\n光照度："+QString::number(ill_value)
                          +"\n烟雾："+QString::number(smoke_value)
                          +"\n可燃气："+QString::number(gas_value)
                          +"\nPM25："+QString::number(pm_value)
                          +"\n人体："+human
                          +"\n气压："+QString::number(air_value)
                          +"\nCO2："+QString::number(co2_value));
}

void Dialog::upload(const QString &type, const QString &cmdCode, const QString &value){
    if(myTcp->getTcpClientFlag())
        myTcp->upload(type,cmdCode,value);
    if(type==TEMP_SERVE){
        temp_value=value.toFloat();
        data_update();
    }else if(type==HUM_SERVE){
        hum_value=value.toFloat();
        data_update();
    }else if(type==ILL_SERVE){
        ill_value=value.toFloat();
        data_update();
    }else if(type==AP_SERVE){
        air_value=value.toFloat();
        data_update();
    }else if(type==CO2_SERVE){
        co2_value=value.toInt();
        data_update();
    }else if(type==GAS_SERVE){
        gas_value=value.toInt();
        data_update();
    }else if(type==PM25_SERVE){
        pm_value=value.toInt();
        data_update();
    }else if(type==SMK_SERVE){
        smoke_value=value.toInt();
        data_update();
    }else if(type==HI_SERVE){
        human_state=value.toInt();
        data_update();
    }else if(type==FAN_SERVE){
        if(value==OFF){
            ui->btn_fan->setText("换气扇开");
            fan_state=SWITCH_OFF;
        }else{
            ui->btn_fan->setText("换气扇关");
            fan_state=SWITCH_ON;
        }
    }else if(type==LAMP_SERVE){
        if(value==OFF){
            ui->btn_lamp->setText("射灯开");
            ui->icon_lamp->setStyleSheet("border-image: url(:/6104.png);");
            lamp1_state=SWITCH_OFF;
            lamp2_state=SWITCH_OFF;
        }else if(value=="1"){
            lamp1_state=SWITCH_ON;
            lamp2_state=SWITCH_OFF;
        }else if(value=="2"){
            lamp1_state=SWITCH_OFF;
            lamp2_state=SWITCH_ON;
        }else{
            ui->btn_lamp->setText("射灯关");
            ui->icon_lamp->setStyleSheet("border-image: url(:/6105.png);");
            lamp1_state=SWITCH_ON;
            lamp2_state=SWITCH_ON;
        }
    }else if(type==WL_SERVE){
        if(value==OFF){
            ui->btn_warning->setText("报警灯开");
            ui->icon_warning->setStyleSheet("border-image: url(:/0112.png);");
            warning_state=SWITCH_OFF;
        }else{
            ui->btn_warning->setText("报警灯关");
            ui->icon_warning->setStyleSheet("border-image: url(:/0111.png);");
            warning_state=SWITCH_ON;
        }
    }else if(type==CT_SERVE){
        if(value==ON){
            ui->icon_curtain->setStyleSheet("border-image: url(:/6106.png);");
            curtain_state=CHANNEL_1;
        }else if(value==STOP){
            curtain_state=CHANNEL_2;
        }else if(value==CLOSE){
            ui->icon_curtain->setStyleSheet("border-image: url(:/6107.png);");
            curtain_state=CHANNEL_3;
        }
    }else if(value==DC_SERVE){
        rfid_state=SWITCH_OFF;
        ui->btn_rfid->setText("门禁开");
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
void Dialog::LampCmd(unsigned int command, unsigned int channel){
    unsigned int pCmd[9];
    pCmd[0]=0;
    pCmd[1]=0;
    pCmd[2]=0x01;
    pCmd[3]=0xee;
    pCmd[4]=0x03;
    pCmd[5]=0;
    pCmd[6]=SWITCH;
    pCmd[7]=command;
    pCmd[8]=channel;
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

void Dialog::on_pushButton_11_clicked()
{
    this->close();
}

void Dialog::on_icon_warning_clicked()
{
    if(warning_state!=SWITCH_ON){
        WarningCmd(SWITCH_ON);
    }else{
        WarningCmd(SWITCH_OFF);
    }
}

void Dialog::on_icon_lamp_clicked()
{
    if(lamp1_state!=SWITCH_ON||lamp2_state!=SWITCH_ON){
        LampCmd(SWITCH_ON,CHANNEL_ALL);
    }else{
        LampCmd(SWITCH_OFF,CHANNEL_ALL);
    }
}

void Dialog::on_btn_warning_clicked()
{
    if(warning_state!=SWITCH_ON){
        WarningCmd(SWITCH_ON);
    }else{
        WarningCmd(SWITCH_OFF);
    }
}

void Dialog::on_btn_lamp_clicked()
{
    if(lamp1_state!=SWITCH_ON||lamp2_state!=SWITCH_ON){
        LampCmd(SWITCH_ON,CHANNEL_ALL);
    }else{
        LampCmd(SWITCH_OFF,CHANNEL_ALL);
    }
}

void Dialog::on_btn_fan_clicked()
{
    if(fan_state!=SWITCH_ON){
        FanCmd(SWITCH_ON);
    }else{
        FanCmd(SWITCH_OFF);
    }
}

void Dialog::on_btn_rfid_clicked()
{
    if(rfid_state!=SWITCH_ON){
        ui->btn_rfid->setText("门禁关");
        RfidCmd(SWITCH_ON);
    }else{
        RfidCmd(SWITCH_OFF);
    }
}

void Dialog::on_btn_curtain_on_clicked()
{
    if(curtain_state!=CHANNEL_1){
        CurtainCmd(CHANNEL_1);
    }
}

void Dialog::on_btn_curtain_off_clicked()
{
    if(curtain_state!=CHANNEL_3){
        CurtainCmd(CHANNEL_3);
    }
}

void Dialog::on_icon_curtain_clicked()
{
    if(curtain_state!=CHANNEL_1){
        CurtainCmd(CHANNEL_1);
    }else{
        CurtainCmd(CHANNEL_3);
    }
}

void Dialog::on_radio_dankong_clicked()
{
    Modes=0;
    Modes_z=0;
}

void Dialog::on_radio_mode_clicked()
{
    Modes_z=1;
}

int ld[5];
void Dialog::on_radio_ld_clicked()
{
    ld[0]=ui->ld1->currentIndex();
    ld[1]=ui->ld2->currentIndex();
    ld[2]=ui->ld3->currentText().toInt();
    ld[3]=ui->ld4->currentIndex();
    ld[4]=ui->ld5->currentIndex();
    Modes=5;
    Modes_z=1;
}

void Dialog::on_btn_infrared_clicked()
{
    if(ui->sp_infrared->value()==tv){
        on_btn_tv_clicked();
    }else if(ui->sp_infrared->value()==dvd){
        on_btn_dvd_clicked();
    }else if(ui->sp_infrared->value()==air){
        on_btn_air_clicked();
    }else{
        InfraredEmit(ui->sp_infrared->value());
    }
}

void Dialog::on_btn_tv_clicked()
{
    if(tv_state!=SWITCH_ON){
        tv_state=SWITCH_ON;
        ui->btn_tv->setText("电视机关");
    }else{
        tv_state=SWITCH_OFF;
        ui->btn_tv->setText("电视机开");
    }
    InfraredEmit(tv);
}

void Dialog::on_btn_dvd_clicked()
{
    if(dvd_state!=SWITCH_ON){
        dvd_state=SWITCH_ON;
        ui->btn_dvd->setText("DVD关");
    }else{
        dvd_state=SWITCH_OFF;
        ui->btn_dvd->setText("DVD开");
    }
    InfraredEmit(dvd);
}

void Dialog::on_btn_air_clicked()
{
    if(air_state!=SWITCH_ON){
        air_state=SWITCH_ON;
        ui->btn_air->setText("空调关");
    }else{
        air_state=SWITCH_OFF;
        ui->btn_air->setText("空调开");
    }
    InfraredEmit(air);
}

void Dialog::on_radio_mode1_clicked()
{
    Modes=1;
}

void Dialog::on_radio_mode2_clicked()
{
    Modes=2;
}

void Dialog::on_radio_mode3_clicked()
{
    Modes=3;
}

void Dialog::on_radio_mode4_clicked()
{
    Modes=4;
}
void Dialog::Mode(){
    if(Modes_z==1){
        switch(Modes){
        case 0://无模式
            if(mod1->isRunning()){
                disconnect(mod1,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod1->ThreadQuit();
            }
            if(mod2->isRunning()){
                disconnect(mod2,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod2->ThreadQuit();
            }
            if(mod3->isRunning()){
                disconnect(mod3,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod3->ThreadQuit();
            }
            if(mod4->isRunning()){
                disconnect(mod4,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod4->ThreadQuit();
            }
            if(mod5->isRunning()){
                disconnect(mod5,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod5->ThreadQuit();
            }
            break;
        case 1://白天模式
            if(!mod1->isRunning()){
                connect(mod1,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod1->start();
            }
            if(mod2->isRunning()){
                disconnect(mod2,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod2->ThreadQuit();
            }
            if(mod3->isRunning()){
                disconnect(mod3,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod3->ThreadQuit();
            }
            if(mod4->isRunning()){
                disconnect(mod4,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod4->ThreadQuit();
            }
            if(mod5->isRunning()){
                disconnect(mod5,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod5->ThreadQuit();
            }
            break;
        case 2://夜间模式
            if(mod1->isRunning()){
                disconnect(mod1,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod1->ThreadQuit();
            }
            if(!mod2->isRunning()){
                connect(mod2,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod2->start();
            }
            if(mod3->isRunning()){
                disconnect(mod3,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod3->ThreadQuit();
            }
            if(mod4->isRunning()){
                disconnect(mod4,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod4->ThreadQuit();
            }
            if(mod5->isRunning()){
                disconnect(mod5,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod5->ThreadQuit();
            }
            break;
        case 3://安防模式
            if(mod1->isRunning()){
                disconnect(mod1,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod1->ThreadQuit();
            }
            if(mod2->isRunning()){
                disconnect(mod2,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod2->ThreadQuit();
            }
            if(!mod3->isRunning()){
                connect(mod3,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod3->start();
            }
            if(mod4->isRunning()){
                disconnect(mod4,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod4->ThreadQuit();
            }
            if(mod5->isRunning()){
                disconnect(mod5,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod5->ThreadQuit();
            }
            break;
        case 4://夜间模式
            if(mod1->isRunning()){
                disconnect(mod1,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod1->ThreadQuit();
            }
            if(mod2->isRunning()){
                disconnect(mod2,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod2->ThreadQuit();
            }
            if(mod3->isRunning()){
                disconnect(mod3,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod3->ThreadQuit();
            }
            if(!mod4->isRunning()){
                connect(mod4,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod4->start();
            }
            if(mod5->isRunning()){
                disconnect(mod5,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod5->ThreadQuit();
            }
            break;
        case 5://联动模式
            if(mod1->isRunning()){
                disconnect(mod1,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod1->ThreadQuit();
            }
            if(mod2->isRunning()){
                disconnect(mod2,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod2->ThreadQuit();
            }
            if(mod3->isRunning()){
                disconnect(mod3,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod3->ThreadQuit();
            }
            if(mod4->isRunning()){
                disconnect(mod4,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod4->ThreadQuit();
            }
            if(!mod5->isRunning()){
                connect(mod5,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
                mod5->start();
            }
            break;
        }
    }
}
void Dialog::ModeHandle(QString type, unsigned int command, unsigned int channel){
    if(type==FAN_SERVE){
        FanCmd(command);
    }else if(type==LAMP_SERVE){
        LampCmd(command,channel);
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

void Dialog::on_btn_draw_clicked()
{
    Draw a;
    a.setWindowTitle(ui->cmb_draw->currentText());
    a.exec();
}
