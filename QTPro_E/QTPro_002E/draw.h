#ifndef DRAW_H
#define DRAW_H

#include <QDialog>
#include "dialog.h"
#include "QVector"
#include "QPainter"
namespace Ui {
class Draw;
}

class Draw : public QDialog
{
    Q_OBJECT
    
public:
    explicit Draw(QWidget *parent = 0);
    ~Draw();
    QVector<float> v;
private slots:
    void play();
    void mydraw();
    bool eventFilter(QObject *a, QEvent *event);
    
private:
    Ui::Draw *ui;
};

#endif // DRAW_H
