#ifndef CLEAN_H
#define CLEAN_H

#include <QDialog>
#include "QTimer"
namespace Ui {
class Clean;
}

class Clean : public QDialog
{
    Q_OBJECT
    
public:
    explicit Clean(QWidget *parent = 0);
    ~Clean();
    int i;
    QTimer *time;
    
private slots:
    void play();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Clean *ui;
};

#endif // CLEAN_H
