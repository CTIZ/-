#include "draw.h"
#include "ui_draw.h"

Draw::Draw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Draw)
{
    ui->setupUi(this);
    N=240;
    ui->lab_draw->installEventFilter(this);
    QTimer *time=new QTimer(this);
    connect(time,SIGNAL(timeout()),this,SLOT(play()));
    time->start(1000);
}
bool Draw::eventFilter(QObject *a, QEvent *event){
    if(a==ui->lab_draw&&event->type()==QEvent::Paint)
        mydraw();
    return QWidget::eventFilter(a,event);
}

void Draw::play(){
    if(this->windowTitle()=="温度"){
        N=240;
        v<<(float)temp_value;
    }else if(this->windowTitle()=="湿度"){
        N=240;
        v<<(float)hum_value;
    }else if(this->windowTitle()=="光照"){
        N=1200;
        v<<(float)ill_value;
    }else if(this->windowTitle()=="烟雾"){
        N=720;
        v<<(float)smoke_value;
    }else if(this->windowTitle()=="气压"){
        N=1680;
        v<<(float)air_value;
    }else if(this->windowTitle()=="PM2.5"){
        N=60;
        v<<(float)pm_value;
    }else if(this->windowTitle()=="Co2"){
        N=720;
        v<<(float)co2_value;
    }else if(this->windowTitle()=="燃气"){
        N=720;
        v<<(float)gas_value;
    }
    if(v.count()>6)
        v.remove(0);
    update();
}
void Draw::mydraw(){
    QPainter q(ui->lab_draw);
    QPen p1,p2;
    p1.setWidth(1);
    p2.setWidth(3);
    float px=30;float py=240;
    float K=N/py;
    q.drawLine(0,py,300,py);
    q.drawLine(px,0,px,300);
    for(int i=0;i<12;i++){
        q.drawText(0,py-i*20,QString::number((int)(i*20*K)));
    }
    for(int i=1;i<=6;i++){
        q.drawText(px+i*40,py+20,QString::number(i));
    }
    q.setPen(p2);
    q.drawPoint(px+40,py-v[0]/K);
    for(int i=2;i<=v.count();i++){
        q.setPen(p1);
        q.drawLine(px+(i-1)*40,py-v[i-2]/K,px+i*40,py-v[i-1]/K);
        q.setPen(p2);
        q.drawPoint(px+i*40,py-v[i-1]/K);
    }
}

Draw::~Draw()
{
    delete ui;
}
