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
#include "mode.h"
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
private slots:
    void on_pushButton_2_clicked();
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
    void RfidCmd(unsigned int command);
    void CurtainCmd(unsigned int channel);
    void CurtainSleep();
    void InfraredEmit(unsigned int channel);

    void ModeHandle(QString type,unsigned int command,unsigned int channel);

    void on_icon_curtain_clicked();

    void on_btn_curtain_clicked();

    void on_icon_fan_clicked();

    void on_btn_fan_clicked();

    void on_icon_lamp_clicked();

    void on_btn_lamp_clicked();

    void on_btn_warning_clicked();

    void on_btn_rfid_clicked();

    void on_icon_tv_clicked();

    void on_btn_tv_clicked();

    void on_icon_dvd_clicked();

    void on_btn_dvd_clicked();

    void on_icon_air_clicked();

    void on_btn_air_clicked();



    void on_sp_infrared_valueChanged(int arg1);

    void on_btn_ok_clicked();


    void on_chk_mode_clicked(bool checked);

    void on_pushButton_clicked();

    void on_btn_clear_clicked();

private:
    SerialDataHandle *SerialHandle;
    SerialThread *Serial;
    TcpClientThread *myTcp;
    TcpServer *Server;
    Sql sql;

    Mode *mod1;

    int ReadNodeNum;

    int dvd,air,tv;


    QTimer *t1;
    QTimer *t2;
    QTimer *t3;
    QTimer *t4;

    void VarInit();
    void deceive_control(unsigned int board_number,unsigned int *pCmd,unsigned int len);
    
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H


