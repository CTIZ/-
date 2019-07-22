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
    myTcp->serverIP=ip;
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

    ui->lab_draw->installEventFilter(this);

    t4=new QTimer(this);
    connect(t4,SIGNAL(timeout()),this,SLOT(play()));
    t4->start(1000);
}
void Dialog::VarInit()
{
    ReadNodeNum=0;
    dvd=8;
    tv=5;
    air=1;

    ill_num<<1<<1<<1;
    temp_num<<1<<1<<1;
    draw_f=0;

    mod=new Mode(this);

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
void Dialog::see(){
    if(!myTcp->getTcpClientFlag())
        myTcp->start();
}
void Dialog::getStr(QByteArray str){
    SerialHandle->receive(str);
}
void Dialog::BoardInit(){
    SerialHandle->init();
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
        ui->v_temp->setValue(value.toFloat());
        temp_value=value.toFloat();
    }else if(type==HUM_SERVE){
        ui->v_hum->setValue(value.toFloat());
        hum_value=value.toFloat();
    }else if(type==ILL_SERVE){
        ui->v_ill->setValue(value.toFloat());
        ill_value=value.toFloat();
    }else if(type==AP_SERVE){
        ui->v_air->setValue(value.toFloat());
        air_value=value.toFloat();
    }else if(type==CO2_SERVE){
        co2_value=value.toInt();
    }else if(type==GAS_SERVE){
        ui->v_gas->setValue(value.toInt());
        gas_value=value.toInt();
    }else if(type==PM25_SERVE){
        ui->v_pm->setValue(value.toInt());
        pm_value=value.toInt();
    }else if(type==SMK_SERVE){
        ui->v_smoke->setValue(value.toInt());
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
        }else{
            ui->chk_fan->setChecked(1);
            fan_state=SWITCH_ON;
        }
    }else if(type==LAMP_SERVE){
        if(value==OFF){
            ui->btn_lamp->setText("全开");
            lamp1_state=SWITCH_OFF;
            lamp2_state=SWITCH_OFF;
        }else if(value=="1"){
            lamp1_state=SWITCH_ON;
            lamp2_state=SWITCH_OFF;
        }else if(value=="2"){
            lamp1_state=SWITCH_OFF;
            lamp2_state=SWITCH_ON;
        }else{
            ui->btn_lamp->setText("全关");
            lamp1_state=SWITCH_ON;
            lamp2_state=SWITCH_ON;
        }
    }else if(type==WL_SERVE){
        if(value==OFF){
            ui->chk_warning->setChecked(0);
            warning_state=SWITCH_OFF;
        }else{
            ui->chk_warning->setChecked(1);
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
        ui->chk_rfid->setChecked(0);
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

void Dialog::on_chk_warning_clicked(bool checked)
{
    if(checked){
        WarningCmd(SWITCH_ON);
    }else{
        WarningCmd(SWITCH_OFF);
    }
}

void Dialog::on_chk_fan_clicked(bool checked)
{
    if(checked){
        FanCmd(SWITCH_ON);
    }else{
        FanCmd(SWITCH_OFF);
    }
}

void Dialog::on_chk_rfid_clicked(bool checked)
{
    if(checked){
        RfidCmd(SWITCH_ON);
    }else{
        RfidCmd(SWITCH_OFF);
    }
}

void Dialog::on_radio_tv_clicked()
{
    if(tv_state!=SWITCH_ON){
        tv_state=SWITCH_ON;
    }else{
        tv_state=SWITCH_OFF;
    }
    InfraredEmit(tv);
}

void Dialog::on_radio_air_clicked()
{
    if(air_state!=SWITCH_ON){
        air_state=SWITCH_ON;
    }else{
        air_state=SWITCH_OFF;
    }
    InfraredEmit(air);
}

void Dialog::on_radio_dvd_clicked()
{
    if(dvd_state!=SWITCH_ON){
        dvd_state=SWITCH_ON;
    }else{
        dvd_state=SWITCH_OFF;
    }
    InfraredEmit(dvd);
}

void Dialog::on_cmb_infrared_currentIndexChanged(int index)
{
    if(index==tv){
        on_radio_tv_clicked();
    }else if(index==air){
        on_radio_air_clicked();
    }else if(index==dvd){
        on_radio_dvd_clicked();
    }else{
        InfraredEmit(index);
    }
}

void Dialog::on_btn_curtain_on_clicked()
{
    if(curtain_state!=CHANNEL_1)
        CurtainCmd(CHANNEL_1);
}

void Dialog::on_btn_curtain_stop_clicked()
{
    if(curtain_state!=CHANNEL_2)
        CurtainCmd(CHANNEL_2);
}

void Dialog::on_btn_curtain_off_clicked()
{
    if(curtain_state!=CHANNEL_3)
        CurtainCmd(CHANNEL_3);
}

void Dialog::on_btn_lamp1_clicked()
{
    if(lamp1_state!=SWITCH_ON){
        LampCmd(SWITCH_ON,CHANNEL_1);
    }else{
        LampCmd(SWITCH_OFF,CHANNEL_1);
    }
}

void Dialog::on_btn_lamp2_clicked()
{
    if(lamp2_state!=SWITCH_ON){
        LampCmd(SWITCH_ON,CHANNEL_2);
    }else{
        LampCmd(SWITCH_OFF,CHANNEL_2);
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
void Dialog::mySql(QString action){
    QSqlQuery q;
    QTime time=QTime::currentTime();
    int hour=time.hour();
    int minute=time.minute();
    int second=time.second();
    QString tm=QString::number(hour)+"点"+QString::number(minute)+"分"+QString::number(second)+"秒";
    q.exec("insert into ld values('"+tm+"','"+ui->ld1->currentText()+ui->ld2->currentText()+ui->ld3->text()+"','"+action+"')");
}

void Dialog::on_btn_save_clicked()
{
    switch(ui->ld1->currentIndex()){
    case 1://温度
        switch(ui->ld2->currentIndex()){
        case 1://>
            mySql("空调开");
            break;
        case 2://<
            mySql("空调关");
            break;
        }
        break;
    case 2://烟雾
        switch(ui->ld2->currentIndex()){
        case 1://>
            mySql("风扇开");
            break;
        case 2://<
            mySql("风扇关");
            break;
        }
        break;
    case 3://光照
        switch(ui->ld2->currentIndex()){
        case 1://>
            mySql("窗帘关");
            break;
        case 2://<
            mySql("窗帘开");
            break;
        }
        break;
    }
}

void Dialog::on_ben_chakan_clicked()
{
    ld_guanli a;
    a.exec();
}

void Dialog::on_chk_ld_clicked(bool checked)
{
    if(checked){
        if(!mod->isRunning()){
            connect(mod,SIGNAL(mod(QString,uint,uint,QString)),this,SLOT(ModeHandle(QString,uint,uint,QString)));
            mod->start();
        }
    }else{
        if(mod->isRunning()){
            disconnect(mod,SIGNAL(mod(QString,uint,uint,QString)),this,SLOT(ModeHandle(QString,uint,uint,QString)));
            mod->ThreadQuit();
            ui->textEdit->setText("");
        }
    }
}
void Dialog::ModeHandle(QString type, unsigned int command, unsigned int channel, QString value){
    if(type==INFRARED_SERVE){
        InfraredEmit(channel);
        if(air_state==SWITCH_ON){
            ui->textEdit->append("温度大于"+value+".执行打开空调命令");
        }else if(air_state==SWITCH_OFF){
            ui->textEdit->append("温度小于"+value+".执行关闭空调命令");
        }
    }else if(type==FAN_SERVE){
        FanCmd(command);
        if(command==SWITCH_ON){
            ui->textEdit->append("烟雾大于"+value+".执行打开风扇命令");
        }else if(command==SWITCH_OFF){
            ui->textEdit->append("烟雾小于"+value+".执行关闭风扇命令");
        }
    }else if(type==CT_SERVE){
        CurtainCmd(channel);
        if(channel==CHANNEL_1){
            ui->textEdit->append("光照小于"+value+".执行打开窗帘命令");
        }else if(channel==CHANNEL_3){
            ui->textEdit->append("光照大于"+value+".执行关闭窗帘命令");
        }
    }
}

void Dialog::on_cmb_draw_currentIndexChanged(int index)
{
    if(index==1){
        draw_f=1;
        ui->lab_title->setText("温度数据一小时统计图");
        ui->lab_num1->setText("0-19");
        ui->lab_num2->setText("19-29");
        ui->lab_num3->setText("29-39");
        ui->lab_dw->setText("单位：℃");
    }else if(index==2){
        draw_f=2;
        ui->lab_title->setText("光照数据一小时统计图");
        ui->lab_num1->setText("0-300");
        ui->lab_num2->setText("301-699");
        ui->lab_num3->setText("700-1500");
        ui->lab_dw->setText("单位：Lx");
    }else{
        draw_f=0;
        ui->lab_title->setText("");
        ui->lab_num1->setText("");
        ui->lab_num2->setText("");
        ui->lab_num3->setText("");
        ui->lab_dw->setText("");
    }
}
void Dialog::play(){
    ui->lab_time->setText(QTime::currentTime().toString("hh:mm"));
    if(temp_value>=0&&temp_value<=19){
        temp_num[0]++;
    }else if(temp_value>=20&&temp_value<=29){
        temp_num[1]++;
    }else if(temp_value>=29&&temp_value<=39){
        temp_num[2]++;
    }

    if(ill_value>=0&&ill_value<=300){
        ill_num[0]++;
    }else if(ill_value>=301&&ill_value<=699){
        ill_num[1]++;
    }else if(ill_value>=700&&ill_value<=1500){
        ill_num[2]++;
    }
//    for(int i=0;i<3;i++){
//        d_temp<<temp_num[i];
//        d_ill<<ill_num[i];
    //    }

    update();
}
bool Dialog::eventFilter(QObject *a, QEvent *event){
    if(a==ui->lab_draw&&event->type()==QEvent::Paint)
        mydraw();
    return QWidget::eventFilter(a,event);
}
void Dialog::mydraw(){
    QPainter q(ui->lab_draw);
    d_color<<QBrush(Qt::blue);
    d_color<<QBrush(Qt::red);
    d_color<<QBrush(Qt::green);
    int radius=150;
    QRect rect(40,20,radius,radius);

    float temp_sum=temp_num[0]+temp_num[1]+temp_num[2];
    float ill_sum=ill_num[0]+ill_num[1]+ill_num[2];

    float angle;

    if(draw_f==1){
        float pos=0;
        for(int i=0;i<temp_num.count();i++){
            angle=temp_num[i]/temp_sum*16*360;
            q.setBrush(d_color[i]);
            q.drawPie(rect,pos,angle);
            pos+=angle;
        }
        pos=0;
        for(int i=0;i<temp_num.count();++i){
            angle=temp_num[i]/temp_sum*16*360;
            double labAngle=(pos+angle/2)/16;
            double tx=rect.width()/2*qCos(labAngle/360*2*3.14);
            double ty=-rect.width()/2*qSin(labAngle/360*2*3.14);
            q.drawText(QPoint(tx/2,ty/2)+rect.center(),QString::number((int)(temp_num[i]/temp_sum*100+0.5f)));
            pos+=angle;
        }
    }else if(draw_f==2){
        float pos=0;
        for(int i=0;i<ill_num.count();++i){
            angle=ill_num[i]/ill_sum*16*360;
            q.setBrush(d_color[i]);
            q.drawPie(rect,pos,angle);
            pos+=angle;
        }
        pos=0;
        for(int i=0;i<ill_num.count();++i){
            angle=ill_num[i]/ill_sum*16*360;
            double labAngle=(pos+angle/2)/16;
            double tx=rect.width()/2*qCos(labAngle/360*2*3.14);
            double ty=-rect.width()/2*qSin(labAngle/360*2*3.14);
            q.drawText(QPoint(tx/2,ty/2)+rect.center(),QString::number((int)(ill_num[i]/ill_sum*100+0.5f)));
            pos+=angle;
        }
    }
    d_color.clear();
}
