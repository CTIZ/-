#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}
//登录
void login::on_pushButton_clicked()
{
    QSqlQuery q;
    q.exec("select * from user where name='"+ui->led_name->text()+"'");
    if(q.next()){
        q.exec("select * from user where name='"+ui->led_name->text()+"' and pwd='"+ui->led_pwd->text()+"'");
        if(q.next()){
            Dialog a;
            a.setWindowFlags(Qt::FramelessWindowHint);
            this->close();
            a.exec();
        }else{
            QMessageBox::critical(this,"登录","密码错误","确定","取消");
        }
    }else{
        QMessageBox::critical(this,"登录","用户名错误","确定","取消");
    }
}
// 管理
void login::on_pushButton_2_clicked()
{
    guanli a;
    a.setWindowFlags(Qt::FramelessWindowHint);
    a.exec();
}
