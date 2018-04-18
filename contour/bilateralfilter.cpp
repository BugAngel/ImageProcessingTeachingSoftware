/**
  ******************************************************************************
  * @file    bilateralfilter.cpp
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    双边滤波设置窗体界面的控件操作
  ******************************************************************************
  */

#include "bilateralfilter.h"
#include "ui_bilateralfilter.h"
#include "bilateralfilterset.h"
#include "mainwindow.h"

/**
* @brief  构造函数，继承自QDialog，设置窗口显示默认值
* @author  BugAngel
* @attention
*/
BilateralFilter::BilateralFilter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BilateralFilter)
{
    ui->setupUi(this);
//    this->setAttribute(Qt::WA_DeleteOnClose);//窗口关闭时销毁窗口

    int d;
    double sigmaColor;
    double sigmaSpace;
    bilateralfilter_set.getValue(d,sigmaColor,sigmaSpace);
    ui->spinBox->setValue(d);
    ui->doubleSpinBox->setValue(sigmaColor);
    ui->doubleSpinBox_2->setValue(sigmaSpace);
}

/**
* @brief  析构函数
* @author  BugAngel
* @attention
*/
BilateralFilter::~BilateralFilter()
{
    delete ui;
}

/**
* @brief  取得双边滤波设置窗口的值，并执行双边滤波操作
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void BilateralFilter::BilateralFilterFunction()
{
    int d;
    double sigmaColor;
    double sigmaSpace;

    d=ui->spinBox->value();
    sigmaColor=ui->doubleSpinBox->value();
    sigmaSpace=ui->doubleSpinBox_2->value();

    bilateralfilter_set.setValue(d,sigmaColor,sigmaSpace);

    MainWindow *ptr = (MainWindow*)parentWidget();  //"parentWidget" very important. 获得父部件指针，同时需要类型强转.
    ptr->on_bilateralFilterRadioButton_clicked();
}

/**
* @brief  改变像素邻域直径对应的数字框，执行BilateralFilterFunction();
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void BilateralFilter::on_spinBox_valueChanged()
{
    BilateralFilterFunction();
}

/**
* @brief  改变颜色空间滤波器的sigma值对应的数字框，执行BilateralFilterFunction();
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void BilateralFilter::on_doubleSpinBox_valueChanged()
{
    BilateralFilterFunction();
}

/**
* @brief  改变坐标空间滤波器的sigma值对应的数字框，执行BilateralFilterFunction();
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void BilateralFilter::on_doubleSpinBox_2_valueChanged()
{
    BilateralFilterFunction();
}
