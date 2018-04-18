/**
  ******************************************************************************
  * @file    blur.cpp
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    均值滤波设置窗体界面的控件操作
  ******************************************************************************
  */

#include "blur.h"
#include "ui_blur.h"
#include "blurset.h"
#include "mainwindow.h"

/**
* @brief  构造函数，继承自QDialog，设置窗口显示默认值
* @author  BugAngel
* @attention
*/
Blur::Blur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Blur)
{
    ui->setupUi(this);
//    this->setAttribute(Qt::WA_DeleteOnClose);//窗口关闭时销毁窗口

    int width;
    int height;
    blur_set.getValue(width,height);

    ui->spinBox->setValue(width);
    ui->spinBox_2->setValue(height);
}

/**
* @brief  析构函数
* @author  BugAngel
* @attention
*/
Blur::~Blur()
{
    delete ui;
}

/**
* @brief  取得均值滤波设置窗口的值，并执行均值滤波操作
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void Blur::blurFunction()
{
    int width;
    int heigth;

    width=ui->spinBox->value();
    heigth=ui->spinBox_2->value();

    blur_set.setValue(width,heigth);

    MainWindow *ptr = (MainWindow*)parentWidget();  //"parentWidget" very important. 获得父部件指针，同时需要类型强转.
    ptr->on_blurRadioButton_clicked();
}

/**
* @brief  改变像素宽度对应的数字框，执行blurFunction();
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void Blur::on_spinBox_valueChanged()
{
    blurFunction();
}

/**
* @brief  改变像素高度对应的数字框，执行blurFunction();
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void Blur::on_spinBox_2_valueChanged()
{
    blurFunction();
}
