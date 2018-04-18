/**
  ******************************************************************************
  * @file    canny.cpp
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    canny边缘检测设置窗体界面的控件操作
  ******************************************************************************
  */

#include "canny.h"
#include "ui_canny.h"
#include "cannyset.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"

/**
* @brief  构造函数，继承自QDialog，设置窗口显示默认值
* @author  BugAngel
* @attention
*/
Canny::Canny(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Canny)
{
    ui->setupUi(this);

    double threshold1;
    double threshold2;
    int apertureSize;

    canny_set.getValue(threshold1,threshold2,apertureSize);

    ui->doubleSpinBox->setValue(threshold1);
    ui->doubleSpinBox_2->setValue(threshold2);
    ui->comboBox->setCurrentIndex((apertureSize-3)/2);
}

/**
* @brief  析构函数
* @author  BugAngel
* @attention
*/
Canny::~Canny()
{
    delete ui;
}

/**
* @brief  取得canny边缘检测设置窗口的值，并执行canny边缘检测操作
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void Canny::cannyFunction()
{
    double threshold1=ui->doubleSpinBox->value();
    double threshold2=ui->doubleSpinBox_2->value();
    int apertureSize=ui->comboBox->currentIndex()*2+3;//sobel孔径大小必须为3,5,7其中一个

    canny_set.setValue(threshold1,threshold2,apertureSize);

    MainWindow *ptr = (MainWindow*)parentWidget();  //"parentWidget" very important. 获得父部件指针，同时需要类型强转.
    ptr->on_cannyRadioButton_clicked();
}

/**
* @brief  改变第一个滞后性阈值对应的数字框，执行cannyFunction();
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void Canny::on_doubleSpinBox_valueChanged()
{
    cannyFunction();
}

/**
* @brief  改变第二个滞后性阈值对应的数字框，执行cannyFunction();
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void Canny::on_doubleSpinBox_2_valueChanged()
{
    cannyFunction();
}

/**
* @brief  改变Sobel算子的孔径大小对应的下拉框，执行cannyFunction();
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void Canny::on_comboBox_currentIndexChanged()
{
    cannyFunction();
}
