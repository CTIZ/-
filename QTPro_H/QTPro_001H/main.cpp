#include <QtGui/QApplication>
#include "login.h"
#include "QTextCodec"
#include "sql.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *code=QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForCStrings(code);
    QTextCodec::setCodecForLocale(code);
    QTextCodec::setCodecForTr(code);

    Sql sql;
    sql.sqlConnect("data.db");
    QSqlQuery q;
    //用户数据库
    q.exec("create table user(name varchar(40),pwd varchar(40))");
    q.exec("select * from user where name='bizideal'");
    if(q.next()){

    }else{
        q.exec("insert into user values('bizideal','123456')");
    }
    //本地数据库，存温度，烟雾
    q.exec("create table date(time varchar(40),type varchar(40),value varchar(40))");
    login w;
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.show();
    
    return a.exec();
}
