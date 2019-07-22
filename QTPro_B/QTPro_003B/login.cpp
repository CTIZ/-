#include "login.h"
#include "ui_login.h"
#include "QDebug"
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    QSqlQuery q;
    q.exec("create table user(name varchar(40),pwd varchar(40))");
    q.exec("select * from user where name='admin'");
    if(q.next()){

    }else{
        q.exec("insert into user values('admin','Aa1111')");
    }
}

login::~login()
{
    delete ui;
}

QString ip;
QString port;

void login::on_pushButton_clicked()
{
    QSqlQuery q;
    q.exec("select * from user where name='"+ui->led_name->text()+"' and pwd='"+ui->led_pwd->text()+"'");
    if(q.next()){
        ip=ui->led_ip->text();
        port=ui->led_port->text();
        welcome a;
        a.setWindowFlags(Qt::FramelessWindowHint);
        this->close();
        a.exec();
    }else{
        QMessageBox::critical(this,"登录错误","用户名或密码错误","确认","取消");
    }
}
void login::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        px=cursor().pos().x();
        py=cursor().pos().y();
    }
}
void login::mouseReleaseEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        int rpx=cursor().pos().x();
        int rpy=cursor().pos().y();
        if(!(280<rpx&&rpx<510)){
            if(px-30<rpx&&rpx<px+30){
                if(py-30>rpy){
                    QSqlQuery q;
                    q.exec("select * from user where name='"+ui->led_name->text()+"' and pwd='"+ui->led_pwd->text()+"'");
                    if(q.next()){
                        ip=ui->led_ip->text();
                        port=ui->led_port->text();
                        welcome a;
                        a.setWindowFlags(Qt::FramelessWindowHint);
                        this->close();
                        a.exec();
                    }else{
                        QMessageBox::critical(this,"登录错误","用户名或密码错误","确认","取消");
                    }
                }
            }
        }
    }
}

void login::on_pushButton_2_clicked()
{
    updatepwd a;
    a.setWindowFlags(Qt::FramelessWindowHint);
    a.exec();
}
