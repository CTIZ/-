#include "welcome.h"
#include "ui_welcome.h"

welcome::welcome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::welcome)
{
    ui->setupUi(this);
    i=0;
}

welcome::~welcome()
{
    delete ui;
}

void welcome::on_pushButton_clicked()
{
    this->close();
}

void welcome::on_pushButton_2_clicked()
{
    time=new QTimer(this);
    connect(time,SIGNAL(timeout()),this,SLOT(play()));
    time->start(50);
}
void welcome::play(){
    i+=2;
    ui->progressBar->setValue(i);
    switch(i){
    case 2:
        ui->label_2->setText("请稍等...");
        break;
    case 30:
        ui->label_2->setText("房间连接中");
        break;
    case 50:
        ui->label_2->setText("房间连接完成");
        break;
    case 70:
        ui->label_2->setText("房间界面初始化");
        break;
    case 90:
        ui->label_2->setText("房间界面加载完成");
        break;
    case 100:
        time->stop();
        rfid a;
        a.setWindowFlags(Qt::FramelessWindowHint);
        this->close();
        a.exec();
        break;
    }
}
