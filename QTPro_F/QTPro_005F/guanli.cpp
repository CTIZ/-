#include "guanli.h"
#include "ui_guanli.h"

guanli::guanli(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::guanli)
{
    ui->setupUi(this);
    Model();
    ui->w_resgister->hide();
    ui->w_update->hide();
    qx=0;
}

guanli::~guanli()
{
    delete ui;
}
//数据表模型
void guanli::Model(){
    model=new QSqlTableModel();
    model->setTable("user");
    model->select();
    model->setHeaderData(0,Qt::Horizontal,"用户名");
    model->setHeaderData(1,Qt::Horizontal,"密码");
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setModel(model);
}
//注册
void guanli::on_pushButton_clicked()
{
    if(qx==1){
        if(ui->led_resgister_pwd->text()!=ui->led_resgister_repwd->text()){
            QMessageBox::critical(this,"注册","两次密码不一致","确定","取消");
        }else{
            QSqlQuery q;
            q.exec("insert into user values('"+ui->led_resgister_name->text()+"','"+ui->led_resgister_pwd->text()+"')");
            Model();
        }
    }else{
        qx=1;
        ui->w_resgister->show();
        ui->w_update->hide();
    }
}
//更改
void guanli::on_pushButton_2_clicked()
{
    if(qx==2){
        QSqlQuery q;
        q.exec("select * from user where name='"+ui->led_update_name->text()+"'");
        if(q.next()){
            q.exec("select * from user where name='"+ui->led_update_name->text()+"' and pwd='"+ui->led_update_pwd->text()+"'");
            if(q.next()){
                if(ui->led_update_Npwd->text()!=ui->led_update_repwd->text()){
                    QMessageBox::critical(this,"更改","新密码和确认密码不一致","确定","取消");
                }else{
                    q.exec("update user set pwd='"+ui->led_update_Npwd->text()+"' and name='"+ui->led_update_name->text()+"' and pwd='"+ui->led_update_pwd->text()+"'");
                    Model();
                }
            }else{
                QMessageBox::critical(this,"更改","密码错误","确定","取消");
            }
        }else{
            QMessageBox::critical(this,"更改","用户名不存在","确定","取消");
        }
    }else{
        qx=2;
        ui->w_resgister->hide();
        ui->w_update->show();
    }
}
//删除
void guanli::on_pushButton_3_clicked()
{
    model=dynamic_cast<QSqlTableModel *>(ui->tableView->model());
    model->removeRow(ui->tableView->currentIndex().row());
    model->submitAll();
}
//退出
void guanli::on_pushButton_4_clicked()
{
    this->close();
}
