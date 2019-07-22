#ifndef DRAW_H
#define DRAW_H

#include <QDialog>
#include "dialog.h"
#include "QPainter"
#include "QVector"
namespace Ui {
class Draw;
}

class Draw : public QDialog
{
    Q_OBJECT
    
public:
    explicit Draw(QWidget *parent = 0);
    ~Draw();
    QTimer *time;
    QVector<float> v;

private slots:
    void play();
    void mydraw();
    bool eventFilter(QObject *a, QEvent *event);
    void on_pushButton_clicked();

    void on_checkBox_clicked(bool checked);

private:
    Ui::Draw *ui;
};

#endif // DRAW_H
