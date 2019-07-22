#include "draw.h"
#include "ui_draw.h"

Draw::Draw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Draw)
{
    ui->setupUi(this);
    //比例参数
    N=1200;
    //过滤
    ui->lab_draw->installEventFilter(this);
    //定时画
    time=new QTimer(this);
    connect(time,SIGNAL(timeout()),this,SLOT(play()));
    time->start(1000);
}
void Draw::play(){
    //比例为光照+100；
    N=ill_value+100;
    //写入数据
    v<<(float)ill_value;
    //数据>20删除
    if(v.count()>20)
        v.remove(0);
    //更新
    update();
}
void Draw::mydraw(){
    QPainter q(ui->lab_draw);
    //设置画笔粗细和颜色
    QPen p1,p2;
    //p1:线画笔
    p1.setWidth(3);
    p1.setColor(QColor(0,255,255));
    //p2:多边形画笔
    p2.setWidth(0);
    p2.setColor(QColor(0,0,0,0));

    q.setPen(p1);

    //绘图区域
    float px=50;float py=420;
    //比例K=图数据最大值N/绘画区域y值py
    float K=N/400;
    //画数据
    for(int i=0;i<=4;i++){
        q.drawText(10,py-i*100,QString::number((int)(i*100*K)));
    }
    //渐变
    QLinearGradient linear(QPoint(width()/2,0),QPoint(width()/2,py));
    linear.setColorAt(0, QColor(0,255,255));
    linear.setColorAt(1, Qt::black);
    // 设置显示模式,线性
    linear.setSpread(QGradient::PadSpread);
    //设置画刷
    q.setBrush(linear);
    for(int i=2;i<=v.count();i++){
        //画多边形
        //多边形4点
        QPoint pnts[4]={
            QPoint(px+(i-1)*30,py-v[i-2]/K),
            QPoint(px+(i-1)*30,py),
            QPoint(px+i*30,py),
            QPoint(px+i*30,py-v[i-1]/K)
        };
        q.setPen(p2);
        q.drawPolygon(pnts,4);
        //画线
        q.setPen(p1);
        q.drawLine(px+(i-1)*30,py-v[i-2]/K,px+i*30,py-v[i-1]/K);
    }
    //画圆圈
    q.setBrush(QBrush(Qt::black));
    q.drawEllipse(px+30,py-v[0]/K-5,10,10);
    for(int i=2;i<=v.count();i++){
        q.drawEllipse(px+i*30,py-v[i-1]/K-5,10,10);
    }
}
bool Draw::eventFilter(QObject *a, QEvent *event){
    if(a==ui->lab_draw&&event->type()==QEvent::Paint)
        mydraw();
    return QWidget::eventFilter(a,event);
}

Draw::~Draw()
{
    delete ui;
}
