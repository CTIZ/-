#ifndef GUANLI_H
#define GUANLI_H

#include <QDialog>
#include "login.h"
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
    int qx;
    
private slots:
    void Model();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::guanli *ui;
};

#endif // GUANLI_H
