#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "mylog.h"
#include "login.h"
#include "QPainter"
#include "QTimer"
#include "sql.h"
#include "serialdatahandle.h"
#include "serialportreceive.h"
#include "serialthread.h"
#include "tcpclientthread.h"
#include "tcpserver.h"
#include "QVector"
#include "mode1.h"
#include "mode2.h"
#include "mode3.h"
#include "mode4.h"

extern QString ip;
extern QString port;

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
    float temp_max,ill_max;
    int Modes;
    int tv,dvd,air;
    QVector<float> temp_v;
    QVector<float> ill_v;

    float N;

    Mode1 *mod1;
    Mode2 *mod2;
    Mode3 *mod3;
    Mode4 *mod4;


    QTimer *t1;
    QTimer *t2;
    QTimer *t3;
    QTimer *t4;
    QTimer *t5;

    void VarInit();
    void ScreenInit();
    void deceive_control(unsigned int board_number,unsigned int *pCmd,unsigned int len);
    
private slots:
    void getStr(QByteArray str);
    void see();
    void BoardInit();
    void ReadNodeData();
    void GetNodeData();
    void app_control(QString type,unsigned int command,unsigned int cmdCode,unsigned int channel);
    void upload(const QString & type,const QString & cmdCode,const QString & value);

    void FanCmd(unsigned int command);
    void LampCmd(unsigned int command,unsigned int channel);
    void WarningCmd(unsigned int command);
    void RfidCmd(unsigned int command);
    void CurtainCmd(unsigned int channel);
    void CurtainSleep();
    void InfraredEmit(unsigned int channel);
    void write_log(QString action);
    void Mode();
    void ModeHandle(QString type,unsigned int command,unsigned int channel);

    void play();
    void mydraw();
    bool eventFilter(QObject *a, QEvent *event);



    void on_pushButton_9_clicked();

    void on_btn_serial_clicked();

    void on_btn_tcp_clicked();

    void on_btn_server_clicked();

    void on_btn_tv_clicked();

    void on_btn_air_clicked();

    void on_btn_rfid_clicked();

    void on_btn_fan_clicked();

    void on_btn_lamp_clicked();

    void on_btn_warning_clicked();

    void on_btn_curtain_clicked();

    void on_cmb_max_currentIndexChanged(int index);

    void on_chk_log_clicked(bool checked);

    void on_radio_mode1_clicked();

    void on_radio_mode2_clicked();

    void on_radio_mode3_clicked();

    void on_radio_mode4_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
