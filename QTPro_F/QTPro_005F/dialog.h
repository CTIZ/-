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
#include "draw.h"
#include "mode1.h"
#include "mode2.h"
#include "mode3.h"
#include "mode4.h"
#include "mode5.h"

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
    int Modes_z;
    int dvd,air,tv;

    QTimer *t1;
    QTimer *t2;
    QTimer *t3;
    QTimer *t4;

    Mode1 *mod1;
    Mode2 *mod2;
    Mode3 *mod3;
    Mode4 *mod4;
    Mode5 *mod5;


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
    void data_update();

    void FanCmd(unsigned int command);
    void LampCmd(unsigned int command,unsigned int channel);
    void WarningCmd(unsigned int command);
    void RfidCmd(unsigned int command);
    void CurtainCmd(unsigned int channel);
    void CurtainSleep();
    void InfraredEmit(unsigned int channel);

    void Mode();
    void ModeHandle(QString type,unsigned int command,unsigned int channel);
    
    void on_pushButton_11_clicked();

    void on_icon_warning_clicked();

    void on_icon_lamp_clicked();

    void on_btn_warning_clicked();

    void on_btn_lamp_clicked();

    void on_btn_fan_clicked();

    void on_btn_rfid_clicked();

    void on_btn_curtain_on_clicked();

    void on_btn_curtain_off_clicked();

    void on_icon_curtain_clicked();

    void on_radio_dankong_clicked();

    void on_radio_mode_clicked();

    void on_radio_ld_clicked();

    void on_btn_infrared_clicked();

    void on_btn_tv_clicked();

    void on_btn_dvd_clicked();

    void on_btn_air_clicked();

    void on_radio_mode1_clicked();

    void on_radio_mode2_clicked();

    void on_radio_mode3_clicked();

    void on_radio_mode4_clicked();

    void on_btn_draw_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
