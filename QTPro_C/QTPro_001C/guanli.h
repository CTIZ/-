#ifndef GUANLI_H
#define GUANLI_H

#include <QDialog>
#include "login.h"

extern int qx;

namespace Ui {
class guanli;
}

class guanli : public QDialog
{
    Q_OBJECT
    
public:
    explicit guanli(QWidget *parent = 0);
    ~guanli();
    QSqlTableModel *model;
    
private slots:
    void on_pushButton_2_clicked();

    void on_btn_delete_clicked();

private:
    Ui::guanli *ui;
};

#endif // GUANLI_H
