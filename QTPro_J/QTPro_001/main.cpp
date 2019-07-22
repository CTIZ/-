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
    //连接数据库
    Sql sql;
    sql.sqlConnect("data.db");
    //创建数据表，并插入数据
    QSqlQuery q;
    q.exec("create table user(name varchar(40),pwd varchar(40))");
    q.exec("select * from user where name='bizideal'");
    if(q.next()){

    }else{
        q.exec("insert into user values('bizideal','123456')");
    }
    login w;
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.show();
    
    return a.exec();
}
