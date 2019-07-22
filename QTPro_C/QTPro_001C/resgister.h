#ifndef RESGISTER_H
#define RESGISTER_H

#include <QDialog>
#include "login.h"
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

private:
    Ui::resgister *ui;
};

#endif // RESGISTER_H
