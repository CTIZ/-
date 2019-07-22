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

void login::on_pushButton_clicked()
{
    QSqlQuery q;
    q.exec("select * from user where name='"+ui->led_name->text()+"'");
    if(q.next()){
        q.exec("select * from user where name='"+ui->led_name->text()+"' and pwd='"+ui->led_pwd->text()+"'");
        if(q.next()){
            Dialog a;
            a.setWindowFlags(Qt::FramelessWindowHint);
            a.exec();
        }else{

            QMessageBox::critical(this,"登录失败","密码错误");
        }
    }else{
        QMessageBox::critical(this,"登录失败","用户名错误");
    }
}

int state;

void login::on_pushButton_2_clicked()
{
    state=1;
    guanli a;
    a.setWindowFlags(Qt::FramelessWindowHint);
    a.exec();
}

void login::on_pushButton_3_clicked()
{
    state=0;
    guanli a;
    a.setWindowFlags(Qt::FramelessWindowHint);
    a.exec();
}
