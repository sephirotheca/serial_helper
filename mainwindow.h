#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QString>
#include <QTimer>
#include <QPainter>
#include "setwidget.h"
#include "chooselevelscene.h"
#include "mychart.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 绘图事件
    void paintEvent(QPaintEvent *);

    void init();
    void updateBg();
    void setBg(QString path);

private slots:
    void on_btnSwitch_clicked();

    void serialPortRead_Slot();

    void on_btnSend_clicked();

    void on_btnClearRec_clicked();

    void on_btnClearSend_clicked();

    void on_chkRec_stateChanged(int arg1);

    void on_chkSend_stateChanged(int arg1);

    void on_chkTimSend_stateChanged(int arg1);

    void chOpacity(int value);

private:
    Ui::MainWindow *ui;

    QSerialPort *mySerialPort;

    ChooseLevelScene * chooseScene = NULL;

    MyChart * chart = NULL;

    // 发送、接收字节计数
    long sendNum, recvNum;
    QLabel *lblSendNum;
    QLabel *lblRecvNum;
    void setNumOnLabel(QLabel *lbl, QString strS, long num);


    //set
    SetWidget * set = NULL;
    //图片位置
    QString pic_path = "";

    QStringList config[10];

    // 定时发送-定时器
    QTimer *timSend;
};
#endif // MAINWINDOW_H
