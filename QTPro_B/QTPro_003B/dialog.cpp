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
volatile unsigned int lamp1_state;
volatile unsigned int lamp2_state;
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
    ScreenInit();

    Server=new TcpServer();

    myTcp=new TcpClientThread();
    myTcp->serverIP=ui->lab_ip->text();

    SerialHandle=new SerialDataHandle();

    Serial=new SerialThread();

}
//变量初始化
void Dialog::VarInit(){
    ReadNodeNum=0;
    dvd=8;
    air=1;
    tv=5;
    //模式状态
    af_mode=sm_mode=ld_mode=false;

    mod1=new Mode1(this);
    mod2=new Mode2(this);
    mod3=new Mode3(this);

    fan_state=SWITCH_OFF;
    lamp1_state=SWITCH_OFF;
    lamp2_state=SWITCH_OFF;
    warning_state=SWITCH_OFF;
    curtain_state=SWITCH_OFF;
    rfid_state=SWITCH_OFF;

    air_state=SWITCH_OFF;
    tv_state=SWITCH_OFF;
    dvd_state=SWITCH_OFF;
}
//界面初始化
void Dialog::ScreenInit(){
    ui->lab_ip->setText(ip);
    ui->lab_port->setText(port);
    ui->lab_wdl->hide();
    ui->w_lx->hide();
}
//板号配置
void Dialog::BoardInit(){
    SerialHandle->init();
}
//客户端监听
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
//数据上传，更新
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
            ui->btn_fan->setText("打开风扇");
            fan_state=SWITCH_OFF;
        }else{
            ui->btn_fan->setText("关闭风扇");
            fan_state=SWITCH_ON;
        }
    }else if(type==LAMP_SERVE){
        if(value==OFF){
            ui->btn_lamp->setText("打开射灯");
            lamp1_state=SWITCH_OFF;
            lamp2_state=SWITCH_OFF;
        }else if(value=="1"){
            lamp1_state=SWITCH_ON;
            lamp2_state=SWITCH_OFF;
        }else if(value=="2"){
            lamp1_state=SWITCH_OFF;
            lamp2_state=SWITCH_ON;
        }else{
            ui->btn_lamp->setText("关闭射灯");
            lamp1_state=SWITCH_ON;
            lamp2_state=SWITCH_ON;
        }
    }else if(type==WL_SERVE){
        if(value==OFF){
            ui->btn_warning->setText("打开报警灯");
            warning_state=SWITCH_OFF;
        }else{
            ui->btn_warning->setText("关闭报警灯");
            warning_state=SWITCH_ON;
        }
    }else if(type==CT_SERVE){
        if(value==ON){
            ui->btn_curtain->setText("关闭窗帘");
            curtain_state=CHANNEL_1;
        }else if(value==STOP){
            curtain_state=CHANNEL_2;
        }else if(value==CLOSE){
            ui->btn_curtain->setText("打开窗帘");
            curtain_state=CHANNEL_3;
        }
    }else if(type==DC_SERVE){
        rfid_state=SWITCH_OFF;
        ui->btn_rfid->setText("打开门禁");
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
    if(channel==11){
        ui->lab_andoird->setText("联动");
    }else if(channel==12){
        ui->lab_andoird->setText("单控");
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
//串口配置参数
QString zh="";
int zhi[3]={0,0,0};

void Dialog::on_btn_serial_clicked()
{
    if(ui->btn_serial->text()=="打开串口"){
        //串口参数设置
        zh=ui->cmb1->currentText();
        zhi[0]=ui->cmb2->currentText().toInt();
        zhi[1]=ui->cmb4->currentText().toInt();
        zhi[2]=ui->cmb3->currentIndex();
        //打开串口
        Serial->start();
        connect(Serial,SIGNAL(serialFinished(QByteArray)),this,SLOT(getStr(QByteArray)));
        connect(SerialHandle,SIGNAL(evt_deviceState(QString,QString,QString)),this,SLOT(upload(QString,QString,QString)));

        t2=new QTimer(this);
        connect(t2,SIGNAL(timeout()),this,SLOT(ReadNodeData()));
        t2->start(500);
        ui->btn_serial->setText("关闭串口");
    }else{
        ReadNodeNum=0;
        t2->stop();
        disconnect(Serial,SIGNAL(serialFinished(QByteArray)),this,SLOT(getStr(QByteArray)));
        disconnect(SerialHandle,SIGNAL(evt_deviceState(QString,QString,QString)),this,SLOT(upload(QString,QString,QString)));
        Serial->exit();
        ui->btn_serial->setText("打开串口");
    }
}
//tcp开启
void Dialog::on_btn_tcp_clicked()
{
    Server->listen(QHostAddress::Any,6001);
    connect(Server,SIGNAL(evt_configBoardId()),this,SLOT(BoardInit()));
    myTcp->start();
    connect(myTcp,SIGNAL(evt_socket_receive(QString,uint,uint,uint)),this,SLOT(app_control(QString,uint,uint,uint)));

    t1=new QTimer(this);
    connect(t1,SIGNAL(timeout()),this,SLOT(see()));
    t1->start(10000);
}
//单控
void Dialog::on_btn_lamp_clicked()
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

void Dialog::on_btn_rfid_clicked()
{
    if(rfid_state!=SWITCH_ON){
        RfidCmd(SWITCH_ON);
    }else{
        RfidCmd(SWITCH_OFF);
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

void Dialog::on_btn_curtain_clicked()
{
    if(curtain_state!=CHANNEL_1){
        CurtainCmd(CHANNEL_1);
    }else{
        CurtainCmd(CHANNEL_3);
    }
}

void Dialog::on_btn_air_clicked()
{
    if(air_state!=SWITCH_ON){
        air_state!=SWITCH_ON;
    }else{
        air_state!=SWITCH_OFF;
    }
    InfraredEmit(air);
}

void Dialog::on_btn_tv_clicked()
{
    if(tv_state!=SWITCH_ON){
        tv_state!=SWITCH_ON;
    }else{
        tv_state!=SWITCH_OFF;
    }
    InfraredEmit(tv);
}

void Dialog::on_btn_dvd_clicked()
{
    if(dvd_state!=SWITCH_ON){
        dvd_state!=SWITCH_ON;
    }else{
        dvd_state!=SWITCH_OFF;
    }
    InfraredEmit(dvd);
}
//打扫模式
void Dialog::on_btn_clean_clicked()
{
    LampCmd(SWITCH_ON,CHANNEL_1);
    Clean a;
    a.setWindowFlags(Qt::FramelessWindowHint);
    a.exec();
}
//请勿打扰
void Dialog::on_btn_wdl_clicked()
{
    if(ui->btn_wdl->text()=="请勿打扰"){
        LampCmd(SWITCH_ON,CHANNEL_2);
        ui->btn_wdl->setText("关闭请勿打扰");
        ui->btn_clean->setEnabled(0);
        ui->lab_wdl->show();
    }else{
        ui->btn_wdl->setText("请勿打扰");
        ui->btn_clean->setEnabled(1);
        ui->lab_wdl->hide();
    }
}
//联系前台
void Dialog::on_btn_lx_clicked()
{
    ui->w_lx->show();
}
//发送
void Dialog::on_btn_lxfs_clicked()
{
    ui->btn_lxfs->setText("发射中...");
    QTimer::singleShot(3000,this,SLOT(Lx()));
}
//发送延时
void Dialog::Lx(){
    ui->btn_lxfs->setText("发射成功");
}
//模式1
void Dialog::on_btn_mode1_clicked()
{
    if(!af_mode){
        if(!mod1->isRunning()){
            connect(mod1,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
            mod1->start();
            af_mode=true;
        }
    }else{
        if(mod1->isRunning()){
            disconnect(mod1,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
            mod1->ThreadQuit();
            af_mode=false;
        }
    }
}
//模式2
void Dialog::on_btn_mode2_clicked()
{
    if(!sm_mode){
        if(!mod2->isRunning()){
            connect(mod2,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
            mod2->start();
            sm_mode=true;
        }
    }else{
        if(mod2->isRunning()){
            disconnect(mod2,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
            mod2->ThreadQuit();
            sm_mode=false;
        }
    }
}
//模式3
int ld[3];
void Dialog::on_pushButton_clicked()
{
    if(!ld_mode){
        if(!mod3->isRunning()){
            //获取联动模式参数
            ld[0]=ui->ld1->currentIndex();
            ld[1]=ui->ld2->currentIndex();
            ld[2]=ui->ld3->text().toInt();
            connect(mod3,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
            mod3->start();
            ld_mode=true;
            ui->pushButton->setText("联动模式关闭");
        }
    }else{
        if(mod3->isRunning()){
            disconnect(mod3,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
            mod3->ThreadQuit();
            ld_mode=false;
            ui->pushButton->setText("联动模式开启");
            if(ui->chk1->isChecked())
                WarningCmd(SWITCH_OFF);
            if(ui->chk2->isChecked()){
                FanCmd(SWITCH_OFF);
            }
            if(ui->chk3->isChecked())
                CurtainCmd(CHANNEL_3);
            if(ui->chk4->isChecked())
                LampCmd(SWITCH_OFF,CHANNEL_ALL);
        }
    }
}
//获取要打开的控件
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
//模式判断
void Dialog::ModeHandle(QString type, unsigned int command, unsigned int channel){
    if(type==FAN_SERVE){
        FanCmd(command);
    }else if(type==LAMP_SERVE){
        LampCmd(command,channel);
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
void Dialog::on_btn_draw_clicked()
{
    Draw a;
    a.setWindowFlags(Qt::FramelessWindowHint);
    a.exec();
}
