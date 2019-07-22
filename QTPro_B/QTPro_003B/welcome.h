#ifndef WELCOME_H
#define WELCOME_H

#include <QDialog>
#include "rfid.h"
#include "QTimer"
namespace Ui {
class welcome;
}

class welcome : public QDialog
{
    Q_OBJECT
    
public:
    explicit welcome(QWidget *parent = 0);
    ~welcome();
    int i;
    QTimer *time;
    
private slots:
    void play();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::welcome *ui;
};

#endif // WELCOME_H
