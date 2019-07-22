#ifndef RESGISTER_H
#define RESGISTER_H

#include <QDialog>
#include "login.h"
#include "sql.h"
#include "QRegExp"
namespace Ui {
class resgister;
}

class resgister : public QDialog
{
    Q_OBJECT
    
public:
    explicit resgister(QWidget *parent = 0);
    ~resgister();
    
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_led_name_editingFinished();

    void on_led_pwd_editingFinished();

    void on_led_repwd_editingFinished();

private:
    Ui::resgister *ui;
};

#endif // RESGISTER_H
