#include "draw.h"
#include "ui_draw.h"

Draw::Draw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Draw)
{
    ui->setupUi(this);
    ui->lab_draw->installEventFilter(this);

    time=new QTimer(this);
    connect(time,SIGNAL(timeout()),this,SLOT(play()));
}

Draw::~Draw()
{
    delete ui;
}

void Draw::on_pushButton_clicked()
{
    this->close();
}
//chk选中打开定时器
void Draw::on_checkBox_clicked(bool checked)
{
    if(checked){
        time->start(1000);
    }else{
        time->stop();
    }
}
//数据写入
void Draw::play(){
    v<<(float)temp_value;
    if(v.count()>7)
        v.remove(0);
    update();
}

void Draw::mydraw(){
    QPainter q(ui->lab_draw);
    QPen p1,p2;
    p1.setWidth(1);
    p2.setWidth(3);
    float px=30;float py=400;
    float K=60.0/300.0;
    q.drawLine(0,py,500,py);
    q.drawLine(px,0,px,400);
    for(int i=0;i<=3;i++){
        q.drawText(0,py-i*100,QString::number(i*20));
    }
    for(int i=1;i<=7;i++){
        q.drawText(px+(i-1)*50,py+20,QString::number(i));
    }
    q.setPen(p2);
    q.drawPoint(px,py-v[0]/K);
    for(int i=2;i<=v.count();i++){
        if(v[i-1]>15){
            p1.setColor(QColor(Qt::red));
            q.setBrush(QBrush(Qt::red));
        }
        else{
            p1.setColor(QColor(Qt::black));
            q.setBrush(QBrush(Qt::black));
        }
        q.setPen(p1);
        q.drawLine(px+(i-2)*50,py-v[i-2]/K,px+(i-1)*50,py-v[i-1]/K);
        q.drawEllipse(px+(i-1)*50,py-v[i-1]/K-3,6,6);
    }
}
bool Draw::eventFilter(QObject *a, QEvent *event){
    if(a==ui->lab_draw&&event->type()==QEvent::Paint)
        mydraw();
    return QWidget::eventFilter(a,event);
}
