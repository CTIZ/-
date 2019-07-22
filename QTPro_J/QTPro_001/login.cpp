#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    //按钮设置是否启用
    QSqlQuery q;
    q.exec("select * from user where name='"+ui->led_name->text()+"'");
    if(q.next()){
        ui->pushButton->setEnabled(1);
    }else{
        ui->pushButton->setEnabled(0);
    }
}

login::~login()
{
    delete ui;
}
//登录
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
        QMessageBox::critical(this,"登录","密码错误","确定","取消");
    }
}
//name编辑完后执行
void login::on_led_name_editingFinished()
{
    QSqlQuery q;
    q.exec("select * from user where name='"+ui->led_name->text()+"'");
    if(q.next()){
        ui->pushButton->setEnabled(1);
    }else{
        ui->pushButton->setEnabled(0);
    }

}
//qx:判断界面
int qx;
//注册
void login::on_pushButton_2_clicked()
{
    qx=1;
    resgister a;
    a.setWindowFlags(Qt::FramelessWindowHint);
    a.exec();
}
//修改
void login::on_pushButton_3_clicked()
{
    qx=2;
    resgister a;
    a.setWindowFlags(Qt::FramelessWindowHint);
    a.exec();
}
//删除
void login::on_pushButton_4_clicked()
{
    qx=0;
    resgister a;
    a.setWindowFlags(Qt::FramelessWindowHint);
    a.exec();
}
