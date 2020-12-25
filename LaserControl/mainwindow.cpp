#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainWindow)
    ,isXReverse(false)
    ,isYReverse(false)
    ,isZReverse(false)
{
    ui->setupUi(this);
    ui->xLeftMoveBtn->setEnabled(false);
    ui->xRightMoveBtn->setEnabled(false);
    m_serialProt = new QSerialPort(this);

    //在端口号下拉框添加数据
    on_searchSerialBtn_clicked();

    ui->viewTextEdit->setReadOnly(true);

    ui->baudRateComb->setCurrentIndex(4);

    connect(m_serialProt, &QSerialPort::readyRead, this, &MainWindow::onSerialReceiveMessage);
    /*
    QString serialProtName = ui->serialPortNameComb->currentText();
    qDebug() << serialProtName << endl;
    */

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_xLeftMoveBtn_clicked()
{
    qreal xStep = ui->xStepLineEidt->text().toFloat();
    qreal fSpeed = ui->fSpeedLineEdit->text().toFloat();

    //判断X轴是否反向
    if(isXReverse==false)
    {
        move(xStep*(-1),0,0,fSpeed);
    }
    else
    {
        move(xStep,0,0,fSpeed);
    }
}

void MainWindow::on_xRightMoveBtn_clicked()
{
    qreal xStep = ui->xStepLineEidt->text().toFloat();
    qreal fSpeed = ui->fSpeedLineEdit->text().toFloat();

    //判断X轴是否反向
    if(isXReverse==false)
    {
        move(xStep,0,0,fSpeed);
    }
    else
    {
        move(xStep*(-1),0,0,fSpeed);
    }
}

 //当串口接收到消息时执行的槽函数  功能接受串口传来的消息，并在富文本上显示
void MainWindow::onSerialReceiveMessage()
{
    QString data = m_serialProt->readAll();
    /*
    if(data.size() == 0)
    {
        return;
    }
    */
    data = "->>" + data;
    ui->viewTextEdit->setTextColor("Red");
    ui->viewTextEdit->append(data);
}

void MainWindow::sendSerialData(QByteArray &data, QColor color)
{
    m_serialProt->write(data);
    ui->viewTextEdit->setTextColor(color);
    data = "<<-" + data;
    ui->viewTextEdit->append(data);
}

void MainWindow::move(qreal X, qreal Y, qreal Z, qreal F)
{
    QByteArray data = (QString("$J=G21G91X%1Y%2Z%3F%4\n").arg(X).arg(Y).arg(Z).arg(F)).toUtf8();
    sendSerialData(data,QColor(0,0,255));
}


//在端口消息下拉框中添加端口描述信息为USB-SERIAL CH340的端口
//添加时格式为   端口描述信息-->端口名
void MainWindow::on_searchSerialBtn_clicked()
{
    ui->serialPortNameComb->clear();
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QString portDes = info.description();
        if(portDes.indexOf("USB-SERIAL CH340") != -1)
        {
            QString itemData = portDes + "-->" + info.portName();
            ui->serialPortNameComb->addItem(itemData);
            int index = ui->serialPortNameComb->count()-1;
            ui->serialPortNameComb->setCurrentIndex(index);
        }
    }
}


void MainWindow::on_openSerialBtn_clicked()
{
    if(ui->openSerialBtn->text() == "打开串口")
    {
        //设置端口名
        QString serialPortName = ui->serialPortNameComb->currentText();
        //判断最后的数值有几位
        QString numStr = serialPortName.right(2);
        qint8 num = numStr.toInt();
        if(num==0)
        {
            serialPortName = serialPortName.right(4);
        }
        else if(num >= 10)
        {
            serialPortName = serialPortName.right(5);
        }
        m_serialProt->setPortName(serialPortName);

        //设置数据位
        num = ui->dataBitsComb->currentText().toInt();
        switch (num)
        {
        case 8:
            m_serialProt->setDataBits(QSerialPort::Data8);
            break;
        default:
            break;
        }

        //设置波特率
        m_serialProt->setBaudRate(ui->baudRateComb->currentText().toInt());

        //设置停止位
        num = ui->stopBitComb->currentText().toInt();
        switch (num)
        {
        case 1:
            m_serialProt->setStopBits(QSerialPort::OneStop);
            break;
        case 2:
            m_serialProt->setStopBits(QSerialPort::TwoStop);
            break;
        default:
            break;
        }

        //设置校验位
        m_serialProt->setParity(QSerialPort::NoParity);

        //设置流控制
        m_serialProt->setFlowControl(QSerialPort::NoFlowControl);

        //打开串口
        if(!m_serialProt->open(QIODevice::ReadWrite))
        {
            QMessageBox::information(this,"警告","串口打开失败");
            return;
        }
        else
        {
            QMessageBox::information(this,"提示","串口打开成功");
            ui->serialPortNameComb->setEnabled(false);
            ui->dataBitsComb->setEnabled(false);
            ui->baudRateComb->setEnabled(false);
            ui->stopBitComb->setEnabled(false);
            ui->parityBitComb->setEnabled(false);
            ui->searchSerialBtn->setEnabled(false);

            ui->xLeftMoveBtn->setEnabled(true);
            ui->xRightMoveBtn->setEnabled(true);
        }
        ui->openSerialBtn->setText("关闭串口");
    }
    else
    {
        m_serialProt->close();
        ui->openSerialBtn->setText("打开串口");
        ui->serialPortNameComb->setEnabled(true);
        ui->dataBitsComb->setEnabled(true);
        ui->baudRateComb->setEnabled(true);
        ui->stopBitComb->setEnabled(true);
        ui->parityBitComb->setEnabled(true);
        ui->searchSerialBtn->setEnabled(true);

        ui->xLeftMoveBtn->setEnabled(false);
        ui->xRightMoveBtn->setEnabled(false);
    }

}

void MainWindow::on_xReverseBtn_clicked()
{
    if(isXReverse==false)
    {
        isXReverse = true;
    }
    else
    {
        isXReverse = false;
    }
}

void MainWindow::on_yReverseBtn_clicked()
{
    if(isYReverse == false)
    {
        isYReverse = true;
    }
    else
    {
        isYReverse = false;
    }
}

void MainWindow::on_zReverseBtn_clicked()
{
    if(isZReverse == false)
    {
        isZReverse = true;
    }
    else
    {
        isZReverse = false;
    }
}
