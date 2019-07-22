#ifndef MYLOG_H
#define MYLOG_H

#include <QDialog>
#include "QFile"
#include "QTextStream"
namespace Ui {
class Mylog;
}

class Mylog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Mylog(QWidget *parent = 0);
    ~Mylog();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::Mylog *ui;
};

#endif // MYLOG_H
