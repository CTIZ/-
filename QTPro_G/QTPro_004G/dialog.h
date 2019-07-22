#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "sql.h"
#include "QTimer"
#include "VariableDefinition.h"
#include "serialdatahandle.h"
#include "serialportreceive.h"
#include "serialthread.h"
#include "tcpclientthread.h"
#include "tcpserver.h"
#include "mode.h"
#include "QPainter"
#include "ld_guanli.h"
#include "QVector"
extern QString ip;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
private:
    SerialDataHandle *SerialHandle;
    SerialThread *Serial;
    TcpClientThread *myTcp;
    TcpServer *Server;
    Sql sql;

    int ReadNodeNum;
    int dvd,air,tv;

    QVector<float> ill_num;
    QVector<float> temp_num;
    int draw_f;

    QList<QBrush> d_color;
    Mode *mod;

    QTimer *t1;
    QTimer *t2;
    QTimer *t3;
    QTimer *t4;

    void VarInit();
    void deceive_control(unsigned int board_number,unsigned int *pCmd,unsigned int len);

private slots:
    void getStr(QByteArray str);
    void see();
    void BoardInit();
    void ReadNodeData();
    void GetNodeData();
    void upload(const QString & type,const QString & cmdCode,const QString & value);
    void app_control(QString type,unsigned int command,unsigned int cmdCode,unsigned int channel);

    void FanCmd(unsigned int command);
    void LampCmd(unsigned int command,unsigned int channel);
    void WarningCmd(unsigned int command);
    void CurtainCmd(unsigned int channel);
    void CurtainSleep();
    void RfidCmd(unsigned int command);
    void InfraredEmit(unsigned int channel);
    
    void mySql(QString action);
    void ModeHandle(QString type,unsigned int command,unsigned int channel,QString value);

    void play();
    void mydraw();
    bool eventFilter(QObject *a, QEvent *event);

    void on_chk_warning_clicked(bool checked);

    void on_chk_fan_clicked(bool checked);

    void on_chk_rfid_clicked(bool checked);

    void on_radio_tv_clicked();

    void on_radio_air_clicked();

    void on_radio_dvd_clicked();

    void on_cmb_infrared_currentIndexChanged(int index);

    void on_btn_curtain_on_clicked();

    void on_btn_curtain_stop_clicked();

    void on_btn_curtain_off_clicked();

    void on_btn_lamp1_clicked();

    void on_btn_lamp2_clicked();

    void on_btn_lamp_clicked();

    void on_btn_save_clicked();

    void on_ben_chakan_clicked();

    void on_chk_ld_clicked(bool checked);

    void on_cmb_draw_currentIndexChanged(int index);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
