/**
  ******************************************************************************
  * @file    gaussianblur.cpp
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    高斯滤波设置窗体界面的控件操作
  ******************************************************************************
  */

#include "gaussianblur.h"
#include "ui_gaussianblur.h"
#include "gaussianblurset.h"
#include <QMessageBox>
#include "mainwindow.h"

/**
* @brief  构造函数，继承自QDialog，设置窗口显示默认值
* @author  BugAngel
* @attention
*/
GaussianBlur::GaussianBlur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GaussianBlur)
{
    ui->setupUi(this);
//    this->setAttribute(Qt::WA_DeleteOnClose);//窗口关闭时销毁窗口

    int width;
    int heigth;
    double sigmaX;
    double sigmaY;
    gaussianblur_set.getValue(width,heigth,sigmaX,sigmaY);

    ui->spinBox->setValue(width);
    ui->spinBox_2->setValue(heigth);
    ui->doubleSpinBox->setValue(sigmaX);
    ui->doubleSpinBox_2->setValue(sigmaY);
}

/**
* @brief  析构函数
* @author  BugAngel
* @attention
*/
GaussianBlur::~GaussianBlur()
{
    delete ui;
}

/**
* @brief  取得高斯滤波设置窗口的值，并执行高斯滤波操作
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void GaussianBlur::gaussianBlurFunction()
{
    int width;
    int heigth;
    double sigmaX;
    double sigmaY;

    width=ui->spinBox->value();
    heigth=ui->spinBox_2->value();
    sigmaX=ui->doubleSpinBox->value();
    sigmaY=ui->doubleSpinBox_2->value();

    if(width%2==0 || heigth%2==0){
        QMessageBox::information(this,
                                          tr("请输入合适的数字"),
                                          tr("高斯滤波算法中像素宽度和高度必须为正奇数!"));
        return;
    }
    gaussianblur_set.setValue(width,heigth,sigmaX,sigmaY);

    MainWindow *ptr = (MainWindow*)parentWidget();  //"parentWidget" very important. 获得父部件指针，同时需要类型强转.
    ptr->on_gaussianBlurRadioButton_clicked();
}

/**
* @brief  改变像素宽度对应的数字框，执行gaussianBlurFunction();
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void GaussianBlur::on_spinBox_valueChanged()
{
    gaussianBlurFunction();
}

/**
* @brief  改变像素高度对应的数字框，执行gaussianBlurFunction();
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void GaussianBlur::on_spinBox_2_valueChanged()
{
    gaussianBlurFunction();
}

/**
* @brief  改变sigmaX对应的数字框，执行gaussianBlurFunction();
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void GaussianBlur::on_doubleSpinBox_valueChanged()
{
    gaussianBlurFunction();
}

/**
* @brief  改变sigmaY对应的数字框，执行gaussianBlurFunction();
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void GaussianBlur::on_doubleSpinBox_2_valueChanged()
{
    gaussianBlurFunction();
}
