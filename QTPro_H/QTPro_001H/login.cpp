#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    yzm();
    QTimer *time=new QTimer(this);
    connect(time,SIGNAL(timeout()),this,SLOT(yzm()));
    time->start(30000);
}
//验证码
void login::yzm(){
    //4个随机数
    for(int i=0;i<4;i++){
        num[i]=rand()%9;
    }
    //设置图片
    if(num[0]>5&&num[0]<9){
        ui->icon1->setStyleSheet("border-image: url(:/"+QString::number(num[0])+".png);");
    }else{
        ui->icon1->setStyleSheet("border-image: url(:/"+QString::number(num[0])+".jpg);");
    }
    if(num[1]>5&&num[1]<9){
        ui->icon2->setStyleSheet("border-image: url(:/"+QString::number(num[1])+".png);");
    }else{
        ui->icon2->setStyleSheet("border-image: url(:/"+QString::number(num[1])+".jpg);");
    }
    if(num[2]>5&&num[2]<9){
        ui->icon3->setStyleSheet("border-image: url(:/"+QString::number(num[2])+".png);");
    }else{
        ui->icon3->setStyleSheet("border-image: url(:/"+QString::number(num[2])+".jpg);");
    }
    if(num[3]>5&&num[3]<9){
        ui->icon4->setStyleSheet("border-image: url(:/"+QString::number(num[3])+".png);");
    }else{
        ui->icon4->setStyleSheet("border-image: url(:/"+QString::number(num[3])+".jpg);");
    }
}

login::~login()
{
    delete ui;
}
//管理
void login::on_pushButton_2_clicked()
{
    guanli a;
    a.exec();
}
//注册
void login::on_pushButton_clicked()
{
    resgister a;
    a.exec();
}

//鼠标单击事件
void login::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){//左键
        //获取鼠标x，y坐标
        px=cursor().pos().x();
        py=cursor().pos().y();
    }
}
//鼠标释放事件
void login::mouseReleaseEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){//左键
        //获取鼠标x，y坐标
        int rpx=cursor().pos().x();
        int rpy=cursor().pos().y();
        //鼠标位置符合时
        if(!(280<rpx&&rpx<510)){
            //x轴偏差
            if(px-30<rpx&&rpx<px+30){
                //y轴移动距离
                if(py-30>rpy){
                    QSqlQuery q;
                    q.exec("select * from user where name='"+ui->led_name->text()+"' and pwd='"+ui->led_pwd->text()+"'");
                    if(q.next()){
                        if(ui->led_yzm->text()==QString::number(num[0])+QString::number(num[1])+QString::number(num[2])+QString::number(num[3])){
                            Dialog a;
                            a.setWindowFlags(Qt::FramelessWindowHint);
                            this->close();
                            a.exec();
                        }else{
                            QMessageBox::critical(this,"登录失败","验证码错误");
                        }
                    }else{
                        QMessageBox::critical(this,"登录失败","用户名密码错误");
                    }
                }
            }
        }
    }
}
