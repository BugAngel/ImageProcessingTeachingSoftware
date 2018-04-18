/**
  ******************************************************************************
  * @file    boxfilter.cpp
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    方框滤波设置窗体界面的控件操作
  ******************************************************************************
  */

#include "boxfilter.h"
#include "ui_boxfilter.h"
#include "boxfilterset.h"
#include "filter.h"
#include "mainwindow.h"
#include <QDebug>

/**
* @brief  构造函数，继承自QDialog，设置窗口显示默认值
* @author  BugAngel
* @attention
*/
BoxFilter::BoxFilter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BoxFilter)
{
    ui->setupUi(this);
//    this->setAttribute(Qt::WA_DeleteOnClose);//窗口关闭时销毁窗口

    int width;
    int Heigth;
    boxfilter_set.getValue(width,Heigth);

    ui->spinBox_2->setValue(width);
    ui->spinBox_3->setValue(Heigth);
}

/**
* @brief  析构函数
* @author  BugAngel
* @attention
*/
BoxFilter::~BoxFilter()
{
    delete ui;
}

/**
* @brief  取得方框滤波设置窗口的值，并执行方框滤波操作
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void BoxFilter::boxFilterFunction()
{
    int width;
    int heigth;

    width=ui->spinBox_2->value();
    heigth=ui->spinBox_3->value();

    boxfilter_set.setValue(width,heigth);

    MainWindow *ptr = (MainWindow*)parentWidget();  //"parentWidget" very important. 获得父部件指针，同时需要类型强转.
    ptr->on_boxFilterRadioButton_clicked();
}

/**
* @brief  改变像素宽度对应的数字框，执行boxFilterFunction();
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void BoxFilter::on_spinBox_2_valueChanged()
{
    boxFilterFunction();
}

/**
* @brief  改变像素高度对应的数字框，执行boxFilterFunction();
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void BoxFilter::on_spinBox_3_valueChanged()
{
    boxFilterFunction();
}
