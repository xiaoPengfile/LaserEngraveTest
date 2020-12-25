#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QSerialPort>
#include <QSerialPortInfo>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_searchSerialBtn_clicked();  //当检测串口按钮被点击   功能在端口消息下拉框中添加端口描述信息为USB-SERIAL CH340的端口， 添加时格式为：端口描述信息-->端口名
    void on_openSerialBtn_clicked();    //当打开串口按钮被点击
    void on_xLeftMoveBtn_clicked();     //当X-按钮被点击
    void on_xRightMoveBtn_clicked();    //当X+按钮被点击

    void onSerialReceiveMessage();      //当串口接收到消息时执行的槽函数  功能接受串口传来的消息，并在富文本上显示

    void on_xReverseBtn_clicked();

    void on_yReverseBtn_clicked();

    void on_zReverseBtn_clicked();

    void on_yLeftMoveBtn_clicked();

    void on_yRightMoveBtn_clicked();

    void on_zLeftMoveBtn_clicked();

    void on_zRightMoveBtn_clicked();

private:
    void sendSerialData(QByteArray &data, QColor color); //向发送串口发送数据
    void move(qreal X=0, qreal Y=0, qreal Z=0, qreal F=800);        //对XYZ轴进行移动
private:
    QSerialPort * m_serialProt;

    bool isXReverse;   //X轴是否反向
    bool isYReverse;   //Y轴是否反向
    bool isZReverse;   //Z轴是否反向

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
