#ifndef LD_GUANLI_H
#define LD_GUANLI_H

#include <QDialog>
#include "dialog.h"
namespace Ui {
class ld_guanli;
}

class ld_guanli : public QDialog
{
    Q_OBJECT
    
public:
    explicit ld_guanli(QWidget *parent = 0);
    ~ld_guanli();
    QSqlTableModel *model;
    
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::ld_guanli *ui;
};

#endif // LD_GUANLI_H
