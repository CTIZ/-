#include "dialog.h"
#include "ui_dialog.h"

volatile float temp_value;
volatile float hum_value;
volatile float ill_value;
volatile float air_value;
volatile unsigned int co2_value;
volatile unsigned int pm_value;
volatile unsigned int gas_value;
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

    myTcp=new TcpClientThread();
    myTcp->serverIP=sql.sqlQuery(QString("select serverIp from tb_gatewayInfo")).toString();

    Serial=new SerialThread();

    SerialHandle=new SerialDataHandle();

    t4=new QTimer(this);
    connect(t4,SIGNAL(timeout()),this,SLOT(Mode()));
    t4->start(1000);

}
void Dialog::VarInit(){
    ReadNodeNum=0;
    dvd=8;
    air=1;
    tv=5;
    Modes=0;

    mod1=new Mode1(this);
    mod2=new Mode2(this);
    mod3=new Mode3(this);
    mod4=new Mode4(this);

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
    }else if(type==CO2_SERVE){
        ui->lab_co2->setText(value);
        co2_value=value.toInt();
    }else if(type==GAS_SERVE){
        ui->lab_gas->setText(value);
        gas_value=value.toInt();
    }else if(type==PM25_SERVE){
        ui->lab_pm->setText(value);
        pm_value=value.toInt();
    }else if(type==SMK_SERVE){
        ui->lab_smoke->setText(value);
        smoke_value=value.toInt();
    }else if(type==HI_SERVE){
        if(value==ON){
            ui->lab_inf->setText("有人");
        }else{
            ui->lab_inf->setText("无人");
        }
        human_state=value.toInt();
    }else if(type==FAN_SERVE){
        if(value==OFF){
            fan_state=SWITCH_OFF;
        }else{
            fan_state=SWITCH_ON;
        }
    }else if(type==LAMP_SERVE){
        if(value==OFF){
            lamp_state=SWITCH_OFF;
        }else{
            lamp_state=SWITCH_ON;
        }
    }else if(type==WL_SERVE){
        if(value==OFF){
            warning_state=SWITCH_OFF;
        }else{
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

QString zh="";
int zhi[3]={0,0,0};

void Dialog::on_btn_serialopen_clicked()
{
    if(ui->btn_serialopen->text()=="打开串口"){
        zh=ui->cmb1->currentText();
        zhi[0]=ui->cmb2->currentText().toInt();
        zhi[1]=ui->cmb4->currentText().toInt();
        zhi[2]=ui->cmb3->currentIndex();
        Serial->start();
        connect(Serial,SIGNAL(serialFinished(QByteArray)),this,SLOT(getStr(QByteArray)));
        connect(SerialHandle,SIGNAL(evt_deviceState(QString,QString,QString)),this,SLOT(upload(QString,QString,QString)));
        t2=new QTimer(this);
        connect(t2,SIGNAL(timeout()),this,SLOT(ReadNodeData()));
        t2->start(500);
        ui->btn_serialopen->setText("关闭串口");
    }else{
        ReadNodeNum=0;
        t2->stop();
        disconnect(Serial,SIGNAL(serialFinished(QByteArray)),this,SLOT(getStr(QByteArray)));
        disconnect(SerialHandle,SIGNAL(evt_deviceState(QString,QString,QString)),this,SLOT(upload(QString,QString,QString)));
        Serial->exit();
        ui->btn_serialopen->setText("打开串口");
    }
}

void Dialog::on_btn_tcp_clicked()
{
    if(ui->btn_tcp->text()=="连接服务器"){
        myTcp->start();
        connect(myTcp,SIGNAL(evt_socket_receive(QString,uint,uint,uint)),this,SLOT(app_control(QString,uint,uint,uint)));
        t1=new QTimer(this);
        connect(t1,SIGNAL(timeout()),this,SLOT(see()));
        t1->start(10000);
        ui->btn_tcp->setText("已连接");
    }else{
        t1->stop();
        disconnect(myTcp,SIGNAL(evt_socket_receive(QString,uint,uint,uint)),this,SLOT(app_control(QString,uint,uint,uint)));
        myTcp->exit();
        ui->btn_tcp->setText("连接服务器");
    }
}

void Dialog::on_btn_server_clicked()
{
    if(ui->btn_server->text()=="监听端口"){
        Server->listen(QHostAddress::Any,6001);
        connect(Server,SIGNAL(evt_configBoardId()),this,SLOT(BoardInit()));
        ui->btn_server->setText("已连接");
    }else{
        disconnect(Server,SIGNAL(evt_configBoardId()),this,SLOT(BoardInit()));
        Server->close();
        ui->btn_server->setText("监听端口");
    }
}

void Dialog::on_btn_warning_clicked()
{
    Modes=0;
    if(warning_state!=SWITCH_ON){
        WarningCmd(SWITCH_ON);
    }else{
        WarningCmd(SWITCH_OFF);
    }
}

void Dialog::on_btn_curtain_clicked()
{
    Modes=0;
    if(curtain_state!=CHANNEL_1){
        CurtainCmd(CHANNEL_1);
    }else{
        CurtainCmd(CHANNEL_3);
    }
}

void Dialog::on_btn_rfid_clicked()
{
    Modes=0;
    if(rfid_state!=SWITCH_ON){
        RfidCmd(SWITCH_ON);
    }else{
        RfidCmd(SWITCH_OFF);
    }
}

void Dialog::on_btn_lamp_clicked()
{
    Modes=0;
    if(lamp_state!=SWITCH_ON){
        LampCmd(SWITCH_ON);
    }else{
        LampCmd(SWITCH_OFF);
    }
}

void Dialog::on_btn_fan_clicked()
{
    Modes=0;
    if(fan_state!=SWITCH_ON){
        FanCmd(SWITCH_ON);
    }else{
        FanCmd(SWITCH_OFF);
    }
}

void Dialog::on_btn_air_clicked()
{
    Modes=0;
    if(air_state!=SWITCH_ON){
        air_state=SWITCH_ON;
    }else{
        air_state=SWITCH_OFF;
    }
    InfraredEmit(air);
}

void Dialog::on_btn_dvd_clicked()
{
    Modes=0;
    if(dvd_state!=SWITCH_ON){
        dvd_state=SWITCH_ON;
    }else{
        dvd_state=SWITCH_OFF;
    }
    InfraredEmit(dvd);
}

void Dialog::on_btn_tv_clicked()
{
    Modes=0;
    if(tv_state!=SWITCH_ON){
        tv_state=SWITCH_ON;
    }else{
        tv_state=SWITCH_OFF;
    }
    InfraredEmit(tv);
}

void Dialog::on_btn_ld_clicked()
{
    if(Modes==0){
        Modes=4;
    }else if(Modes==4){
        Modes=0;
    }
}

bool chk[4];

void Dialog::on_chk1_clicked(bool checked)
{
    chk[0]=checked;
}

void Dialog::on_chk2_clicked(bool checked)
{
    chk[1]=checked;
}

void Dialog::on_chk3_clicked(bool checked)
{
    chk[2]=checked;
}

void Dialog::on_chk4_clicked(bool checked)
{
    chk[3]=checked;
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

QString ld[3];

void Dialog::Mode(){
    switch(Modes){
    case 0:
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
            ui->btn_ld->setText("联动模式开启");
            ui->chk1->setEnabled(1);
            ui->chk2->setEnabled(1);
            ui->chk3->setEnabled(1);
            ui->chk4->setEnabled(1);
        }

        break;
    case 1:
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
            ui->btn_ld->setText("联动模式开启");
            ui->chk1->setEnabled(1);
            ui->chk2->setEnabled(1);
            ui->chk3->setEnabled(1);
            ui->chk4->setEnabled(1);
        }

        break;
    case 2:
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
            ui->btn_ld->setText("联动模式开启");
            ui->chk1->setEnabled(1);
            ui->chk2->setEnabled(1);
            ui->chk3->setEnabled(1);
            ui->chk4->setEnabled(1);
        }

        break;
    case 3:
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
            ui->btn_ld->setText("联动模式开启");
            ui->chk1->setEnabled(1);
            ui->chk2->setEnabled(1);
            ui->chk3->setEnabled(1);
            ui->chk4->setEnabled(1);
        }

        break;
    case 4:
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
            ld[0]=ui->ld1->currentText();
            ld[1]=ui->ld2->currentText();
            ld[2]=ui->ld3->text();
            connect(mod4,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
            mod4->start();
            ui->btn_ld->setText("联动模式关闭");
            ui->chk1->setEnabled(0);
            ui->chk2->setEnabled(0);
            ui->chk3->setEnabled(0);
            ui->chk4->setEnabled(0);
        }

        break;
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

void Dialog::on_btn_temp_clicked()
{
    Draw a;
    a.setWindowTitle("温度");
    a.exec();
}

void Dialog::on_btn_hum_clicked()
{
    Draw a;
    a.setWindowTitle("湿度");
    a.exec();
}

void Dialog::on_btn_ill_clicked()
{
    Draw a;
    a.setWindowTitle("光照");
    a.exec();
}

void Dialog::on_btn_smoke_clicked()
{
    Draw a;
    a.setWindowTitle("烟雾");
    a.exec();
}

void Dialog::on_btn_ap_clicked()
{
    Draw a;
    a.setWindowTitle("气压");
    a.exec();
}

void Dialog::on_btn_pm_clicked()
{
    Draw a;
    a.setWindowTitle("PM2.5");
    a.exec();
}

void Dialog::on_btn_co2_clicked()
{
    Draw a;
    a.setWindowTitle("Co2");
    a.exec();
}

void Dialog::on_btn_gas_clicked()
{
    Draw a;
    a.setWindowTitle("燃气");
    a.exec();
}
void Dialog::on_tabWidget_currentChanged(int index)
{
    if(index==2){
        QFile f("log.txt");
        if(f.open(QIODevice::ReadOnly)){
            QTextStream in(&f);
            ui->textEdit->setText(in.readAll());
            f.close();
        }
    }
}
