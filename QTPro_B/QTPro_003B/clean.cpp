#include "clean.h"
#include "ui_clean.h"

//打扫模式


Clean::Clean(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Clean)
{
    ui->setupUi(this);
}

Clean::~Clean()
{
    delete ui;
}

void Clean::on_pushButton_clicked()
{
    this->close();
}

void Clean::on_pushButton_2_clicked()
{
    time=new QTimer(this);
    connect(time,SIGNAL(timeout()),this,SLOT(play()));
    //50毫秒一次
    time->start(50);
}
void Clean::play(){
    i+=2;
    ui->progressBar->setValue(i);
    switch(i){
    case 2:
        ui->label_2->setText("请稍等...");
        break;
    case 30:
        ui->label_2->setText("正在准备打扫工具...");
        break;
    case 50:
        ui->label_2->setText("正在打扫...");
        break;
    case 70:
        ui->label_2->setText("已打扫干净");
        break;
    case 100:
        time->stop();
        this->close();
        break;
    }
}
