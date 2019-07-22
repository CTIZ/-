#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "dialog.h"
#include "resgister.h"
#include "sql.h"
#include "QMessageBox"
#include "guanli.h"
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT
    
public:
    explicit login(QWidget *parent = 0);
    ~login();
    Sql sql;
    
private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
