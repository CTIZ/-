#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "resgister.h"
#include "guanli.h"
#include "dialog.h"
#include "sql.h"
#include "QMessageBox"
#include "QMouseEvent"
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT
    
public:
    explicit login(QWidget *parent = 0);
    ~login();
    int num[4];
    int px,py;
    
private slots:
    void yzm();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();


private:
    Ui::login *ui;
};

#endif // LOGIN_H
