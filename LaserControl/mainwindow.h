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
    void onSerialReceiveMessage();      //当串口接收到消息时执行的槽函数  功能接受串口传来的消息，并在富文本上显

    void on_searchSerialBtn_clicked();  //当检测串口按钮被点击   功能在端口消息下拉框中添加端口描述信息为USB-SERIAL CH340的端口， 添加时格式为：端口描述信息-->端口名

    void on_openSerialBtn_clicked();    //当打开串口按钮被点击

    void on_xLeftMoveBtn_clicked();     //当X-按钮被点击
    void on_xRightMoveBtn_clicked();    //当X+按钮被点击
    void on_yLeftMoveBtn_clicked();     //当Y-按钮被点击
    void on_yRightMoveBtn_clicked();    //当Y+按钮被点击
    void on_zLeftMoveBtn_clicked();     //当Z-按钮被点击
    void on_zRightMoveBtn_clicked();    //当Z+按钮被点击

    void on_xReverseBtn_clicked();      //当x轴反向按钮被点击时
    void on_yReverseBtn_clicked();      //当y轴反向按钮被点击时
    void on_zReverseBtn_clicked();      //当Z轴反向按钮被点击时

    void on_openLaserBtn_clicked();     //打开激光按钮被点击
    void on_setTheOriginBtn_clicked();  //当设置原点被点击时
    void on_RegressionOriginBtn_clicked();  //当回归原点被点击时

    void on_unlockBtn_clicked();        //解锁按钮被点击时

    void on_restorationBtn_clicked();   //复位按钮被点击时

    void on_pauseBtn_clicked();         //暂停按钮被点击时

    void on_continueBtn_clicked();      //继续按钮被点击时

private:
    void initViewBtn();
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
