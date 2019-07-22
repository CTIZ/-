#include "mylog3.h"
#include "ui_mylog3.h"

myLog3::myLog3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myLog3)
{
    ui->setupUi(this);
    QFile f("log.txt");
    if(f.open(QIODevice::ReadWrite)){
        QTextStream in(&f);
        ui->textEdit->setText(in.readAll());
        f.close();
    }
}

myLog3::~myLog3()
{
    delete ui;
}

void myLog3::on_pushButton_clicked()
{
    this->close();
}
