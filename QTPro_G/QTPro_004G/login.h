#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "sql.h"
#include "QMessageBox"
#include "guanli.h"
#include "resgister.h"
#include "QMouseEvent"
#include "QTimer"
#include "dialog.h"
#include "QLabel"
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT
    
public:
    explicit login(QWidget *parent = 0);
    ~login();
    int px,py;
    int num[4];


    
private slots:
    void yzm();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
