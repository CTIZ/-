#include "guanli.h"
#include "ui_guanli.h"

guanli::guanli(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::guanli)
{
    ui->setupUi(this);
    //数据模型
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
void guanli::on_pushButton_2_clicked()
{
    this->close();
}

void guanli::on_pushButton_clicked()
{
    //删除
    model=dynamic_cast<QSqlTableModel *>(ui->tableView->model());
    model->removeRow(ui->tableView->currentIndex().row());
    model->submitAll();
}
