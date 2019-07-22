#include "mylog.h"
#include "ui_mylog.h"
#include "QFile"
#include "QTextStream"
mylog::mylog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mylog)
{
    ui->setupUi(this);
    QFile f("log.txt");
    if(f.open(QIODevice::ReadWrite)){
        QTextStream in(&f);
        ui->textEdit->setText(in.readAll());
        f.close();
    }
}

mylog::~mylog()
{
    delete ui;
}

void mylog::on_pushButton_clicked()
{
    this->close();
}
