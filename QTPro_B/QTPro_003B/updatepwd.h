#ifndef UPDATEPWD_H
#define UPDATEPWD_H

#include <QDialog>
#include "login.h"
namespace Ui {
class updatepwd;
}

class updatepwd : public QDialog
{
    Q_OBJECT
    
public:
    explicit updatepwd(QWidget *parent = 0);
    ~updatepwd();
    
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::updatepwd *ui;
};

#endif // UPDATEPWD_H
