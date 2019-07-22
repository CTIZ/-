#ifndef RESGISTER_H
#define RESGISTER_H

#include <QDialog>
#include "login.h"

extern int qx;


namespace Ui {
class resgister;
}

class resgister : public QDialog
{
    Q_OBJECT
    
public:
    explicit resgister(QWidget *parent = 0);
    ~resgister();
    QSqlTableModel *model;
    
private slots:
    void Model();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

private:
    Ui::resgister *ui;
};

#endif // RESGISTER_H
