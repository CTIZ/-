#include "draw.h"
#include "ui_draw.h"

Draw::Draw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Draw)
{
    ui->setupUi(this);
    ui->label->installEventFilter(this);
    QTimer *time=new QTimer();
    connect(time,SIGNAL(timeout()),this,SLOT(play()));
    time->start(1000);
}
bool Draw::eventFilter(QObject *a, QEvent *event){
    if(a==ui->label&&event->type()==QEvent::Paint)
        mydraw();
    return QWidget::eventFilter(a,event);
}

void Draw::play(){
    v<<(float)temp_value;
    if(v.count()>8)
        v.remove(0);
    update();
}
void Draw::mydraw(){
    QPainter q(ui->label);
    float px=30;float py=400;
    float K=40/py;

    for(int i=2;i<=v.count()+1;i++){
        q.drawText(px+(i-1)*70,py-v[i-2]/K-10,QString::number(v[i-2])+"℃");
    }

    QPen p1;
    p1.setColor(QColor(255,170,0));
    q.setPen(p1);
    q.setBrush(QBrush(QColor(255,170,0)));
    q.drawEllipse(px+70,py-v[0]/K-5,10,10);
    for(int i=2;i<=v.count();i++){
        q.drawLine(px+(i-1)*70,py-v[i-2]/K,px+i*70,py-v[i-1]/K);
        q.drawEllipse(px+i*70,py-v[i-1]/K-5,10,10);
    }

}

Draw::~Draw()
{
    delete ui;
}
