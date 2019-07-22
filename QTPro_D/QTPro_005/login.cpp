#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    QFile f("userinfo.txt");
    if(f.open(QIODevice::ReadOnly)){
        QTextStream in(&f);
        if(in.readLine().mid(6)=="1"){
            ui->led_name->setText(in.readLine().mid(5));
            ui->led_pwd->setText(in.readLine().mid(4));
            ui->led_ip->setText(in.readLine().mid(3));
        }else{
            ui->checkBox->setChecked(0);
        }
        f.close();
    }


    ui->label->installEventFilter(this);
    m_cur=12;
    m_text="欢迎您使用智能家居系统";
//    m_width=QFontMetrics.width("a");
    m_width=4;
    QTimer *time=new QTimer(this);
    connect(time,SIGNAL(timeout()),this,SLOT(play()));
    time->start(500);
}
bool login::eventFilter(QObject *a, QEvent *event){
    if(a==ui->label&&event->type()==QEvent::Paint)
        mydraw();
    return QWidget::eventFilter(a,event);
}

void login::play(){
    update();
    m_cur++;
    if(m_cur*m_width>=this->width())
        m_cur=0;
}

void login::mydraw(){
    QPainter q(ui->label);
    q.drawText(0,30,m_text.left(m_cur));
    q.drawText(width()-m_cur*m_width,30,m_text.mid(m_cur));
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    QSqlQuery q;
    q.exec("select * from tb_userInfo where name='"+ui->led_name->text()+"' and pwd='"+ui->led_pwd->text()+"'");
    if(q.next()){
        if(ui->checkBox->isChecked()){
            QFile f("userinfo.txt");
            if(f.open(QIODevice::WriteOnly)){
                QTextStream in(&f);
                in<<"state=1\n"
                 <<"user="<<ui->led_name->text()<<"\n"
                <<"pwd="<<ui->led_pwd->text()<<"\n"
                <<"IP="<<ui->led_ip->text()<<endl;
                f.close();
            }
        }else{
            QFile f("userinfo.txt");
            if(f.open(QIODevice::WriteOnly)){
                QTextStream in(&f);
                in<<"state=0\n"
                 <<"user="<<ui->led_name->text()<<"\n"
                <<"pwd="<<ui->led_pwd->text()<<"\n"
                <<"IP="<<ui->led_ip->text()<<endl;
                f.close();
            }
        }
        Dialog a;
        a.setWindowFlags(Qt::FramelessWindowHint);
        this->close();
        a.exec();
    }
}

void login::on_pushButton_2_clicked()
{
    resgister a;
    a.setWindowFlags(Qt::FramelessWindowHint);
    a.exec();
}

