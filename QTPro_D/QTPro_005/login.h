#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "dialog.h"
#include "resgister.h"
#include "sql.h"
#include "QMessageBox"
#include "QPainter"
#include "QTimer"
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT
    
public:
    explicit login(QWidget *parent = 0);
    ~login();
    QString m_text;
    int m_cur;
    int m_width;
    
private slots:
    void mydraw();
    void play();
    bool eventFilter(QObject *a, QEvent *event);
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


private:
    Ui::login *ui;
};

#endif // LOGIN_H




