#include "dialog.h"
#include "ui_dialog.h"

//变量定义
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

volatile unsigned int dvd_state;
volatile unsigned int tv_state;
volatile unsigned int air_state;


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    VarInit();
//服务
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

//变量初始化
void Dialog::VarInit(){
    ReadNodeNum=0;

    air=1;
    dvd=2;
    tv=3;

    mod1=new Mode(this);

    fan_state=SWITCH_OFF;
    lamp_state=SWITCH_OFF;
    warning_state=SWITCH_OFF;
    curtain_state=SWITCH_OFF;
    rfid_state=SWITCH_OFF;

    dvd_state=SWITCH_OFF;
    tv_state=SWITCH_OFF;
    air_state=SWITCH_OFF;
}
//客户端检测
void Dialog::see(){
    if(!myTcp->getTcpClientFlag())
        myTcp->start();
}
//板号配置
void Dialog::BoardInit(){
    SerialHandle->init();
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
    //上传
    if(myTcp->getTcpClientFlag())
        myTcp->upload(type,cmdCode,value);
    //状态更新
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
            ui->btn_fan->setText("风扇打开");
            ui->icon_fan->setStyleSheet("border-image: url(:/0119.png);");
            fan_state=SWITCH_OFF;
        }else{
            ui->btn_fan->setText("风扇关闭");
            ui->icon_fan->setStyleSheet("border-image: url(:/0120.png);");
            fan_state=SWITCH_ON;
        }
    }else if(type==LAMP_SERVE){
        if(value==OFF){
            ui->btn_lamp->setText("射灯打开");
            ui->icon_lamp->setStyleSheet("border-image: url(:/0125.png);");
            lamp_state=SWITCH_OFF;
        }else{
            ui->btn_lamp->setText("射灯关闭");
            ui->icon_lamp->setStyleSheet("border-image: url(:/0126.png);");
            lamp_state=SWITCH_ON;
        }
    }else if(type==WL_SERVE){
        if(value==OFF){
            ui->btn_warning->setStyleSheet("border-image: url(:/0112.png);");

            warning_state=SWITCH_OFF;
        }else{
            ui->btn_warning->setStyleSheet("border-image: url(:/0111.png);");

            warning_state=SWITCH_ON;
        }
    }else if(type==CT_SERVE){
        if(value==ON){
            ui->btn_curtain->setText("窗帘关闭");
            ui->icon_curtain->setStyleSheet("border-image: url(:/0114.png);");
            curtain_state=CHANNEL_1;
        }else if(value==STOP){
            curtain_state=CHANNEL_2;
        }else if(value==CLOSE){
            ui->btn_curtain->setText("窗帘打开");
            ui->icon_curtain->setStyleSheet("border-image: url(:/0113.png);");
            curtain_state=CHANNEL_3;
        }
    }else if(type==DC_SERVE){
        rfid_state=SWITCH_OFF;
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
    deceive_control(SerialHandle->sensorTypeToBoardIdMap[type],pCmd,9);
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


Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_2_clicked()
{
    this->close();
}
//单控
void Dialog::on_icon_curtain_clicked()
{
    if(curtain_state!=CHANNEL_1){
        CurtainCmd(CHANNEL_1);
    }else{
        CurtainCmd(CHANNEL_3);
    }
}

void Dialog::on_btn_curtain_clicked()
{
    if(curtain_state!=CHANNEL_1){
        CurtainCmd(CHANNEL_1);
    }else{
        CurtainCmd(CHANNEL_3);
    }
}

void Dialog::on_icon_fan_clicked()
{
    if(fan_state!=SWITCH_ON){
        FanCmd(SWITCH_ON);
    }else{
        FanCmd(SWITCH_OFF);
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

void Dialog::on_icon_lamp_clicked()
{
    if(lamp_state!=SWITCH_ON){
        LampCmd(SWITCH_ON);
    }else{
        LampCmd(SWITCH_OFF);
    }
}

void Dialog::on_btn_lamp_clicked()
{
    if(lamp_state!=SWITCH_ON){
        LampCmd(SWITCH_ON);
    }else{
        LampCmd(SWITCH_OFF);
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

void Dialog::on_btn_rfid_clicked()
{
    if(rfid_state!=SWITCH_ON){
        RfidCmd(SWITCH_ON);
    }else{
        RfidCmd(SWITCH_OFF);
    }
}

void Dialog::on_icon_tv_clicked()
{
    if(tv_state!=SWITCH_ON){
        tv_state=SWITCH_ON;
        ui->btn_tv->setText("电视机关闭");
        ui->icon_tv->setStyleSheet("border-image: url(:/0116.png);");
    }else{
        tv_state=SWITCH_OFF;
        ui->btn_tv->setText("电视机打开");
        ui->icon_tv->setStyleSheet("border-image: url(:/0115.png);");
    }
    InfraredEmit(tv);
}

void Dialog::on_btn_tv_clicked()
{
    if(tv_state!=SWITCH_ON){
        tv_state=SWITCH_ON;
        ui->btn_tv->setText("电视机关闭");
        ui->icon_tv->setStyleSheet("border-image: url(:/0116.png);");
    }else{
        tv_state=SWITCH_OFF;
        ui->btn_tv->setText("电视机打开");
        ui->icon_tv->setStyleSheet("border-image: url(:/0115.png);");
    }
    InfraredEmit(tv);
}

void Dialog::on_icon_dvd_clicked()
{
    if(dvd_state!=SWITCH_ON){
        dvd_state=SWITCH_ON;
        ui->btn_dvd->setText("DVD关闭");
        ui->icon_dvd->setStyleSheet("border-image: url(:/0118.png);");
    }else{
        dvd_state=SWITCH_OFF;
        ui->btn_dvd->setText("DVD打开");
        ui->icon_dvd->setStyleSheet("border-image: url(:/0117.png);");
    }
    InfraredEmit(dvd);
}

void Dialog::on_btn_dvd_clicked()
{
    if(dvd_state!=SWITCH_ON){
        dvd_state=SWITCH_ON;
        ui->btn_dvd->setText("DVD关闭");
        ui->icon_dvd->setStyleSheet("border-image: url(:/0118.png);");
    }else{
        dvd_state=SWITCH_OFF;
        ui->btn_dvd->setText("DVD打开");
        ui->icon_dvd->setStyleSheet("border-image: url(:/0117.png);");
    }
    InfraredEmit(dvd);
}

void Dialog::on_icon_air_clicked()
{
    if(air_state!=SWITCH_ON){
        air_state=SWITCH_ON;
        ui->btn_air->setText("空调关闭");
        ui->icon_air->setStyleSheet("border-image: url(:/013.png);");
    }else{
        air_state=SWITCH_OFF;
        ui->btn_air->setText("空调打开");
        ui->icon_air->setStyleSheet("border-image: url(:/0122.png);");
    }
    InfraredEmit(air);
}

void Dialog::on_btn_air_clicked()
{
    if(air_state!=SWITCH_ON){
        air_state=SWITCH_ON;
        ui->btn_air->setText("空调关闭");
        ui->icon_air->setStyleSheet("border-image: url(:/013.png);");
    }else{
        air_state=SWITCH_OFF;
        ui->btn_air->setText("空调打开");
        ui->icon_air->setStyleSheet("border-image: url(:/0122.png);");
    }
    InfraredEmit(air);
}

//红外发送
void Dialog::on_sp_infrared_valueChanged(int arg1)
{
    if(arg1==tv){
        on_btn_tv_clicked();
    }else if(arg1==air){
        on_btn_air_clicked();
    }else if(arg1==dvd){
        on_btn_dvd_clicked();
    }else{
        InfraredEmit(arg1);
    }

}

//4个模式的命令存储
int ld1[5];
int ld2[5];
int ld3[5];
int ld4[5];
//模式命令存储
void Dialog::on_btn_ok_clicked()
{
    switch(ui->cmb_smode->currentIndex()){
    case 0://模式1
        ld1[0]=ui->ld1->currentIndex();
        ld1[1]=ui->ld2->currentIndex();
        ld1[2]=ui->ld3->value();
        ld1[3]=ui->ld4->currentIndex();
        ld1[4]=ui->ld5->currentIndex();
        break;
    case 1://模式2
        ld2[0]=ui->ld1->currentIndex();
        ld2[1]=ui->ld2->currentIndex();
        ld2[2]=ui->ld3->value();
        ld2[3]=ui->ld4->currentIndex();
        ld2[4]=ui->ld5->currentIndex();
        break;
    case 2://模式3
        ld3[0]=ui->ld1->currentIndex();
        ld3[1]=ui->ld2->currentIndex();
        ld3[2]=ui->ld3->value();
        ld3[3]=ui->ld4->currentIndex();
        ld3[4]=ui->ld5->currentIndex();
        break;
    case 3://模式4
        ld4[0]=ui->ld1->currentIndex();
        ld4[1]=ui->ld2->currentIndex();
        ld4[2]=ui->ld3->value();
        ld4[3]=ui->ld4->currentIndex();
        ld4[4]=ui->ld5->currentIndex();
        break;
    }
}
//模式清空
void Dialog::on_btn_clear_clicked()
{
    switch(ui->cmb_smode->currentIndex()){
    case 0:
        ld1[0]=0;
        ld1[1]=0;
        ld1[2]=0;
        ld1[3]=0;
        ld1[4]=0;
        break;
    case 1:
        ld2[0]=0;
        ld2[1]=0;
        ld2[2]=0;
        ld2[3]=0;
        ld2[4]=0;
        break;
    case 2:
        ld3[0]=0;
        ld3[1]=0;
        ld3[2]=0;
        ld3[3]=0;
        ld3[4]=0;
        break;
    case 3:
        ld4[0]=0;
        ld4[1]=0;
        ld4[2]=0;
        ld4[3]=0;
        ld4[4]=0;
        break;
    }
}

int Modes;
//模式开启/关闭
void Dialog::on_chk_mode_clicked(bool checked)
{
    if(checked){
        if(!mod1->isRunning()){
            Modes=ui->cmb_zmode->currentIndex();//判断开启哪个模式
            connect(mod1,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
            mod1->start();
        }
    }else{
        if(mod1->isRunning()){
            disconnect(mod1,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
            mod1->ThreadQuit();
        }
    }
}
//模式命令转发
void Dialog::ModeHandle(QString type, unsigned int command, unsigned int channel){
    if(type==FAN_SERVE){
        FanCmd(command);
    }else if(type==LAMP_SERVE){
        LampCmd(command);
    }else if(type==WL_SERVE){
        WarningCmd(command);
    }else if(type==CT_SERVE){
        CurtainCmd(channel);
    }else if(type==DC_SERVE){
        RfidCmd(command);
    }else if(type==INFRARED_SERVE){
        InfraredEmit(channel);
    }
}
//画图
void Dialog::on_pushButton_clicked()
{
    Draw a;
    a.exec();
}
