#ifndef MYLOG3_H
#define MYLOG3_H

#include <QDialog>
#include "dialog.h"
namespace Ui {
class myLog3;
}

class myLog3 : public QDialog
{
    Q_OBJECT
    
public:
    explicit myLog3(QWidget *parent = 0);
    ~myLog3();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::myLog3 *ui;
};

#endif // MYLOG3_H
