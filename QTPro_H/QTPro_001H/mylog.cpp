#include "mylog.h"
#include "ui_mylog.h"

Mylog::Mylog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mylog)
{
    ui->setupUi(this);
    QFile f("log.txt");
    if(f.open(QIODevice::ReadOnly)){
        QTextStream in(&f);
        ui->textEdit->setText(in.readAll());
        f.close();
    }
}

Mylog::~Mylog()
{
    delete ui;
}

void Mylog::on_pushButton_clicked()
{
    this->close();
}
