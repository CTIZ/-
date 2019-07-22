#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "sql.h"
#include "draw.h"
#include "serialdatahandle.h"
#include "serialportreceive.h"
#include "serialthread.h"
#include "tcpclientthread.h"
#include "tcpserver.h"
#include "QTimer"
#include "mode1.h"
#include "mode2.h"
#include "mode3.h"
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
    int Modes;
    bool mode_ld;

    QTimer *t1;
    QTimer *t2;
    QTimer *t3;
    QTimer *t4;

    Mode1 *mod1;
    Mode2 *mod2;
    Mode3 *mod3;

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
    void RfidCmd(unsigned int command);
    void CurtainCmd(unsigned int channel);
    void CurtainSleep();
    void InfraredEmit(unsigned int channel);
    void write_log(QString action);
    void Mode();
    void ModeHandle(QString type,unsigned int command,unsigned int channel);

    void on_pushButton_3_clicked();

    void on_chk_fan_clicked(bool checked);

    void on_chk_warning_clicked(bool checked);

    void on_chk_lamp_clicked(bool checked);

    void on_chk_rfid_clicked(bool checked);

    void on_chk_curtain_clicked(bool checked);

    void on_btn_curtain_clicked();

    void on_btn_lamp_clicked();

    void on_btn_warning_clicked();

    void on_radio_infrared_clicked();

    void on_radio_dandu_clicked();

    void on_radio_mode_clicked();

    void on_timeEdit_timeChanged(const QTime &date);

    void on_chk_log_clicked(bool checked);

    void on_btn_ld_clicked();

    void on_btn_draw_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
