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
#include "clean.h"
#include "draw.h"
#include "mode1.h"
#include "mode2.h"
#include "mode3.h"

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

    Mode1 *mod1;
    Mode2 *mod2;
    Mode3 *mod3;

    int ReadNodeNum;
    int dvd,tv,air;
    bool af_mode,sm_mode,ld_mode;


    QTimer *t1;
    QTimer *t2;
    QTimer *t3;
    QTimer *t4;

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
    void ModeHandle(QString type,unsigned int command,unsigned int channel);

    void Lx();

    void on_pushButton_11_clicked();

    void on_btn_serial_clicked();

    void on_btn_tcp_clicked();

    void on_btn_lamp_clicked();

    void on_btn_warning_clicked();

    void on_btn_rfid_clicked();

    void on_btn_fan_clicked();

    void on_btn_curtain_clicked();

    void on_btn_air_clicked();

    void on_btn_tv_clicked();

    void on_btn_dvd_clicked();

    void on_btn_clean_clicked();

    void on_btn_wdl_clicked();

    void on_btn_lx_clicked();

    void on_btn_lxfs_clicked();

    void on_btn_mode1_clicked();

    void on_btn_mode2_clicked();

    void on_pushButton_clicked();

    void on_chk1_clicked(bool checked);

    void on_chk2_clicked(bool checked);

    void on_chk3_clicked(bool checked);

    void on_chk4_clicked(bool checked);

    void on_btn_draw_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
