/**
  ******************************************************************************
  * @file    adaptivethreshold.cpp
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    自适应阈值设置窗体界面的控件操作
  ******************************************************************************
  */

#include "adaptivethreshold.h"
#include "ui_adaptivethreshold.h"
#include "adaptiveset.h"
#include <QMessageBox>
#include "mainwindow.h"

/**
* @brief  构造函数，继承自QDialog，设置窗口显示默认值
* @author  BugAngel
* @attention
*/
AdaptiveThreshold::AdaptiveThreshold(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adaptiveThreshold)
{
    ui->setupUi(this);
//    this->setAttribute(Qt::WA_DeleteOnClose);//窗口关闭时销毁窗口

    int method;
    int type;
    int blockSize;
    double C;

    adaptive_set.getValue(method,type,blockSize,C);

    ui->comboBoxMethod->setCurrentIndex(method);
    ui->comboBoxType->setCurrentIndex(type);
    ui->spinBox->setValue(blockSize);
    ui->doubleSpinBox->setValue(C);
}

/**
* @brief  析构函数
* @author  BugAngel
* @attention
*/
AdaptiveThreshold::~AdaptiveThreshold()
{
    delete ui;
}

/**
* @brief  取得自适应阈值设置窗口的值，并执行自适应阈值操作
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void AdaptiveThreshold::adaptiveThresholdFunction()
{
    int method;
    int type;
    int blockSize;
    double C;

    method=ui->comboBoxMethod->currentIndex();
    type=ui->comboBoxType->currentIndex();
    blockSize=ui->spinBox->value();
    C=ui->doubleSpinBox->value();

    adaptive_set.setValue(method,type,blockSize,C);

    MainWindow *ptr = (MainWindow*)parentWidget();  //"parentWidget" very important. 获得父部件指针，同时需要类型强转.
    ptr->on_adaptiveRadioButton_clicked();
}

/**
* @brief  改变自适应方法对应的下拉框，执行adaptiveThresholdFunction();
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void AdaptiveThreshold::on_comboBoxMethod_currentIndexChanged()
{
    adaptiveThresholdFunction();
}

/**
* @brief  改变阈值方法对应的下拉框，执行adaptiveThresholdFunction();
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void AdaptiveThreshold::on_comboBoxType_currentIndexChanged()
{
    adaptiveThresholdFunction();
}

/**
* @brief  改变块大小对应的数字框，执行adaptiveThresholdFunction();
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void AdaptiveThreshold::on_spinBox_valueChanged()
{
    adaptiveThresholdFunction();
}

/**
* @brief  改变常数值对应的数字框，执行adaptiveThresholdFunction();
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void AdaptiveThreshold::on_doubleSpinBox_valueChanged()
{
    adaptiveThresholdFunction();
}
