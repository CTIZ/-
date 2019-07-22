#include "resgister.h"
#include "ui_resgister.h"

resgister::resgister(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::resgister)
{
    ui->setupUi(this);
}

resgister::~resgister()
{
    delete ui;
}

void resgister::on_pushButton_clicked()
{
    if(ui->led_name->text()==""){
        QMessageBox::critical(this,"注册","用户名不能为空");
    }else if(QRegExp("^(?=.*[a-z].*)(?=.*[0-9].*).*$").indexIn(ui->led_pwd->text())==-1){
        QMessageBox::critical(this,"注册","密码格式不正确");
    }else if(ui->led_pwd->text()!=ui->led_repwd->text()){
        QMessageBox::critical(this,"注册","两次密码不一致");
    }else{
        QSqlQuery q;
        q.exec("insert into tb_userInfo values('"+ui->led_name->text()+"','"+ui->led_pwd->text()+"')");
        QMessageBox::information(this,"注册成功","欢迎使用","确定","取消");
    }
}

void resgister::on_pushButton_2_clicked()
{
    this->close();
}
