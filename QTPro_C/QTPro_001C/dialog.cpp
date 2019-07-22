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
volatile unsigned int rfid_state;
volatile unsigned int curtain_state;
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

    Server=new TcpServer(this);

    myTcp=new TcpClientThread();
    myTcp->serverIP=ip;

    SerialHandle=new SerialDataHandle(this);

    Serial=new SerialThread();
//模式
    t4=new QTimer(this);
    connect(t4,SIGNAL(timeout()),this,SLOT(Mode()));
    t4->start(1000);
//画图
    t5=new QTimer(this);
    connect(t5,SIGNAL(timeout()),this,SLOT(play()));
    t5->start(1000);
}
//变量初始化
void Dialog::VarInit(){
    ReadNodeNum=0;
    temp_max=ill_max=0;
    Modes=0;
    tv=5;
    dvd=8;
    air=1;

    N=400;

    mod1=new Mode1(this);
    mod2=new Mode2(this);
    mod3=new Mode3(this);
    mod4=new Mode4(this);

    fan_state=SWITCH_OFF;
    lamp1_state=SWITCH_OFF;
    lamp2_state=SWITCH_OFF;
    warning_state=SWITCH_OFF;
    rfid_state=SWITCH_OFF;
    curtain_state=SWITCH_OFF;
    air_state=SWITCH_OFF;
    tv_state=SWITCH_OFF;
    dvd_state=SWITCH_OFF;
}
//界面初始化
void Dialog::ScreenInit(){
    ui->lab_ip->setText(ip);
    ui->lab_port->setText(port);
    ui->lab_draw->installEventFilter(this);
}
//监测客户端
void Dialog::see(){
    if(!myTcp->getTcpClientFlag())
        myTcp->start();
}
//数据处理
void Dialog::getStr(QByteArray str){
    SerialHandle->receive(str);
}
//配置板号
void Dialog::BoardInit(){
    SerialHandle->init();
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
        t1->stop();
        t2=new QTimer(this);
        connect(t2,SIGNAL(timeout()),this,SLOT(GetNodeData()));
        t2->start(500);
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
        t2->stop();
    }
}
//数据更新，上传
void Dialog::upload(const QString &type, const QString &cmdCode, const QString &value){
    if(myTcp->getTcpClientFlag())
        myTcp->upload(type,cmdCode,value);
    if(type==TEMP_SERVE){
        ui->lab_temp->setText(value);
        temp_value=value.toFloat();
        //最大值比较
        if(temp_max<temp_value){
            temp_max=temp_value;
        }
        if(ui->cmb_max->currentIndex()==0){
            ui->led_max->setText("最大值:"+QString::number(temp_max));
        }
    }else if(type==HUM_SERVE){
        ui->lab_hum->setText(value);
        hum_value=value.toFloat();
    }else if(type==ILL_SERVE){
        ui->lab_ill->setText(value);
        ill_value=value.toFloat();
        if(ill_max<ill_value){
            ill_max=ill_value;
        }
        if(ui->cmb_max->currentIndex()==1){
            ui->led_max->setText("最大值:"+QString::number(ill_max));
        }
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
    }else if(type==LAMP_SERVE){//射灯单独开关
        if(value==OFF){
            ui->btn_lamp->setText("打开射灯");
            lamp1_state=SWITCH_OFF;
            lamp2_state=SWITCH_OFF;
        }else if(value=="1"){
            ui->btn_lamp->setText("关闭射灯");
            lamp1_state=SWITCH_ON;
            lamp2_state=SWITCH_OFF;
        }else if(value=="2"){
            ui->btn_lamp->setText("关闭射灯");
            lamp1_state=SWITCH_OFF;
            lamp2_state=SWITCH_ON;
        }else{
            ui->btn_lamp->setText("关闭射灯");
            lamp1_state=SWITCH_ON;
            lamp2_state=SWITCH_ON;
        }
    }else if(type==WL_SERVE){
        if(value==OFF){
            ui->btn_warning->setStyleSheet("border-image: url(:/3204.png);");
            warning_state=SWITCH_OFF;
        }else{
            ui->btn_warning->setStyleSheet("border-image: url(:/3205.png);");
            warning_state=SWITCH_ON;
        }
    }else if(type==CT_SERVE){
        if(value==ON){
            ui->btn_curtain->setStyleSheet("border-image: url(:/3203.png);");
            curtain_state=CHANNEL_1;
        }else if(value==STOP){
            curtain_state=CHANNEL_2;
        }else if(value==CLOSE){
            ui->btn_curtain->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
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
//命令发送
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
//写日志
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

void Dialog::on_pushButton_9_clicked()
{
    this->close();
}
QString zh="";
int zhi[3]={0,0,0};
//串口
void Dialog::on_btn_serial_clicked()
{
    if(ui->btn_serial->text()=="打开串口"){
        zh=ui->cmb1->currentText();
        zhi[0]=ui->cmb2->currentText().toInt();
        zhi[1]=ui->cmb4->currentText().toInt();
        zhi[2]=ui->cmb3->currentIndex();

        Serial->start();
        connect(Serial,SIGNAL(serialFinished(QByteArray)),this,SLOT(getStr(QByteArray)));
        connect(SerialHandle,SIGNAL(evt_deviceState(QString,QString,QString)),this,SLOT(upload(QString,QString,QString)));
        ReadNodeNum=0;
        t1=new QTimer(this);
        connect(t1,SIGNAL(timeout()),this,SLOT(ReadNodeData()));
        t1->start(500);

        ui->btn_serial->setText("关闭串口");
    }else{
        ReadNodeNum=0;
        t1->stop();
        disconnect(Serial,SIGNAL(serialFinished(QByteArray)),this,SLOT(getStr(QByteArray)));
        disconnect(SerialHandle,SIGNAL(evt_deviceState(QString,QString,QString)),this,SLOT(upload(QString,QString,QString)));
        Serial->exit();
        ui->btn_serial->setText("打开串口");
    }
}
//服务器
void Dialog::on_btn_tcp_clicked()
{
    if(ui->btn_tcp->text()=="连接服务器"){
        myTcp->start();
        connect(myTcp,SIGNAL(evt_socket_receive(QString,uint,uint,uint)),this,SLOT(app_control(QString,uint,uint,uint)));
        t3=new QTimer(this);
        connect(t3,SIGNAL(timeout()),this,SLOT(see()));
        t3->start(10000);
        ui->btn_tcp->setText("已连接服务器");
    }else{
        t3->stop();
        disconnect(myTcp,SIGNAL(evt_socket_receive(QString,uint,uint,uint)),this,SLOT(app_control(QString,uint,uint,uint)));
        myTcp->exit();
        ui->btn_tcp->setText("连接服务器");
    }
}
//监听
void Dialog::on_btn_server_clicked()
{
    if(ui->btn_server->text()=="监听"){
        Server->listen(QHostAddress::Any,6001);
        connect(Server,SIGNAL(evt_configBoardId()),this,SLOT(BoardInit()));
        ui->btn_server->setText("已监听");
    }else{
        disconnect(Server,SIGNAL(evt_configBoardId()),this,SLOT(BoardInit()));
        Server->close();
        ui->btn_server->setText("监听");
    }
}
//单控
void Dialog::on_btn_tv_clicked()
{
    Modes=0;
    if(tv_state!=SWITCH_ON){
        tv_state=SWITCH_ON;
        write_log("打开电视");
    }else{
        tv_state=SWITCH_OFF;
        write_log("关闭电视");
    }
    InfraredEmit(tv);
}

void Dialog::on_btn_air_clicked()
{
    Modes=0;
    if(air_state!=SWITCH_ON){
        air_state=SWITCH_ON;
        write_log("打开空调");
    }else{
        air_state=SWITCH_OFF;
        write_log("关闭空调");
    }
    InfraredEmit(air);
}

void Dialog::on_btn_rfid_clicked()
{
    Modes=0;
    RfidCmd(SWITCH_ON);
    write_log("无线开门");
}

void Dialog::on_btn_fan_clicked()
{
    Modes=0;
    if(fan_state!=SWITCH_ON){
        FanCmd(SWITCH_ON);
        write_log("打开风扇");
    }else{
        FanCmd(SWITCH_OFF);
        write_log("关闭风扇");
    }
}

void Dialog::on_btn_lamp_clicked()
{
    Modes=0;
    if(lamp1_state!=SWITCH_ON||lamp2_state!=SWITCH_ON){
        LampCmd(SWITCH_ON,CHANNEL_ALL);
        write_log("打开射灯");
    }else{
        LampCmd(SWITCH_OFF,CHANNEL_ALL);
        write_log("关闭射灯");
    }
}

void Dialog::on_btn_warning_clicked()
{
    Modes=0;
    if(warning_state!=SWITCH_ON){
        WarningCmd(SWITCH_ON);
        write_log("打开报警灯");
    }else{
        WarningCmd(SWITCH_OFF);
        write_log("关闭报警灯");
    }
}

void Dialog::on_btn_curtain_clicked()
{
    Modes=0;
    if(curtain_state!=CHANNEL_1){
        CurtainCmd(CHANNEL_1);
        write_log("打开窗帘");
    }else{
        CurtainCmd(CHANNEL_3);
        write_log("关闭窗帘");
    }
}
//最大值
void Dialog::on_cmb_max_currentIndexChanged(int index)
{
    switch(index){
    case 0://温度
        ui->led_max->setText("最大值:"+QString::number(temp_max));
        break;
    case 1://光照
        ui->led_max->setText("最大值:"+QString::number(ill_max));
        break;
    }
}

//日志
void Dialog::on_chk_log_clicked(bool checked)
{
    mylog a;
    a.setWindowFlags(Qt::FramelessWindowHint);
    a.exec();
    ui->chk_log->setChecked(0);
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
        if(mod3->isRunning()){
            disconnect(mod3,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
            mod3->ThreadQuit();
        }
        if(mod4->isRunning()){
            disconnect(mod4,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
            mod4->ThreadQuit();
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
            connect(mod4,SIGNAL(mod(QString,uint,uint)),this,SLOT(ModeHandle(QString,uint,uint)));
            mod4->start();
        }
        break;
    }
}
//模式命令转发
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
//画图事件过滤
bool Dialog::eventFilter(QObject *a, QEvent *event){
    if(a==ui->lab_draw&&event->type()==QEvent::Paint)
        mydraw();
    return QWidget::eventFilter(a,event);
}
//画图数据写入
void Dialog::play(){
    if(temp_value>250&&temp_value>ill_value){
        N=temp_value+100;
        if(N>1000){
            N=1000;
        }
    }else{
        N=400;
    }
    if(ill_value>250&&ill_value>temp_value){
        N=ill_value+100;
        if(N>1000){
            N=1000;
        }
    }else{
        N=400;
    }
    temp_v<<(float)temp_value;
    ill_v<<(float)ill_value;
    if(temp_v.count()>4)
        temp_v.remove(0);
    if(ill_v.count()>4)
        ill_v.remove(0);
    update();
}
//画图
void Dialog::mydraw(){
    QPainter q(ui->lab_draw);
    float px=50;float py=100;
    float K=N/py;
    QPen p1,p2;
    p1.setColor(Qt::red);
    p2.setColor(Qt::blue);
    q.setRenderHint(QPainter::Antialiasing,true);
    for(int i=0;i<3;i++){
        q.drawText(0,py-i*50+20,QString::number((int)(i*50*K)));
        q.drawLine(px,py-i*50+20,250,py-i*50+20);
    }
    for(int i=1;i<=4;i++){
        q.drawText(px+i*40,py+40,QString::number(i));
    }
    q.setPen(p1);
    q.drawLine(px,py+70,px+40,py+70);
    for(int i=2;i<=temp_v.count();i++){
        q.drawLine(px+(i-1)*40,py-temp_v[i-2]/K+20,px+i*40,py-temp_v[i-1]/K+20);
    }
    q.setPen(p2);
    q.drawLine(px+100,py+70,px+100+40,py+70);
    for(int i=2;i<=ill_v.count();i++){
        q.drawLine(px+(i-1)*40,py-ill_v[i-2]/K+20,px+i*40,py-ill_v[i-1]/K+20);
    }

}

