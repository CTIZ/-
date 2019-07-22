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
    for(int i=0;i<4;i++)
        num[i]=rand()%9;
    if(num[0]>5&&num[0]<9)
        ui->lab_num1->setStyleSheet("background-image: url(:/"+QString::number(num[0])+".png);");
    else
        ui->lab_num1->setStyleSheet("background-image: url(:/"+QString::number(num[0])+".jpg);");
    if(num[1]>5&&num[1]<9)
        ui->lab_num2->setStyleSheet("background-image: url(:/"+QString::number(num[1])+".png);");
    else
        ui->lab_num2->setStyleSheet("background-image: url(:/"+QString::number(num[1])+".jpg);");
    if(num[2]>5&&num[2]<9)
        ui->lab_num3->setStyleSheet("background-image: url(:/"+QString::number(num[2])+".png);");
    else
        ui->lab_num3->setStyleSheet("background-image: url(:/"+QString::number(num[2])+".jpg);");
    if(num[3]>5&&num[3]<9)
        ui->lab_num4->setStyleSheet("background-image: url(:/"+QString::number(num[3])+".png);");
    else
        ui->lab_num4->setStyleSheet("background-image: url(:/"+QString::number(num[3])+".jpg);");
}

login::~login()
{
    delete ui;
}
//注册
void login::on_pushButton_clicked()
{
    resgister a;
    a.exec();
}
//管理
void login::on_pushButton_2_clicked()
{
    guanli a;
    a.exec();
}
//触摸事件
void login::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        px=cursor().pos().x();
        py=cursor().pos().y();
    }
}

QString ip;
//结束触摸事件
void login::mouseReleaseEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        int rpx=cursor().pos().x();
        int rpy=cursor().pos().y();
        if(!(rpx>260&&rpx<440)){
            if(rpx>px-30&&rpx<px+30){
                if(rpy<py-30){
                    QSqlQuery q;
                    q.exec("select * from user where name='"+ui->led_name->text()+"' and pwd='"+ui->led_pwd->text()+"'");
                    if(q.next()){
                        if(ui->led_yzm->text()==QString::number(num[0])+QString::number(num[1])+QString::number(num[2])+QString::number(num[3])){
                            ip=ui->led_ip->text();
                            Dialog a;
                            a.setWindowFlags(Qt::FramelessWindowHint);
                            a.exec();
                        }else{
                            QMessageBox::critical(this,"登录失败","验证码错误","确定","取消");
                        }
                    }else{
                        QMessageBox::critical(this,"登录失败","用户名或密码错误","确定","取消");
                    }
                }
            }
        }
    }
}

void login::on_pushButton_3_clicked()
{
    QSqlQuery q;
    q.exec("select * from user where name='"+ui->led_name->text()+"' and pwd='"+ui->led_pwd->text()+"'");
    if(q.next()){
        if(ui->led_yzm->text()==QString::number(num[0])+QString::number(num[1])+QString::number(num[2])+QString::number(num[3])){
            ip=ui->led_ip->text();
            Dialog a;
            a.setWindowFlags(Qt::FramelessWindowHint);
            a.exec();
        }else{
            QMessageBox::critical(this,"登录失败","验证码错误","确定","取消");
        }
    }else{
        QMessageBox::critical(this,"登录失败","用户名或密码错误","确定","取消");
    }
}
