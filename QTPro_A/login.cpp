#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    QSqlQuery q;
    q.exec("create table user(name varchar(40),pwd varchar(40))");
    q.exec("select * from user where name='bizideal'");
    if(q.next()){

    }else{
        q.exec("insert into user values('bizideal','123456')");
    }
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_2_clicked()
{
    this->close();
}

void login::on_pushButton_clicked()
{
    QSqlQuery q;
    q.exec("select * from user where name='"+ui->led_name->text()+"' and pwd='"+ui->led_pwd->text()+"'");
    if(q.next()){
        Dialog a;
        a.setWindowFlags(Qt::FramelessWindowHint);
        this->close();
        a.exec();
    }else{
        QMessageBox::critical(this,"登录错误","用户名或密码错误","确定","取消");
    }
}

void login::on_pushButton_3_clicked()
{
    resgister a;
    a.setWindowFlags(Qt::FramelessWindowHint);
    a.exec();
}
