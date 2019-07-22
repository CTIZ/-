#include "rfid.h"
#include "ui_rfid.h"

rfid::rfid(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rfid)
{
    ui->setupUi(this);
}

rfid::~rfid()
{
    delete ui;
}

void rfid::on_pushButton_clicked()
{
    Dialog a;
    a.setWindowFlags(Qt::FramelessWindowHint);
    this->close();
    a.exec();
}
