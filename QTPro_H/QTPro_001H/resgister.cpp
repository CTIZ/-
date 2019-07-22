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
    //检测
    if(ui->led_name->text()!=""&&ui->led_pwd->text()!=""){
        if(ui->icon_name->styleSheet()=="border-image: url(:/8214.png);"&&ui->icon_pwd->styleSheet()=="border-image: url(:/8214.png);"&&ui->icon_repwd->styleSheet()=="border-image: url(:/8214.png);"){
            QSqlQuery q;
            q.exec("select * from user where name='"+ui->led_name->text()+"'");
            if(q.next()){

            }else{
                //注册
                q.prepare("insert into user values(:name,:pwd)");
                q.bindValue(":name",ui->led_name->text());
                q.bindValue(":pwd",ui->led_pwd->text());
                q.exec();
                //对话框
                QMessageBox ms(QMessageBox::Information,"注册成功","欢迎使用",QMessageBox::Yes|QMessageBox::No);
                //设置对话框文本
                ms.setButtonText(QMessageBox::Yes,"程序界面");
                ms.setButtonText(QMessageBox::No,"登录界面");
                //对话框按钮点击判断
                if(ms.exec()==QMessageBox::Yes){
                    Dialog a;
                    a.setWindowFlags(Qt::FramelessWindowHint);
                    this->close();
                    a.exec();
                }else{
                    this->close();
                }
            }
        }
    }else{
        QMessageBox::critical(this,"注册错误","用户名密码不能为空");
    }
}
//name编辑完后
void resgister::on_led_name_editingFinished()
{
    if(ui->led_name->text().length()>6){
        //正则表达式
        if(QRegExp("^(?=.*[0-9].*)(?=.*[a-z].*).*$").indexIn(ui->led_name->text())==-1){
            ui->icon_name->setStyleSheet("border-image: url(:/8213.png);");
        }else{
            ui->icon_name->setStyleSheet("border-image: url(:/8214.png);");
        }
    }else{
        ui->icon_name->setStyleSheet("border-image: url(:/8213.png);");
    }
}

void resgister::on_led_pwd_editingFinished()
{
    if(ui->led_pwd->text().length()>6){
        if(QRegExp("^(?=.*[0-9].*)(?=.*[a-z].*).*$").indexIn(ui->led_pwd->text())==-1){
            ui->icon_pwd->setStyleSheet("border-image: url(:/8213.png);");
        }else{
            ui->icon_pwd->setStyleSheet("border-image: url(:/8214.png);");
        }
    }else{
        ui->icon_pwd->setStyleSheet("border-image: url(:/8213.png);");
    }
}

void resgister::on_led_repwd_editingFinished()
{
    if(ui->led_pwd->text()!=ui->led_repwd->text()){
        ui->icon_repwd->setStyleSheet("border-image: url(:/8213.png);");
    }else{
        ui->icon_repwd->setStyleSheet("border-image: url(:/8214.png);");
    }
}
