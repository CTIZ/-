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
volatile unsigned int rfid_state;
volatile unsigned int curtain_state;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    VarInit();

    Server=new TcpServer(this);
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
    connect(Serial,SIGNAL(serialFinished(QByteArray)),this,SLOT(getStr(QByteArray)));

    SerialHandle=new SerialDataHandle(this);
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
    Modes=0;
    mode_ld=false;

    mod1=new Mode1(this);
    mod2=new Mode2(this);
    mod3=new Mode3(this);


    fan_state=SWITCH_OFF;
    lamp_state=SWITCH_OFF;
    warning_state=SWITCH_OFF;
    rfid_state=SWITCH_OFF;
    curtain_state=SWITCH_OFF;
}
//板号配置
void Dialog::BoardInit(){
    SerialHandle->init();
}
//客户端监测
void Dialog::see(){
    if(!myTcp->getTcpClientFlag())
        myTcp->start();
}
//数据处理
void Dialog::getStr(QByteArray str){
    SerialHandle->receive(str);
}
//读板号
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
//读板数据
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
//数据更新，上传
void Dialog::upload(const QString &type, const QString &cmdCode, const QString &value){
    if(myTcp->getTcpClientFlag())
        myTcp->upload(type,cmdCode,value);
    if(type==TEMP_SERVE){
        ui->lcd_temp->display(value);
        temp_value=value.toFloat();
    }else if(type==HUM_SERVE){
        ui->lcd_hum->display(value);
        hum_value=value.toFloat();
    }else if(type==ILL_SERVE){
        ui->lcd_ill->display(value);
        ill_value=value.toFloat();
    }else if(type==AP_SERVE){
        ui->lcd_air->display(value);
        air_value=value.toFloat();
    }else if(type==CO2_SERVE){
        ui->lcd_co2->display(value);
        co2_value=value.toInt();
    }else if(type==GAS_SERVE){
        ui->lcd_gas->display(value);
        gas_value=value.toInt();
    }else if(type==PM25_SERVE){
        ui->lcd_pm->display(value);
        pm_value=value.toInt();
    }else if(type==SMK_SERVE){
        ui->lcd_smoke->display(value);
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
            ui->chk_fan->setChecked(0);
            fan_state=SWITCH_OFF;
            ui->chk_fan->setText("风扇开");
        }else{
            ui->chk_fan->setChecked(1);
            fan_state=SWITCH_ON;
            ui->chk_fan->setText("风扇关");
        }
    }else if(type==LAMP_SERVE){
        if(value==OFF){
            ui->chk_lamp->setChecked(0);
            lamp_state=SWITCH_OFF;
            ui->btn_lamp->setStyleSheet("border-image: url(:/5111.png);");
            ui->chk_lamp->setText("射灯开");
        }else{
            ui->chk_lamp->setChecked(1);
            lamp_state=SWITCH_ON;
            ui->btn_lamp->setStyleSheet("border-image: url(:/5110.png);");
            ui->chk_lamp->setText("射灯关");
        }
    }else if(type==WL_SERVE){
        if(value==OFF){
            ui->chk_warning->setChecked(0);
            warning_state=SWITCH_OFF;
            ui->btn_warning->setStyleSheet("border-image: url(:/5107.png);");
            ui->chk_warning->setText("报警灯开");
        }else{
            ui->chk_warning->setChecked(1);
            warning_state=SWITCH_ON;
            ui->btn_warning->setStyleSheet("border-image: url(:/5106.png);");
            ui->chk_warning->setText("报警灯关");
        }
    }else if(type==CT_SERVE){
        if(value==ON){
            ui->chk_curtain->setChecked(1);
            curtain_state=CHANNEL_1;
            ui->btn_curtain->setStyleSheet("border-image: url(:/5109.png);");
            ui->chk_curtain->setText("窗帘关");
        }else if(value==STOP){
            curtain_state=CHANNEL_2;
        }else if(value==CLOSE){
            ui->chk_curtain->setChecked(0);
            curtain_state=CHANNEL_3;
            ui->btn_curtain->setStyleSheet("border-image: url(:/5108.png);");
            ui->chk_curtain->setText("窗帘开");
        }
    }else if(type==DC_SERVE){
        rfid_state=SWITCH_OFF;
        ui->chk_rfid->setChecked(0);
        ui->chk_rfid->setText("门禁开");
    }
}
//安卓控制
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
    //判断安卓：单控/联动
    if(channel==11){
        ui->lab_ad->setText("单控");
    }else if(channel==12){
        ui->lab_ad->setText("联动");
    }else{
        deceive_control(SerialHandle->sensorTypeToBoardIdMap[type],pCmd,9);
    }
}
//命令转发
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
//写入日志
void Dialog::write_log(QString action){
    QFile f("log.txt");
    if(f.open(QIODevice::Append)){
        QTextStream in(&f);
        in<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ")<<action<<endl;
        f.close();
    }
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_3_clicked()
{
    this->close();
}
//单控
void Dialog::on_chk_fan_clicked(bool checked)
{
    if(fan_state!=SWITCH_ON){
        FanCmd(SWITCH_ON);
        write_log("风扇开");
    }else{
        FanCmd(SWITCH_OFF);
        write_log("风扇关");
    }
}

void Dialog::on_chk_warning_clicked(bool checked)
{
    if(warning_state!=SWITCH_ON){
        WarningCmd(SWITCH_ON);
        write_log("报警灯开");
    }else{
        WarningCmd(SWITCH_OFF);
        write_log("报警灯关");
    }
}

void Dialog::on_chk_lamp_clicked(bool checked)
{
    if(lamp_state!=SWITCH_ON){
        LampCmd(SWITCH_ON);
        write_log("射灯开");
    }else{
        LampCmd(SWITCH_OFF);
        write_log("射灯关");
    }
}

void Dialog::on_chk_rfid_clicked(bool checked)
{
    if(rfid_state!=SWITCH_ON){
        RfidCmd(SWITCH_ON);
        write_log("门禁开");
        ui->chk_rfid->setText("门禁关");
    }else{
        RfidCmd(SWITCH_OFF);
        write_log("门禁关");
    }
}

void Dialog::on_chk_curtain_clicked(bool checked)
{
    if(curtain_state!=CHANNEL_1){
        CurtainCmd(CHANNEL_1);
        write_log("窗帘开");
    }else{
        CurtainCmd(CHANNEL_3);
        write_log("窗帘关");
    }
}

void Dialog::on_btn_curtain_clicked()
{
    if(curtain_state!=CHANNEL_1){
        CurtainCmd(CHANNEL_1);
        write_log("窗帘开");
    }else{
        CurtainCmd(CHANNEL_3);
        write_log("窗帘关");
    }
}

void Dialog::on_btn_lamp_clicked()
{
    if(lamp_state!=SWITCH_ON){
        LampCmd(SWITCH_ON);
        write_log("射灯开");
    }else{
        LampCmd(SWITCH_OFF);
        write_log("射灯关");
    }
}

void Dialog::on_btn_warning_clicked()
{
    if(warning_state!=SWITCH_ON){
        WarningCmd(SWITCH_ON);
        write_log("报警灯开");
    }else{
        WarningCmd(SWITCH_OFF);
        write_log("报警灯关");
    }
}
//红外发射
void Dialog::on_radio_infrared_clicked()
{
    InfraredEmit(ui->sp_infrared->value());
}

void Dialog::on_radio_dandu_clicked()
{
    Modes=0;
}
//判断标签文本，打开模式
void Dialog::on_radio_mode_clicked()
{
    if(ui->lab_mode->text()=="离家模式"){
        Modes=1;
    }else if(ui->lab_mode->text()=="夜间模式"){
        Modes=2;
    }
}
//改变时间，判断模式
void Dialog::on_timeEdit_timeChanged(const QTime &date)
{
    //小时
    int hour=date.hour();
    //分钟
    int minute=date.minute();
    if((hour>=7&&hour<17)||(hour==17&&minute==0)){
        ui->lab_mode->setText("离家模式");
    }else{
        ui->lab_mode->setText("夜间模式");
    }
}
//日志显示
void Dialog::on_chk_log_clicked(bool checked)
{
    if(checked){
        QFile f("log.txt");
        if(f.open(QIODevice::ReadOnly)){
            QTextStream in(&f);
            ui->textEdit->setText(in.readAll());
            f.close();
        }
    }else{
        ui->textEdit->setText("");
    }
}
//模式判断
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
        break;
    }
}
//联动命令转发
void Dialog::ModeHandle(QString type, unsigned int command, unsigned int channel){
    if(type==FAN_SERVE){
        FanCmd(SWITCH_ON);
    }else if(type==LAMP_SERVE){
        LampCmd(command);
    }else if(type==WL_SERVE){
        WarningCmd(command);
    }else if(type==DC_SERVE){
        RfidCmd(command);
    }else if(type==CT_SERVE){
        CurtainCmd(channel);
    }else if(type==INFRARED_SERVE){
        InfraredEmit(command);
    }
}

int ld[5];
//联动
void Dialog::on_btn_ld_clicked()
{
    if(!mode_ld){
        if(!mod3->isRunning()){
            ld[0]=ui->ld1->currentIndex();
            ld[1]=ui->ld2->currentIndex();
            ld[2]=ui->ld3->text().toInt();
            ld[3]=ui->ld4->currentIndex();
            ld[4]=ui->ld5->currentIndex();
            connect(mod3,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
            mod3->start();
            ui->btn_ld->setText("关闭");
            mode_ld=1;
        }
    }else{
        if(mod3->isRunning()){
            disconnect(mod3,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
            mod3->ThreadQuit();
            ui->btn_ld->setText("开启");
            mode_ld=0;
        }
    }
}

void Dialog::on_btn_draw_clicked()
{
    Draw a;
    a.setWindowFlags(Qt::FramelessWindowHint);
    a.exec();
}
