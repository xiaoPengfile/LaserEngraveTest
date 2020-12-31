#include "grblwindow.h"
#include <QHeaderView>
#include <QStringList>
#include <QSizePolicy>
#include <QVBoxLayout>
#include <QDebug>


GrblWindow::GrblWindow(QWidget *parent) : QDialog(parent)
{
    setPalette(QPalette(QColor(255,255,0)));
    m_grblWin = new QTableWidget(this);
    this->setFixedSize(QSize(1248,930));
    m_grblWin->setGeometry(10,10,1228,877);
    QSizePolicy sizePolicy;
    sizePolicy.setVerticalPolicy(QSizePolicy::Fixed);
    sizePolicy.setHorizontalPolicy(QSizePolicy::Fixed);
    m_grblWin->setSizePolicy(sizePolicy);
    this->setWindowTitle("grbl配置");

    //添加写入按钮
    m_writeBtn = new QPushButton(this);
    m_writeBtn->setText("写入配置");
    m_writeBtn->setGeometry(1150,897,90,23);

    connect(m_writeBtn, SIGNAL(clicked()), this, SLOT(onModfiyGrblConfig()));
}



void GrblWindow::onGetGrblInfo(QString data)
{
    m_receiveData = data;

    m_grblWin->setRowCount(34);    //设置行数
    m_grblWin->setColumnCount(5);  //设置列数
    QStringList tableHeaderList;
    tableHeaderList << "#" << "参数" << "值" << "单位" << "描述";
    m_grblWin->setHorizontalHeaderLabels(tableHeaderList);
//    m_grblWin->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //列等宽

//    //列宽自动适应
//    m_grblWin->horizontalHeader()->setStretchLastSection(true);
//    m_grblWin->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    //自定列宽
    m_grblWin->setColumnWidth(0,40);
    m_grblWin->setColumnWidth(1,210);
    m_grblWin->setColumnWidth(2,65);
    m_grblWin->setColumnWidth(3,88);
    m_grblWin->setColumnWidth(4,800);

   // m_grblWin->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);   //设置自动设置行宽
    for(int i = 0; i<34; i++)
    {
         m_grblWin->setRowHeight(i,20);
    }

    QStringList dataList = m_receiveData.split("\r\n");
    QStringList lineList;
    for(int i = 0; i< 34; i++)
    {
        lineList = dataList.at(i).split("=");
        m_grblWin->setItem(i,0,new QTableWidgetItem(lineList.at(0)));
        m_grblWin->setItem(i,2,new QTableWidgetItem(lineList.at(1)));
    }

    //往表单中存无规律放数据
    loadParameterColumn();
    loadUnitColumn();
    loadDescriptionColumn();

    //对数据进行处理去除数据中多余的"\r"和"ok\n"
    m_receiveData.remove("\r");
    m_receiveData.remove("ok\n");
}

void GrblWindow::loadParameterColumn()
{
    m_grblWin->setItem(0,1,new QTableWidgetItem("Step pulse time"));
    m_grblWin->setItem(1,1,new QTableWidgetItem("Step idle delay"));
    m_grblWin->setItem(2,1,new QTableWidgetItem("Step pulse invert"));
    m_grblWin->setItem(3,1,new QTableWidgetItem("Step direction invert"));
    m_grblWin->setItem(4,1,new QTableWidgetItem("Invert step enable pin"));
    m_grblWin->setItem(5,1,new QTableWidgetItem("Invert limit pins"));
    m_grblWin->setItem(6,1,new QTableWidgetItem("Invert probe pin"));
    m_grblWin->setItem(7,1,new QTableWidgetItem("Status report options"));
    m_grblWin->setItem(8,1,new QTableWidgetItem("Junction deviation"));
    m_grblWin->setItem(9,1,new QTableWidgetItem("Arc tolerance"));
    m_grblWin->setItem(10,1,new QTableWidgetItem("Report in inches"));
    m_grblWin->setItem(11,1,new QTableWidgetItem("Soft limits enable"));
    m_grblWin->setItem(12,1,new QTableWidgetItem("Hard linits enable"));
    m_grblWin->setItem(13,1,new QTableWidgetItem("Homing cycle enable"));
    m_grblWin->setItem(14,1,new QTableWidgetItem("Homing direction invert"));
    m_grblWin->setItem(15,1,new QTableWidgetItem("Homing locate feed rate"));
    m_grblWin->setItem(16,1,new QTableWidgetItem("Homing search seek rate"));
    m_grblWin->setItem(17,1,new QTableWidgetItem("Homing switch debounce delay"));
    m_grblWin->setItem(18,1,new QTableWidgetItem("Homing switch pull-off distance"));
    m_grblWin->setItem(19,1,new QTableWidgetItem("Maximum spindel speed"));
    m_grblWin->setItem(20,1,new QTableWidgetItem("Minimum spindel speed"));
    m_grblWin->setItem(21,1,new QTableWidgetItem("Laser-model enable"));
    m_grblWin->setItem(22,1,new QTableWidgetItem("X-axis travel resolution"));
    m_grblWin->setItem(23,1,new QTableWidgetItem("Y-axis travel resolution"));
    m_grblWin->setItem(24,1,new QTableWidgetItem("Z-axis travel resolution"));
    m_grblWin->setItem(25,1,new QTableWidgetItem("X-axis maximum rate"));
    m_grblWin->setItem(26,1,new QTableWidgetItem("Y-axis maximum rate"));
    m_grblWin->setItem(27,1,new QTableWidgetItem("Z-axis maximum rate"));
    m_grblWin->setItem(28,1,new QTableWidgetItem("X-axis acceleration"));
    m_grblWin->setItem(29,1,new QTableWidgetItem("Y-axis acceleration"));
    m_grblWin->setItem(30,1,new QTableWidgetItem("Z-axis acceleration"));
    m_grblWin->setItem(31,1,new QTableWidgetItem("X-axis maximum travel"));
    m_grblWin->setItem(32,1,new QTableWidgetItem("Y-axis maximum travel"));
    m_grblWin->setItem(33,1,new QTableWidgetItem("Z-axis maximum travel"));
}

void GrblWindow::loadUnitColumn()
{
    m_grblWin->setItem(0,3,new QTableWidgetItem("microseconds"));
    m_grblWin->setItem(1,3,new QTableWidgetItem("milliseconds"));
    m_grblWin->setItem(2,3,new QTableWidgetItem("mask"));
    m_grblWin->setItem(3,3,new QTableWidgetItem("mask"));
    m_grblWin->setItem(4,3,new QTableWidgetItem("boolean"));
    m_grblWin->setItem(5,3,new QTableWidgetItem("boolean"));
    m_grblWin->setItem(6,3,new QTableWidgetItem("boolean"));
    m_grblWin->setItem(7,3,new QTableWidgetItem("mask"));
    m_grblWin->setItem(8,3,new QTableWidgetItem("millimeters"));
    m_grblWin->setItem(9,3,new QTableWidgetItem("millimeters"));
    m_grblWin->setItem(10,3,new QTableWidgetItem("boolean"));
    m_grblWin->setItem(11,3,new QTableWidgetItem("boolean"));
    m_grblWin->setItem(12,3,new QTableWidgetItem("boolean"));
    m_grblWin->setItem(13,3,new QTableWidgetItem("boolean"));
    m_grblWin->setItem(14,3,new QTableWidgetItem("mask"));
    m_grblWin->setItem(15,3,new QTableWidgetItem("mm/min"));
    m_grblWin->setItem(16,3,new QTableWidgetItem("mm/min"));
    m_grblWin->setItem(17,3,new QTableWidgetItem("milliseconds"));
    m_grblWin->setItem(18,3,new QTableWidgetItem("millimeters"));
    m_grblWin->setItem(19,3,new QTableWidgetItem("RPM"));
    m_grblWin->setItem(20,3,new QTableWidgetItem("RPM"));
    m_grblWin->setItem(21,3,new QTableWidgetItem("boolean"));
    m_grblWin->setItem(22,3,new QTableWidgetItem("step/mm"));
    m_grblWin->setItem(23,3,new QTableWidgetItem("step/mm"));
    m_grblWin->setItem(24,3,new QTableWidgetItem("step/mm"));
    m_grblWin->setItem(25,3,new QTableWidgetItem("mm/min"));
    m_grblWin->setItem(26,3,new QTableWidgetItem("mm/min"));
    m_grblWin->setItem(27,3,new QTableWidgetItem("mm/min"));
    m_grblWin->setItem(28,3,new QTableWidgetItem("mm/sec^2"));
    m_grblWin->setItem(29,3,new QTableWidgetItem("mm/sec^2"));
    m_grblWin->setItem(30,3,new QTableWidgetItem("mm/sec^2"));
    m_grblWin->setItem(31,3,new QTableWidgetItem("millimeters"));
    m_grblWin->setItem(32,3,new QTableWidgetItem("millimeters"));
    m_grblWin->setItem(33,3,new QTableWidgetItem("millimeters"));
}

void GrblWindow::loadDescriptionColumn()
{
    m_grblWin->setItem(0,4,new QTableWidgetItem("Sets time length per step. Minimum 3usec"));
    m_grblWin->setItem(1,4,new QTableWidgetItem("Sets a short hold delay when stopping to let dynamics settle before disabling steppers. Value 255 keeps motors enabled with no delay."));
    m_grblWin->setItem(2,4,new QTableWidgetItem("Inverts the step signal. set axis bit to invert (00000ZYX)"));
    m_grblWin->setItem(3,4,new QTableWidgetItem("Inverts the direction signal. Set axis bit to invert (0000ZXY)"));
    m_grblWin->setItem(4,4,new QTableWidgetItem("Inverts the stepper driver enable pin signal."));
    m_grblWin->setItem(5,4,new QTableWidgetItem("Inverts the all of the limit input pins."));
    m_grblWin->setItem(6,4,new QTableWidgetItem("Inverts the probe input pin signal."));
    m_grblWin->setItem(7,4,new QTableWidgetItem("Alters data included in status reports."));
    m_grblWin->setItem(8,4,new QTableWidgetItem("Sets how fast Grbl travels through consecutive motions. Lower value slows it down"));
    m_grblWin->setItem(9,4,new QTableWidgetItem("Sets the G2 and G3 arc tracing accuracy based on radial error. Beware: A very small value may effect performance."));
    m_grblWin->setItem(10,4,new QTableWidgetItem("Enables inch units when returning any position and rate value that is not a settings value."));
    m_grblWin->setItem(11,4,new QTableWidgetItem("Enables soft limits checks within machine travel and sets alarm when exceeded. Requires homing."));
    m_grblWin->setItem(12,4,new QTableWidgetItem("Enables hard limits. Immediately halts motion and throws an alarm when switch is triggered."));
    m_grblWin->setItem(13,4,new QTableWidgetItem("Enables homing cycle. Requires limit switch on all axes."));
    m_grblWin->setItem(14,4,new QTableWidgetItem("Homing searches for a switch in the positve direction. set acis bit (00000ZXY) to search in negative direction."));
    m_grblWin->setItem(15,4,new QTableWidgetItem("Feed rate to slowly engage limit switch to determine its location accurately."));
    m_grblWin->setItem(16,4,new QTableWidgetItem("Seek rate to quickly find the limit switch before the slower locating phase."));
    m_grblWin->setItem(17,4,new QTableWidgetItem("Sets a short delay betwwen phases of homing cycle to let a switch debounce."));
    m_grblWin->setItem(18,4,new QTableWidgetItem("Retract distance after triggering switch to disengage it. Homing will fail if switch isn’t cleared."));
    m_grblWin->setItem(19,4,new QTableWidgetItem("Maximum spindle speed. Sets PWM to 100% duty cycle."));
    m_grblWin->setItem(20,4,new QTableWidgetItem("Minimum soindle speed. Sets PWM to 0.4% or lowest duty cycle."));
    m_grblWin->setItem(21,4,new QTableWidgetItem("Enables laser mode. Consecutive G1/2/3 commands will not halt when spindle speed is changed."));
    m_grblWin->setItem(22,4,new QTableWidgetItem("X-axis travel resolution in steps per millimeter."));
    m_grblWin->setItem(23,4,new QTableWidgetItem("Y-axis travel resolution in steps per millimeter."));
    m_grblWin->setItem(24,4,new QTableWidgetItem("Z-axis travel resolution in steps per millimeter."));
    m_grblWin->setItem(25,4,new QTableWidgetItem("X-axis maximum rate. Used as Go rapid rate."));
    m_grblWin->setItem(26,4,new QTableWidgetItem("Y-axis maximum rate. Used as Go rapid rate."));
    m_grblWin->setItem(27,4,new QTableWidgetItem("Z-axis maximum rate. Used as Go rapid rate."));
    m_grblWin->setItem(28,4,new QTableWidgetItem("X-axis acceleration. Used for motion planning to not exceed motor torque and lose steps."));
    m_grblWin->setItem(29,4,new QTableWidgetItem("Y-axis acceleration. Used for motion planning to not exceed motor torque and lose steps."));
    m_grblWin->setItem(30,4,new QTableWidgetItem("Z-axis acceleration. Used for motion planning to not exceed motor torque and lose steps."));
    m_grblWin->setItem(31,4,new QTableWidgetItem("Maximum X-axis travel diatance from homing switch. Determines valid machine space for soft-limits and homing search distances."));
    m_grblWin->setItem(32,4,new QTableWidgetItem("Maximum Y-axis travel diatance from homing switch. Determines valid machine space for soft-limits and homing search distances."));
    m_grblWin->setItem(33,4,new QTableWidgetItem("Maximum z-axis travel diatance from homing switch. Determines valid machine space for soft-limits and homing search distances."));
}

void GrblWindow::onModfiyGrblConfig()
{
    QString column2;  //保存参数数值
    qint32 index1 =0;   //“=”下标索引
    qint32 index2 =0;   //“\r\n”下标索引
    for(int i=0; i<34; i++)
    {
        column2 = m_grblWin->item(i,2)->text();
        index1 = m_receiveData.indexOf("=",index1);
        index2 = m_receiveData.indexOf("\n",index1);
        qint32 valueLength = index2 - index1-1; //获取参数值得长度
        m_receiveData.replace(index1+1,valueLength,column2); //对参数值进行替换
        index1 = index1+valueLength+2;
    }
    qDebug() << m_receiveData << endl;
    emit singnalSenderConfigInfo(m_receiveData);
}
