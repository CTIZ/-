#include "guanli.h"
#include "ui_guanli.h"

guanli::guanli(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::guanli)
{
    ui->setupUi(this);
    model=new QSqlTableModel();
    model->setTable("user");
    model->select();
    model->setHeaderData(0,Qt::Horizontal,"用户名");
    model->setHeaderData(1,Qt::Horizontal,"密码");
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setModel(model);
}

guanli::~guanli()
{
    delete ui;
}
//退出
void guanli::on_pushButton_2_clicked()
{
    this->close();
}
//删除数据
void guanli::on_pushButton_clicked()
{
    model=dynamic_cast<QSqlTableModel *>(ui->tableView->model());
    model->removeRow(ui->tableView->currentIndex().row());
    model->submitAll();
}
