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
#include "mylog3.h"
#include "mode.h"
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

    int tv,dvd,air;

    int ReadNodeNum;

    Mode *mod;
    int Modes;

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
    void app_control(QString type,unsigned int command,unsigned int cmdCode,unsigned int channel);
    void upload(const QString & type,const QString & cmdCode,const QString & value);

    void mylog(QString action);
    void FanCmd(unsigned int command);
    void LampCmd(unsigned int command);
    void WarningCmd(unsigned int command);
    void RfidCmd(unsigned int command);
    void CurtainCmd(unsigned int channel);
    void CurtainSleep();
    void InfraredEmit(unsigned int channel);

    void ModeHandle(QString type,unsigned int command,unsigned int channel);
    
    void on_btn_lamp_clicked();

    void on_btn_rfid_clicked();

    void on_btn_fan_clicked();

    void on_btn__clicked();

    void on_btn_warning_clicked();

    void on_btn_tv_on_clicked();

    void on_btn_tv_off_clicked();

    void on_btn_dvd_on_clicked();

    void on_btn_dvd_off_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_btn_air_on_clicked();

    void on_btn_air_off_clicked();

    void on_btn_curtain_on_clicked();

    void on_btn_curtain_stop_clicked();

    void on_btn_curtain_off_clicked();

    void on_chk_log_clicked(bool checked);

    void on_btn_ld_clicked();

    void on_btn_ld2_d_clicked();

    void on_btn_ld2_x_clicked();

    void on_btn_ld4_k_clicked();

    void on_btn_ld4_g_clicked();

    void on_btn_ld5_tv_clicked();

    void on_btn_ld5_dvd_clicked();

    void on_pushButton_14_clicked();

    void on_btn_ld5_air_clicked();

    void on_btn_ld5_rfid_clicked();

    void on_btn_ld5_fan_clicked();

    void on_pushButton_18_clicked();

    void on_btn_ld5_warning_clicked();

    void on_btn_ld5_lamp_clicked();

    void on_btn_ld5_curtain_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H








