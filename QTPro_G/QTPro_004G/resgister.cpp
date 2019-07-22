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
//返回
void resgister::on_pushButton_2_clicked()
{
    this->close();
}
//确定
void resgister::on_pushButton_clicked()
{
    if(ui->led_name->text()==""||ui->led_pwd->text()==""){
        QMessageBox::critical(this,"注册错误","用户名密码不能为空","确定","取消");
    }else{
        if(ui->icon_name->styleSheet()=="background-image: url(:/8214.png);"&&ui->icon_pwd->styleSheet()=="background-image: url(:/8214.png);"&&ui->icon_repwd->styleSheet()=="background-image: url(:/8214.png);"){
            QSqlQuery q;
            q.exec("insert into user values('"+ui->led_name->text()+"','"+ui->led_pwd->text()+"')");
            QMessageBox ms(QMessageBox::Information,"注册成功","欢迎使用",QMessageBox::Yes|QMessageBox::No);
            ms.setButtonText(QMessageBox::No,"程序界面");
            ms.setButtonText(QMessageBox::Yes,"登录界面");
            if(ms.exec()==QMessageBox::No){
                Dialog a;
                a.setWindowFlags(Qt::FramelessWindowHint);
                this->close();
                a.exec();
            }else{
                this->close();
            }
        }
    }
}
//用户名编辑完成
void resgister::on_led_name_editingFinished()
{
    if(ui->led_name->text().length()>=6){
        if(QRegExp("^(?=.*[a-z].*)(?=.*[A-Z].*)(?=.*[0-9].*).*$").indexIn(ui->led_name->text())==-1){
            ui->icon_name->setStyleSheet("background-image: url(:/8213.png);");
        }else{
            ui->icon_name->setStyleSheet("background-image: url(:/8214.png);");
        }
    }else{
        ui->icon_name->setStyleSheet("background-image: url(:/8213.png);");
    }
}
//密码编辑完成
void resgister::on_led_pwd_editingFinished()
{
    if(ui->led_pwd->text().length()>=6){
        if(QRegExp("^(?=.*[a-z].*)(?=.*[A-Z].*)(?=.*[0-9].*).*$").indexIn(ui->led_pwd->text())==-1){
            ui->icon_pwd->setStyleSheet("background-image: url(:/8213.png);");
        }else{
            ui->icon_pwd->setStyleSheet("background-image: url(:/8214.png);");
        }
    }else{
        ui->icon_pwd->setStyleSheet("background-image: url(:/8213.png);");
    }
}
//确认密码编辑完成
void resgister::on_led_repwd_editingFinished()
{
    if(ui->led_pwd->text()==ui->led_repwd->text()){
        ui->icon_repwd->setStyleSheet("background-image: url(:/8214.png);");
    }else{
        ui->icon_repwd->setStyleSheet("background-image: url(:/8214.png);");
    }
}
