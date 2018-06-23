/**
  ******************************************************************************
  * @file    multioperate.cpp
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    多步操作控件功能
  ******************************************************************************
  */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "showimage.h"
#include "file.h"

/**
* @brief  第一步操作的checkbox状态改变，选上了使能第二个，取消了失能下面的;
* @param  arg1 第一步操作的checkbox的状态值
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_firstOperateCheckBox_stateChanged(int arg1)
{
    if(arg1!=0)
    {
        ui->secondOperateCheckBox->setEnabled(true);
        ui->firstOperateComboBox->setEnabled(true);
//        on_firstOperateComboBox_currentTextChanged();
    }
    else
    {
        ui->firstOperateComboBox->setEnabled(false);

        ui->secondOperateCheckBox->setEnabled(false);
        ui->secondOperateCheckBox->setChecked(false);
        ui->secondOperateComboBox->setEnabled(false);//失能下拉框

        ui->thirdOperateCheckBox->setEnabled(false);
        ui->thirdOperateCheckBox->setChecked(false);
        ui->thirdOperateComboBox->setEnabled(false);//失能下拉框

        ui->forthOperateCheckBox->setEnabled(false);
        ui->forthOperateCheckBox->setChecked(false);
        ui->forthOperateComboBox->setEnabled(false);//失能下拉框

        ui->fifthOperateCheckBox->setEnabled(false);
        ui->fifthOperateCheckBox->setChecked(false);
        ui->fifthOperateComboBox->setEnabled(false);//失能下拉框

        ui->sixthOperateCheckBox->setEnabled(false);
        ui->sixthOperateCheckBox->setChecked(false);
        ui->sixthOperateComboBox->setEnabled(false);//失能下拉框
    }
}

/**
* @brief  第二步操作的checkbox状态改变，选上了使能第三个，取消了失能下面的;
* @param  arg1 第二步操作的checkbox的状态值
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_secondOperateCheckBox_stateChanged(int arg1)
{
    if(arg1!=0)
    {
        ui->thirdOperateCheckBox->setEnabled(true);
        ui->secondOperateComboBox->setEnabled(true);
//        on_secondOperateComboBox_currentTextChanged();
    }
    else
    {
        ui->secondOperateComboBox->setEnabled(false);

        ui->thirdOperateCheckBox->setEnabled(false);
        ui->thirdOperateCheckBox->setChecked(false);
        ui->thirdOperateComboBox->setEnabled(false);//失能下拉框

        ui->forthOperateCheckBox->setEnabled(false);
        ui->forthOperateCheckBox->setChecked(false);
        ui->forthOperateComboBox->setEnabled(false);//失能下拉框

        ui->fifthOperateCheckBox->setEnabled(false);
        ui->fifthOperateCheckBox->setChecked(false);
        ui->fifthOperateComboBox->setEnabled(false);//失能下拉框

        ui->sixthOperateCheckBox->setEnabled(false);
        ui->sixthOperateCheckBox->setChecked(false);
        ui->sixthOperateComboBox->setEnabled(false);//失能下拉框
    }
}

/**
* @brief  第三步操作的checkbox状态改变，选上了使能第四个，取消了失能下面的;
* @param  arg1 第三步操作的checkbox的状态值
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_thirdOperateCheckBox_stateChanged(int arg1)
{
    if(arg1!=0)
    {
        ui->forthOperateCheckBox->setEnabled(true);
        ui->thirdOperateComboBox->setEnabled(true);
//        on_thirdOperateComboBox_currentTextChanged();
    }
    else
    {
        ui->thirdOperateComboBox->setEnabled(false);

        ui->forthOperateCheckBox->setEnabled(false);
        ui->forthOperateCheckBox->setChecked(false);
        ui->forthOperateComboBox->setEnabled(false);//失能下拉框

        ui->fifthOperateCheckBox->setEnabled(false);
        ui->fifthOperateCheckBox->setChecked(false);
        ui->fifthOperateComboBox->setEnabled(false);//失能下拉框

        ui->sixthOperateCheckBox->setEnabled(false);
        ui->sixthOperateCheckBox->setChecked(false);
        ui->sixthOperateComboBox->setEnabled(false);//失能下拉框
    }
}

/**
* @brief  第四步操作的checkbox状态改变，选上了使能第五个，取消了失能下面的;
* @param  arg1 第四步操作的checkbox的状态值
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_forthOperateCheckBox_stateChanged(int arg1)
{
    if(arg1!=0)
    {
        ui->fifthOperateCheckBox->setEnabled(true);
        ui->forthOperateComboBox->setEnabled(true);
//        on_forthOperateComboBox_currentTextChanged();
    }
    else
    {
        ui->forthOperateComboBox->setEnabled(false);

        ui->fifthOperateCheckBox->setEnabled(false);
        ui->fifthOperateCheckBox->setChecked(false);
        ui->fifthOperateComboBox->setEnabled(false);//失能下拉框

        ui->sixthOperateCheckBox->setEnabled(false);
        ui->sixthOperateCheckBox->setChecked(false);
        ui->sixthOperateComboBox->setEnabled(false);//失能下拉框
    }
}

/**
* @brief  第五步操作的checkbox状态改变，选上了使能第六个，取消了失能下面的;
* @param  arg1 第五步操作的checkbox的状态值
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_fifthOperateCheckBox_stateChanged(int arg1)
{
    if(arg1!=0)
    {
        ui->sixthOperateCheckBox->setEnabled(true);
        ui->fifthOperateComboBox->setEnabled(true);
//        on_fifthOperateComboBox_currentTextChanged();
    }
    else
    {
        ui->fifthOperateComboBox->setEnabled(false);

        ui->sixthOperateCheckBox->setEnabled(false);
        ui->sixthOperateCheckBox->setChecked(false);
        ui->sixthOperateComboBox->setEnabled(false);//失能下拉框
    }
}

void MainWindow::on_sixthOperateCheckBox_stateChanged(int arg1)
{
    if(arg1!=0)
    {
        ui->sixthOperateComboBox->setEnabled(true);
    }
    else
    {
        ui->sixthOperateComboBox->setEnabled(false);
    }
}

/**
* @brief  多步操作处理按键按下，根据下拉框的内容依次处理，之后将CurrentImageNum复位
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_multiOperatePushButton_clicked()
{
    if(ui->firstOperateCheckBox->isChecked())
    {
       showImg.setCurrentImageNum(1);
       file.setFileString();
       on_tabWidget_currentChanged(ui->firstOperateComboBox->currentIndex());
    }
    if(ui->secondOperateCheckBox->isChecked())
    {
        showImg.setCurrentImageNum(2);
        file.setFileString();
        on_tabWidget_currentChanged(ui->secondOperateComboBox->currentIndex());
    }
    if(ui->thirdOperateCheckBox->isChecked())
    {
        showImg.setCurrentImageNum(3);
        file.setFileString();
        on_tabWidget_currentChanged(ui->thirdOperateComboBox->currentIndex());
    }
    if(ui->forthOperateCheckBox->isChecked())
    {
        showImg.setCurrentImageNum(4);
        file.setFileString();
        on_tabWidget_currentChanged(ui->forthOperateComboBox->currentIndex());
    }
    if(ui->fifthOperateCheckBox->isChecked())
    {
        showImg.setCurrentImageNum(5);
        file.setFileString();
        on_tabWidget_currentChanged(ui->fifthOperateComboBox->currentIndex());
    }
    if(ui->sixthOperateCheckBox->isChecked())
    {
        showImg.setCurrentImageNum(6);
        file.setFileString();
        on_tabWidget_currentChanged(ui->sixthOperateComboBox->currentIndex());
    }
    showImg.setCurrentImageNum(1);//输出图像序号复位
    file.setFileString();//文件名复位
}
