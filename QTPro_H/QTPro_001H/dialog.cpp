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

    SerialHandle=new  SerialDataHandle(this);
    connect(SerialHandle,SIGNAL(evt_deviceState(QString,QString,QString)),this,SLOT(upload(QString,QString,QString)));
    t2=new QTimer(this);
    connect(t2,SIGNAL(timeout()),this,SLOT(ReadNodeData()));
    t2->start(500);
//模式
    t4=new QTimer(this);
    connect(t4,SIGNAL(timeout()),this,SLOT(Mode()));
    t4->start(1000);
//画图
    t5=new QTimer(this);
    connect(t5,SIGNAL(timeout()),this,SLOT(play()));
t5->start(1000);
}
void Dialog::VarInit(){
    //过滤
    ui->lab_draw->installEventFilter(this);
//温度数组
    num_temp[0]=1;
    num_temp[1]=1;
    num_temp[2]=1;
//光照数组
    num_ill[0]=1;
    num_ill[1]=1;
    num_ill[2]=1;

    ReadNodeNum=0;
    //画温度/光照判断
    drawFlag=0;
    //红外
    dvd=8;
    air=1;
    tv=5;
    //模式
    Modes=0;

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
//板号配置
void Dialog::BoardInit(){
    SerialHandle->init();
}
//数据处理
void Dialog::getStr(QByteArray str){
    SerialHandle->receive(str);
}
//客户端检测
void Dialog::see(){
    if(!myTcp->getTcpClientFlag())
        myTcp->start();
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
        ui->lab_temp->setText(value);
        ui->v_temp->setValue(value.toFloat());
        temp_value=value.toFloat();
        //上传温度数据至本地数据库
        QSqlQuery q;
        q.exec("insert into date values('"+QTime::currentTime().toString("hh:mm")+"','温度','"+value+"')");
    }else if(type==HUM_SERVE){
        ui->lab_hum->setText(value);
        ui->v_hum->setValue(value.toFloat());
        hum_value=value.toFloat();
    }else if(type==ILL_SERVE){
        ui->lab_ill->setText(value);
        ui->v_ill->setValue(value.toFloat());
        ill_value=value.toFloat();
    }else if(type==AP_SERVE){
        ui->lab_air->setText(value);
        ui->v_air->setValue(value.toFloat());
        air_value=value.toFloat();
    }else if(type==CO2_SERVE){
        ui->lab_co2->setText(value);
        ui->v_co2->setValue(value.toInt());
        co2_value=value.toInt();
    }else if(type==GAS_SERVE){
        ui->lab_gas->setText(value);
        ui->v_gas->setValue(value.toInt());
        gas_value=value.toInt();
    }else if(type==PM25_SERVE){
        ui->lab_pm->setText(value);
        ui->v_pm->setValue(value.toInt());
        pm_value=value.toInt();
    }else if(type==SMK_SERVE){
        ui->lab_smoke->setText(value);
        ui->v_smoke->setValue(value.toInt());
        smoke_value=value.toInt();
        //上传烟雾数据至本地数据库
        QSqlQuery q;
        q.exec("insert into date values('"+QTime::currentTime().toString("hh:mm")+"','烟雾','"+value+"')");
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
        ui->chk_rfid->setChecked(0);
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
    Deceive_control(SerialHandle->sensorTypeToBoardIdMap[type],pCmd,9);
}
//命令转发
void Dialog::Deceive_control(unsigned int board_number, unsigned int *pCmd, unsigned int len){
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
    Deceive_control(SerialHandle->sensorTypeToBoardIdMap[FAN_SERVE],pCmd,9);
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
    Deceive_control(SerialHandle->sensorTypeToBoardIdMap[LAMP_SERVE],pCmd,9);
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
    Deceive_control(SerialHandle->sensorTypeToBoardIdMap[WL_SERVE],pCmd,9);
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
    Deceive_control(SerialHandle->sensorTypeToBoardIdMap[DC_SERVE],pCmd,9);
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
    Deceive_control(SerialHandle->sensorTypeToBoardIdMap[CT_SERVE],pCmd,9);
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
    Deceive_control(SerialHandle->sensorTypeToBoardIdMap[CT_SERVE],pCmd,9);
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
    Deceive_control(SerialHandle->sensorTypeToBoardIdMap[INFRARED_SERVE],pCmd,9);
}
//日志
void Dialog::writelog(QString action){
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
//单控
void Dialog::on_chk_warning_clicked(bool checked)
{
    Modes=0;
    if(checked){
        WarningCmd(SWITCH_ON);
        writelog("报警灯开");
    }else{
        WarningCmd(SWITCH_OFF);
        writelog("报警灯关");
    }
}

void Dialog::on_chk_fan_clicked(bool checked)
{
    Modes=0;
    if(checked){
        FanCmd(SWITCH_ON);
        writelog("排气扇开");
    }else{
        FanCmd(SWITCH_OFF);
        writelog("排气扇关");
    }
}

void Dialog::on_chk_rfid_clicked(bool checked)
{
    Modes=0;
    if(checked){
        RfidCmd(SWITCH_ON);
        writelog("门禁开");
    }else{
        RfidCmd(SWITCH_OFF);
        writelog("门禁关");
    }
}

void Dialog::on_btn_lamp1_clicked()
{
    Modes=0;
    if(lamp1_state!=SWITCH_ON){
        LampCmd(SWITCH_ON,CHANNEL_1);
        writelog("灯1开");
    }else{
        LampCmd(SWITCH_OFF,CHANNEL_1);
        writelog("灯1关");
    }
}

void Dialog::on_btn_lamp2_clicked()
{
    Modes=0;
    if(lamp2_state!=SWITCH_ON){
        LampCmd(SWITCH_ON,CHANNEL_2);
        writelog("灯2开");
    }else{
        LampCmd(SWITCH_OFF,CHANNEL_2);
        writelog("灯2关");
    }
}

void Dialog::on_btn_lamp_clicked()
{
    Modes=0;
    if(lamp1_state!=SWITCH_ON||lamp2_state!=SWITCH_ON){
        LampCmd(SWITCH_ON,CHANNEL_ALL);
        writelog("灯全开");
    }else{
        LampCmd(SWITCH_OFF,CHANNEL_ALL);
        writelog("灯全关");
    }
}

void Dialog::on_btn_curtain_on_clicked()
{
    Modes=0;
    if(curtain_state!=CHANNEL_1){
        CurtainCmd(CHANNEL_1);
        writelog("窗帘开");
    }
}

void Dialog::on_btn_curtain_stop_clicked()
{
    Modes=0;
    if(curtain_state!=CHANNEL_2){
        CurtainCmd(CHANNEL_2);
        writelog("窗帘停");
    }
}

void Dialog::on_btn_curtain_off_clicked()
{
    Modes=0;
    if(curtain_state!=CHANNEL_3){
        CurtainCmd(CHANNEL_3);
        writelog("窗帘关");
    }
}

void Dialog::on_radio_tv_clicked()
{
    Modes=0;
    if(tv_state!=SWITCH_ON){
        tv_state=SWITCH_ON;
        writelog("电视开");
    }else{
        tv_state=SWITCH_OFF;
        writelog("电视关");
    }
    InfraredEmit(tv);
}

void Dialog::on_radio_air_clicked()
{
    Modes=0;
    if(air_state!=SWITCH_ON){
        air_state=SWITCH_ON;
        writelog("空调开");
    }else{
        air_state=SWITCH_OFF;
        writelog("空调关");
    }
    InfraredEmit(air);
}

void Dialog::on_radio_dvd_clicked()
{
    Modes=0;
    if(dvd_state!=SWITCH_ON){
        dvd_state=SWITCH_ON;
        writelog("DVD开");
    }else{
        dvd_state=SWITCH_OFF;
        writelog("DVD关");
    }
    InfraredEmit(dvd);
}

void Dialog::on_cmb_infrared_currentIndexChanged(int index)
{
    Modes=0;
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
//打开日志界面
void Dialog::on_chk_log_clicked()
{
    Mylog a;
    a.exec();
    ui->chk_log->setChecked(0);
}
//模式判断
void Dialog::Mode(){
    ui->lab_time->setText(QTime::currentTime().toString("hh:mm"));
    switch(Modes){
    case 0://关闭模式
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
//饼图变更，文本改变
void Dialog::on_comboBox_currentIndexChanged(int index)
{
    if(index==1){
        drawFlag=1;
        ui->lab_text_draw->setText("温度数据一小时统计图");
        ui->lab_num1->setText("0-19");
        ui->lab_num2->setText("20-29");
        ui->lab_num3->setText("30-39");
        ui->lab_dw->setText("单位：℃");
        ui->lab_draw->show();
    }else if(index==2){
        drawFlag=2;
        ui->lab_text_draw->setText("光照数据一小时统计图");
        ui->lab_num1->setText("0-300");
        ui->lab_num2->setText("301-699");
        ui->lab_num3->setText("700-1500");
        ui->lab_dw->setText("单位：Lx");
        ui->lab_draw->show();
    }else{
        ui->lab_text_draw->setText("");
        ui->lab_num1->setText("");
        ui->lab_num2->setText("");
        ui->lab_num3->setText("");
        ui->lab_dw->setText("单位：");
        ui->lab_draw->hide();
    }
}
bool Dialog::eventFilter(QObject *a, QEvent *event){
    if(a==ui->lab_draw&&event->type()==QEvent::Paint)
        mydraw();
    return QWidget::eventFilter(a,event);
}

void Dialog::play(){
    //判断温度，符合条件则+1
    if(0<=temp_value&&temp_value<=19){
        num_temp[0]+=1;
    }else if(20<=temp_value&&temp_value<=29){
        num_temp[1]+=1;
    }else if(30<=temp_value&&temp_value<=39){
        num_temp[2]+=1;
    }
//判断光照，符合条件则+1
    if(0<=ill_value&&ill_value<=300){
        num_ill[0]+=1;
    }else if(301<=ill_value&&ill_value<=699){
        num_ill[1]+=1;
    }else if(700<=ill_value&&ill_value<=1500){
        num_ill[2]+=1;
    }
//温度，光照写入数组
    for(int i=0;i<3;i++){
        v_temp<<num_temp[i];
        v_ill<<num_ill[i];
    }
//颜色写入
    v_color<<QBrush(Qt::blue)<<QBrush(Qt::red)<<QBrush(Qt::green);

    update();

}
void Dialog::mydraw(){
    QPainter q(ui->lab_draw);
    //反走样
    q.setRenderHint(QPainter::Antialiasing, true);
    //半径
    int radius=130;
    //圆的矩形
    QRect rect(20,40,radius,radius);
    //总值
    float sum_temp=num_temp[0]+num_temp[1]+num_temp[2];
    float sum_ill=num_ill[0]+num_ill[1]+num_ill[2];
    //角度
    float angle;
    //温度
    if(drawFlag==1){
        //起始角度
        int pos=0;
        for(int i=0;i<v_temp.count();++i){
            //求角度，温度值【1】/温度总值
            angle=v_temp[i]/sum_temp*16*360;
            //设置画刷颜色
            q.setBrush(v_color[i]);
            //画扇型，参数1：矩形，参数2：起始角度，参数3：角度
            q.drawPie(rect,pos,angle);
            //起始角度+=角度
            pos+=angle;
        }
        //起始角度复原
        pos=0;
        for(int i=0;i<v_temp.count();++i){
            angle=v_temp[i]/sum_temp*16*360;
            //文本角度
            double labAngle=(pos+angle/2)/16;
            //文本点位置
            double tx=rect.width()/2*qCos(labAngle/360*2*3.14);
            double ty=-rect.width()/2*qSin(labAngle/360*2*3.14);
            //画文本
            q.drawText(QPoint(tx/2,ty/2)+rect.center(),QString::number((int)(v_temp[i]/sum_temp*100+0.5f))+"%");
            pos+=angle;
        }
    }
    if(drawFlag==2){
        int pos=0;
        for(int i=0;i<v_ill.count();++i){
            angle=v_ill[i]/sum_ill*16*360;
            q.setBrush(v_color[i]);
            q.drawPie(rect,pos,angle);
            pos+=angle;
        }
        pos=0;
        for(int i=0;i<v_ill.count();++i){
            angle=v_ill[i]/sum_ill*16*360;
            double labAngle=(pos+angle/2)/16;
            double tx=rect.width()/2*qCos(labAngle/360*2*3.14);
            double ty=-rect.width()/2*qSin(labAngle/360*2*3.14);
            q.drawText(QPoint(tx/2,ty/2)+rect.center(),QString::number((int)(v_ill[i]/sum_ill*100+0.5f))+"%");
            pos+=angle;
        }
    }
    //清除光照，温度，颜色
    v_temp.clear();
    v_ill.clear();
    v_color.clear();
}
