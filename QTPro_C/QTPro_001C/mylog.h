#ifndef MYLOG_H
#define MYLOG_H

#include <QDialog>

namespace Ui {
class mylog;
}

class mylog : public QDialog
{
    Q_OBJECT
    
public:
    explicit mylog(QWidget *parent = 0);
    ~mylog();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::mylog *ui;
};

#endif // MYLOG_H
