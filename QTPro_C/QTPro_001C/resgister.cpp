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

void resgister::on_pushButton_2_clicked()
{
    this->close();
}

void resgister::on_pushButton_clicked()
{
    if(ui->led_name->text()==""){
        QMessageBox::critical(this,"注册失败","用户名不能为空");
    }else if(ui->led_pwd->text()==""){
        QMessageBox::critical(this,"注册失败","密码不能为空");
    }else if(ui->led_pwd->text()!=ui->led_repwd->text()){
        QMessageBox::critical(this,"注册失败","两次密码不一致");
    }else if(QRegExp("^(?=.*[0-9].*)(?=.*[a-z].*)(?=.*[A-Z].*).*$").indexIn(ui->led_pwd->text())==-1){
        QMessageBox::critical(this,"注册失败","密码必须是数字和字母组合的格式");
    }else{
        QSqlQuery q;
        q.exec("select * from user where name='"+ui->led_name->text()+"'");
        if(q.next()){

        }else{
            q.prepare("insert into user values(:name,:pwd)");
            q.bindValue(":name",ui->led_name->text());
            q.bindValue(":pwd",ui->led_pwd->text());
            q.exec();
            QMessageBox::information(this,"注册成功","欢迎使用");
        }
    }
}
