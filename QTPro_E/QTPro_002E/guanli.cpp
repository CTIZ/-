#include "guanli.h"
#include "ui_guanli.h"

guanli::guanli(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::guanli)
{
    ui->setupUi(this);
    if(state==1){
        ui->update->hide();
        ui->resgister->show();
    }else if(state==0){
        ui->update->hide();
        ui->resgister->hide();
    }
    Model();
}

guanli::~guanli()
{
    delete ui;
}
void guanli::Model(){
    model=new QSqlTableModel();
    model->setTable("user");;
    model->select();
    model->setHeaderData(0,Qt::Horizontal,"用户名");
    model->setHeaderData(1,Qt::Horizontal,"密码");
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setModel(model);
}

void guanli::on_pushButton_4_clicked()
{
    this->close();
}
void guanli::on_pushButton_clicked()
{
    if(state==2){
        if(ui->led_update_Npwd->text()!=ui->led_update_repwd->text()){
            QMessageBox::critical(this,"修改失败","两次密码不同");
        }else{
            QSqlQuery q;
            q.exec("update user set pwd='"+ui->led_update_Npwd->text()+"' where name='"+ui->led_update_name->text()+"' and pwd='"+ui->led_update_pwd->text()+"'");
            Model();
        }
    }else{
        state==2;
        ui->update->show();
        ui->resgister->hide();
    }
}

void guanli::on_pushButton_2_clicked()
{
    if(state==1){
            if(ui->led_resgister_pwd->text()!=ui->led_resgister_repwd->text()){
                QMessageBox::critical(this,"注册失败","两次密码不同");
            }else{
                QSqlQuery q;
                q.exec("select * from user where name='"+ui->led_resgister_name->text()+"'");
                if(q.next()){

                }else{
                    q.prepare("insert into user values(:name,:pwd)");
                    q.bindValue(":name",ui->led_resgister_name->text());
                    q.bindValue(":pwd",ui->led_resgister_pwd->text());
                    q.exec();
                    QMessageBox::information(this,"注册成功","欢迎使用");
                    Model();
                }
            }
        }else{
            state==1;
            ui->update->hide();
            ui->resgister->show();
        }
}

void guanli::on_pushButton_3_clicked()
{
    model=dynamic_cast<QSqlTableModel *>(ui->tableView->model());
    model->removeRow(ui->tableView->currentIndex().row());
    model->submitAll();
}
