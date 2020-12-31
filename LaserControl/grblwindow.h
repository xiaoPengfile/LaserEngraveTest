#ifndef GRBLWINDOW_H
#define GRBLWINDOW_H

#include <QTableWidget>
#include <QDialog>
#include <QPushButton>

class GrblWindow : public QDialog
{
    Q_OBJECT
public:
    explicit GrblWindow(QWidget *parent = nullptr);

private:

public slots:
    void onGetGrblInfo(QString data);  //当有信息发送来时对信息进行进行处理，并进行展示
    void loadParameterColumn();  //加载参数列
    void loadUnitColumn();       //加载单位
    void loadDescriptionColumn(); //加载描述

private:
    QTableWidget *m_grblWin;
    QString m_receiveData;    //保存读取到的grbl的数据
    QPushButton * m_writeBtn; //写入配置按钮


public slots:
    void onModfiyGrblConfig(); //当写入配置按钮被点击时执行

signals:
    void singnalSenderConfigInfo(QString data);
};

#endif // GRBLWINDOW_H
