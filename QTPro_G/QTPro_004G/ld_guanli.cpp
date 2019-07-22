#include "ld_guanli.h"
#include "ui_ld_guanli.h"

ld_guanli::ld_guanli(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ld_guanli)
{
    ui->setupUi(this);
    model=new QSqlTableModel();
    model->setTable("ld");
    model->select();
    model->setHeaderData(0,Qt::Horizontal,"设置时间");
    model->setHeaderData(1,Qt::Horizontal,"执行条件");
    model->setHeaderData(2,Qt::Horizontal,"执行器件");
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setModel(model);
}

ld_guanli::~ld_guanli()
{
    delete ui;
}

void ld_guanli::on_pushButton_2_clicked()
{
    this->close();
}

void ld_guanli::on_pushButton_clicked()
{
    model=dynamic_cast<QSqlTableModel *>(ui->tableView->model());
    model->removeRow(ui->tableView->currentIndex().row());
    model->submitAll();
}
