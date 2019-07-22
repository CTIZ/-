#include "updatepwd.h"
#include "ui_updatepwd.h"

updatepwd::updatepwd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updatepwd)
{
    ui->setupUi(this);
}

updatepwd::~updatepwd()
{
    delete ui;
}

void updatepwd::on_pushButton_2_clicked()
{
    this->close();
}

void updatepwd::on_pushButton_clicked()
{
    if(ui->led_pwd->text()!=""){
        QSqlQuery q;
        q.exec("select * from user where name='admin' and pwd='"+ui->led_pwd->text()+"'");
        if(q.next()){
            if(ui->led_Npwd->text()!=""){
                if(QRegExp("^(?=.*[0-9].*)(?=.*[a-z].*)(?=.*[A-Z].*).*$").indexIn(ui->led_Npwd->text())!=-1){
                    if(ui->led_Npwd->text()!=ui->led_pwd->text()){
                        if(ui->led_Npwd->text().length()>=6){
                            if(ui->led_repwd->text()!=""){
                                if(ui->led_Npwd->text()==ui->led_repwd->text()){
                                    q.exec("update user set pwd='"+ui->led_Npwd->text()+"' where name='admin' and pwd='"+ui->led_pwd->text()+"'");
                                    QMessageBox::critical(this,"注册成功","欢迎使用","确认","取消");
                                    this->close();
                                }else{
                                    QMessageBox::critical(this,"注册错误","两次密码不同","确认","取消");
                                }
                            }else{
                                QMessageBox::critical(this,"注册错误","确认密码不能为空","确认","取消");
                            }
                        }else{
                            QMessageBox::critical(this,"注册错误","现密码不能少于6位","确认","取消");
                        }
                    }else{
                        QMessageBox::critical(this,"注册错误","密码已存在","确认","取消");
                    }
                }else{
                    QMessageBox::critical(this,"注册错误","密码须有数字和大小写字母组成","确认","取消");
                }
            }else{
                QMessageBox::critical(this,"注册错误","请输入现密码","确认","取消");
            }
        }else{
            QMessageBox::critical(this,"注册错误","原密码错误","确认","取消");
        }
    }else{
        QMessageBox::critical(this,"注册错误","原密码不能为空","确认","取消");
    }
}
