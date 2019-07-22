#ifndef RFID_H
#define RFID_H

#include <QDialog>
#include "dialog.h"
namespace Ui {
class rfid;
}

class rfid : public QDialog
{
    Q_OBJECT
    
public:
    explicit rfid(QWidget *parent = 0);
    ~rfid();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::rfid *ui;
};

#endif // RFID_H
