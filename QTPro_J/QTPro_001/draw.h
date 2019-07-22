#ifndef DRAW_H
#define DRAW_H

#include <QDialog>
#include "QPainter"
#include "dialog.h"
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
    QVector<float> v;
    QTimer *time;
    float N;

private slots:
    void mydraw();
    void play();
    bool eventFilter(QObject *a, QEvent *event);

private:
    Ui::Draw *ui;
};

#endif // DRAW_H
