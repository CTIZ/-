#include "resgister.h"
#include "ui_resgister.h"

resgister::resgister(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::resgister)
{
    ui->setupUi(this);
    //界面元素隐藏
    ui->w_resgister->hide();
    ui->w_update->hide();
    //判断界面元素显示哪个
    if(qx==1){
        ui->w_resgister->show();
    }else if(qx==2){
        ui->w_update->show();
    }
    //数据模型
    Model();
}
void resgister::Model(){
    model=new QSqlTableModel();
    model->setTable("user");
    model->select();
    model->setHeaderData(0,Qt::Horizontal,"用户名");
    model->setHeaderData(1,Qt::Horizontal,"密码");
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setModel(model);
}

resgister::~resgister()
{
    delete ui;
}
//注册
void resgister::on_pushButton_2_clicked()
{
    if(qx==1){
        if(ui->led_resgister_pwd->text()!=ui->led_resgister_repwd->text()){
            QMessageBox::critical(this,"注册","密码和确认密码不相同","确定","取消");
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
//修改
void resgister::on_pushButton_3_clicked()
{
    if(qx==2){
        QSqlQuery q;
        q.exec("select * from user where name='"+ui->led_update_name->text()+"' and pwd='"+ui->led_update_pwd->text()+"'");
        if(q.next()){
            if(ui->led_update_Npwd->text()!=ui->led_update_repwd->text()){
                QMessageBox::critical(this,"修改","新密码和确认密码不相同","确定","取消");
            }else{
                q.exec("update user set pwd='"+ui->led_update_Npwd->text()+"' where name='"+ui->led_update_name->text()+"' and pwd='"+ui->led_update_pwd->text()+"'");
                Model();
            }
        }else{
            QMessageBox::critical(this,"修改","用户名或密码错误","确定","取消");
        }
    }else{
        qx=2;
        ui->w_resgister->hide();
        ui->w_update->show();
    }
}
//删除
void resgister::on_pushButton_4_clicked()
{
    qx=0;
    ui->w_resgister->hide();
    ui->w_update->hide();
    model=dynamic_cast<QSqlTableModel *>(ui->tableView->model());
    model->removeRow(ui->tableView->currentIndex().row());
    model->submitAll();
}

void resgister::on_pushButton_clicked()
{
    this->close();
}
