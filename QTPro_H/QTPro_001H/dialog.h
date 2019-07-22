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
#include "QPainter"
#include "mode1.h"
#include "mode2.h"
#include "mode3.h"
#include "mylog.h"
#include "QVector"

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
    int dvd,air,tv;
    int drawFlag;
    QVector<float> v_temp;
    QVector<float> v_ill;
    QVector<QBrush> v_color;

    float num_temp[3];
    float num_ill[3];

    QTimer *t1;
    QTimer *t2;
    QTimer *t3;
    QTimer *t4;
    QTimer *t5;

    Mode1 *mod1;
    Mode2 *mod2;
    Mode3 *mod3;


    void VarInit();
    void Deceive_control(unsigned int board_number,unsigned int *pCmd,unsigned int len);
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
    void RfidCmd(unsigned int command);
    void CurtainCmd(unsigned int channel);
    void CurtainSleep();
    void InfraredEmit(unsigned int channel);
    void writelog(QString action);

    void Mode();
    void ModeHandle(QString type,unsigned int command,unsigned int channel);

    void play();
    void mydraw();
    bool eventFilter(QObject *a, QEvent *event);
    
    void on_chk_warning_clicked(bool checked);

    void on_chk_fan_clicked(bool checked);

    void on_chk_rfid_clicked(bool checked);

    void on_btn_lamp1_clicked();

    void on_btn_lamp2_clicked();

    void on_btn_lamp_clicked();

    void on_btn_curtain_on_clicked();

    void on_btn_curtain_stop_clicked();

    void on_btn_curtain_off_clicked();

    void on_radio_tv_clicked();

    void on_radio_air_clicked();

    void on_radio_dvd_clicked();

    void on_cmb_infrared_currentIndexChanged(int index);

    void on_chk_log_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
