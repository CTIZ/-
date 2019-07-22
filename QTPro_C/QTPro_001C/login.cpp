#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    QSqlQuery q;
    q.exec("create table user(name varchar(40),pwd varchar(40))");
    q.exec("select * from user where name='bizideal' and pwd='123456'");
    if(q.next()){

    }else{
        q.exec("insert into user values('bizideal','123456')");
    }
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_5_clicked()
{
    this->close();
}

QString ip="";
QString port="";

void login::on_pushButton_clicked()
{
    QSqlQuery q;
    q.exec("select * from user where name='"+ui->led_name->text()+"' and pwd='"+ui->led_pwd->text()+"'");
    if(q.next()){
        ip=ui->led_ip->text();
        port=ui->led_port->text();
        Dialog a;
        a.setWindowFlags(Qt::FramelessWindowHint);
        this->close();
        a.exec();
    }else{
        QMessageBox::critical(this,"登录失败","密码输入错误");
    }
}

void login::on_pushButton_2_clicked()
{
    resgister a;
    a.setWindowFlags(Qt::FramelessWindowHint);
    a.exec();
}

int qx=0;

void login::on_pushButton_3_clicked()
{
    qx=1;
    guanli a;
    a.setWindowFlags(Qt::FramelessWindowHint);
    a.exec();
}

void login::on_pushButton_4_clicked()
{
    qx=2;
    guanli a;
    a.setWindowFlags(Qt::FramelessWindowHint);
    a.exec();
}
