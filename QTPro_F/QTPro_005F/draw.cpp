#include "draw.h"
#include "ui_draw.h"

Draw::Draw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Draw)
{
    ui->setupUi(this);
    ui->lab_draw->installEventFilter(this);
    N=1200;
    time=new QTimer(this);
    connect(time,SIGNAL(timeout()),this,SLOT(play()));
    time->start(1000);
}
bool Draw::eventFilter(QObject *a, QEvent *event){
    if(a==ui->lab_draw&&event->type()==QEvent::Paint)
        mydraw();
    return QWidget::eventFilter(a,event);
}
void Draw::play(){
    if(this->windowTitle()=="光照度"){
        v<<(float)ill_value;
        N=1200;
    }else if(this->windowTitle()=="温度"){
        v<<(float)temp_value;
        N=60;
    }
    if(v.count()>13)
        v.remove(0);
    update();
}
void Draw::mydraw(){
    QPainter q(ui->lab_draw);
    float px=50;float py=440;
    float K=N/420;
    float j=15;
    float width=25;

    q.setBrush(QBrush(Qt::blue));
    q.drawLine(px,0,px,py);
    for(int i=0;i<=6;i++){
        q.drawText(5,py-i*70,QString::number((int)(i*70*K)));
        q.drawLine(px,py-i*70,750,py-i*70);
    }
    for(int i=1;i<=v.count();i++){
        q.drawRect(px+i*j+(i-1)*width+(i-1)*j,py,width,-v[i-1]/K);
        q.drawText(px+i*j+(i-1)*width+(i-1)*j+12,py-v[i-1]/K-20,QString::number(v[i-1]));
    }
}

Draw::~Draw()
{
    delete ui;
}
