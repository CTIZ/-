#ifndef DRAW_H
#define DRAW_H

#include <QDialog>
#include "QPainter"
#include "QVector"
#include "dialog.h"

extern volatile float temp_value;
extern volatile float hum_value;
extern volatile float ill_value;
extern volatile float air_value;
extern volatile unsigned int co2_value;
extern volatile unsigned int pm_value;
extern volatile unsigned int gas_value;
extern volatile unsigned int smoke_value;

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
    int N;


private slots:
    void play();
    void mydraw();
    bool eventFilter(QObject *a, QEvent *event);
    
private:
    Ui::Draw *ui;
};

#endif // DRAW_H
