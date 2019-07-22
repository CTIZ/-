#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "sql.h"
#include "QTimer"
#include "serialdatahandle.h"
#include "serialportreceive.h"
#include "serialthread.h"
#include "tcpclientthread.h"
#include "tcpserver.h"
#include "VariableDefinition.h"
#include "mode1.h"
#include "mode2.h"
#include "mode3.h"
#include "mode4.h"
#include "draw.h"


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
    QSqlTableModel *model;

    int ReadNodeNum;
    int tv,dvd,air;
    int Modes;

    QTimer *t1;
    QTimer *t2;
    QTimer *t3;
    QTimer *t4;

    Mode1 *mod1;
    Mode2 *mod2;
    Mode3 *mod3;
    Mode4 *mod4;

    void VarInit();
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
    void LampCmd(unsigned int command);
    void WarningCmd(unsigned int command);
    void CurtainCmd(unsigned int channel);
    void RfidCmd(unsigned int command);
    void CurtainSleep();
    void InfraredEmit(unsigned int channel);

    void Mode();
    void ModeHandle(QString type,unsigned int command,unsigned int channel);
    
    void on_btn_serialopen_clicked();

    void on_btn_tcp_clicked();

    void on_btn_server_clicked();

    void on_btn_warning_clicked();

    void on_btn_curtain_clicked();

    void on_btn_rfid_clicked();

    void on_btn_lamp_clicked();

    void on_btn_fan_clicked();

    void on_btn_air_clicked();

    void on_btn_dvd_clicked();

    void on_btn_tv_clicked();

    void on_btn_ld_clicked();

    void on_chk1_clicked(bool checked);

    void on_chk2_clicked(bool checked);

    void on_chk3_clicked(bool checked);

    void on_chk4_clicked(bool checked);

    void on_radio_mode1_clicked();

    void on_radio_mode2_clicked();

    void on_radio_mode3_clicked();

    void on_btn_temp_clicked();

    void on_btn_hum_clicked();

    void on_btn_ill_clicked();

    void on_btn_smoke_clicked();

    void on_btn_ap_clicked();

    void on_btn_pm_clicked();

    void on_btn_co2_clicked();

    void on_btn_gas_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H


