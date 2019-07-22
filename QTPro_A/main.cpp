#include <QtGui/QApplication>
#include "login.h"
#include "sql.h"
#include "QTextCodec"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *code=QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForCStrings(code);
    QTextCodec::setCodecForLocale(code);
    QTextCodec::setCodecForTr(code);

    Sql sql;
    sql.sqlConnect("data.db");

    login w;
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.show();
    
    return a.exec();
}
