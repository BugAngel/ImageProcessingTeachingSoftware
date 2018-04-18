/**
  ******************************************************************************
  * @file    contour.cpp
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    轮廓检测设置窗体界面的控件操作
  ******************************************************************************
  */

#include "contour.h"
#include "ui_contour.h"
#include "contourset.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
* @brief  构造函数，继承自QDialog，设置窗口显示默认值
* @author  BugAngel
* @attention
*/
Contour::Contour(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::contour)
{
    ui->setupUi(this);

    double thresh;
    int mode;
    int method;

    contour_set.getValue(thresh,mode,method);

    ui->doubleSpinBox->setValue(thresh);
    ui->comboBox->setCurrentIndex(mode);
    ui->comboBox_2->setCurrentIndex(method);
}

/**
* @brief  析构函数
* @author  BugAngel
* @attention
*/
Contour::~Contour()
{
    delete ui;
}

/**
* @brief  取得轮廓检测设置窗口的值，并执行轮廓检测操作
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void Contour::contourFunction()
{
    double thresh=ui->doubleSpinBox->value();
    int mode=ui->comboBox->currentIndex();
    int method=ui->comboBox_2->currentIndex();

    contour_set.setValue(thresh,mode,method);

    MainWindow *ptr = (MainWindow*)parentWidget();  //"parentWidget" very important. 获得父部件指针，同时需要类型强转.
    ptr->on_contourRadioButton_clicked();
}

/**
* @brief  改变阈值对应的数字框，执行cannyFunction();
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void Contour::on_doubleSpinBox_valueChanged()
{
    contourFunction();
}

/**
* @brief  改变轮廓检索模式对应的下拉框，执行cannyFunction();
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void Contour::on_comboBox_currentIndexChanged()
{
    contourFunction();
}

/**
* @brief  改变轮廓近似方法对应的下拉框，执行cannyFunction();
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void Contour::on_comboBox_2_currentIndexChanged()
{
    contourFunction();
}
