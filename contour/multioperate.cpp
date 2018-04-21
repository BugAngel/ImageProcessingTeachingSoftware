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
#include "multioperateset.h"
#include <QMessageBox>
#include "showimage.h"

MultiOperateSet multiOperate_set;//这个对象来存储多步操作设置的值

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
        ui->secondOperateComboBox->setEnabled(true);
        on_firstOperateComboBox_currentIndexChanged();
    }
    else
    {
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
        ui->thirdOperateComboBox->setEnabled(true);
        on_secondOperateComboBox_currentIndexChanged();
    }
    else
    {
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
        ui->forthOperateComboBox->setEnabled(true);
        on_thirdOperateComboBox_currentIndexChanged();
    }
    else
    {
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
        ui->fifthOperateComboBox->setEnabled(true);
        on_forthOperateComboBox_currentIndexChanged();
    }
    else
    {
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
        ui->sixthOperateComboBox->setEnabled(true);
        on_fifthOperateComboBox_currentIndexChanged();
    }
    else
    {
        ui->sixthOperateCheckBox->setEnabled(false);
        ui->sixthOperateCheckBox->setChecked(false);
        ui->sixthOperateComboBox->setEnabled(false);//失能下拉框
    }
}

/**
* @brief  第一步操作的combobox改变，改变下面的，保证没有重复
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_firstOperateComboBox_currentIndexChanged()
{
    multiOperate_set.itemsAllTrue();
    multiOperate_set.setItemFalse(ui->firstOperateComboBox->currentText());

    if(ui->secondOperateCheckBox->isEnabled())
    {
        ui->secondOperateComboBox->clear();//清空下拉框内容
        ui->secondOperateComboBox->addItems(multiOperate_set.getCurrentItems());
        if(ui->thirdOperateCheckBox->isEnabled())
        {
            ui->thirdOperateComboBox->clear();//清空下拉框内容
            ui->thirdOperateComboBox->addItems(multiOperate_set.getCurrentItems());
            if(ui->forthOperateCheckBox->isEnabled())
            {
                ui->forthOperateComboBox->clear();//清空下拉框内容
                ui->forthOperateComboBox->addItems(multiOperate_set.getCurrentItems());
                if(ui->fifthOperateCheckBox->isEnabled())
                {
                    ui->fifthOperateComboBox->clear();//清空下拉框内容
                    ui->fifthOperateComboBox->addItems(multiOperate_set.getCurrentItems());
                    if(ui->sixthOperateCheckBox->isEnabled())
                    {
                        ui->sixthOperateComboBox->clear();//清空下拉框内容
                        ui->sixthOperateComboBox->addItems(multiOperate_set.getCurrentItems());
                    }
                }
            }
        }
    }
}

/**
* @brief  第二步操作的combobox改变，改变下面的，保证没有重复
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_secondOperateComboBox_currentIndexChanged()
{
    multiOperate_set.itemsAllTrue();
    multiOperate_set.setItemFalse(ui->firstOperateComboBox->currentText());
    multiOperate_set.setItemFalse(ui->secondOperateComboBox->currentText());

    if(ui->thirdOperateCheckBox->isEnabled())
    {
        ui->thirdOperateComboBox->clear();//清空下拉框内容
        ui->thirdOperateComboBox->addItems(multiOperate_set.getCurrentItems());
        if(ui->forthOperateCheckBox->isEnabled())
        {
            ui->forthOperateComboBox->clear();//清空下拉框内容
            ui->forthOperateComboBox->addItems(multiOperate_set.getCurrentItems());
            if(ui->fifthOperateCheckBox->isEnabled())
            {
                ui->fifthOperateComboBox->clear();//清空下拉框内容
                ui->fifthOperateComboBox->addItems(multiOperate_set.getCurrentItems());
                if(ui->sixthOperateCheckBox->isEnabled())
                {
                    ui->sixthOperateComboBox->clear();//清空下拉框内容
                    ui->sixthOperateComboBox->addItems(multiOperate_set.getCurrentItems());
                }
            }
        }
    }
}

/**
* @brief  第三步操作的combobox改变，改变下面的，保证没有重复
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_thirdOperateComboBox_currentIndexChanged()
{
    multiOperate_set.itemsAllTrue();
    multiOperate_set.setItemFalse(ui->firstOperateComboBox->currentText());
    multiOperate_set.setItemFalse(ui->secondOperateComboBox->currentText());
    multiOperate_set.setItemFalse(ui->thirdOperateComboBox->currentText());

    if(ui->forthOperateCheckBox->isEnabled())
    {
        ui->forthOperateComboBox->clear();//清空下拉框内容
        ui->forthOperateComboBox->addItems(multiOperate_set.getCurrentItems());
        if(ui->fifthOperateCheckBox->isEnabled())
        {
            ui->fifthOperateComboBox->clear();//清空下拉框内容
            ui->fifthOperateComboBox->addItems(multiOperate_set.getCurrentItems());
            if(ui->sixthOperateCheckBox->isEnabled())
            {
                ui->sixthOperateComboBox->clear();//清空下拉框内容
                ui->sixthOperateComboBox->addItems(multiOperate_set.getCurrentItems());
            }
        }
    }
}

void MainWindow::on_forthOperateComboBox_currentIndexChanged()
{
    multiOperate_set.itemsAllTrue();
    multiOperate_set.setItemFalse(ui->firstOperateComboBox->currentText());
    multiOperate_set.setItemFalse(ui->secondOperateComboBox->currentText());
    multiOperate_set.setItemFalse(ui->thirdOperateComboBox->currentText());
    multiOperate_set.setItemFalse(ui->forthOperateComboBox->currentText());

    if(ui->fifthOperateCheckBox->isEnabled())
    {
        ui->fifthOperateComboBox->clear();//清空下拉框内容
        ui->fifthOperateComboBox->addItems(multiOperate_set.getCurrentItems());
        if(ui->sixthOperateCheckBox->isEnabled())
        {
            ui->sixthOperateComboBox->clear();//清空下拉框内容
            ui->sixthOperateComboBox->addItems(multiOperate_set.getCurrentItems());
        }
    }
}

void MainWindow::on_fifthOperateComboBox_currentIndexChanged()
{
    multiOperate_set.itemsAllTrue();
    multiOperate_set.setItemFalse(ui->firstOperateComboBox->currentText());
    multiOperate_set.setItemFalse(ui->secondOperateComboBox->currentText());
    multiOperate_set.setItemFalse(ui->thirdOperateComboBox->currentText());
    multiOperate_set.setItemFalse(ui->forthOperateComboBox->currentText());
    multiOperate_set.setItemFalse(ui->fifthOperateComboBox->currentText());

    if(ui->sixthOperateCheckBox->isEnabled())
    {
        ui->sixthOperateComboBox->clear();//清空下拉框内容
        ui->sixthOperateComboBox->addItems(multiOperate_set.getCurrentItems());
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
    int index;//tab的index值
    if(ui->firstOperateCheckBox->isChecked())
    {
       showImg.setCurrentImageNum(1);
       index=multiOperate_set.getTabValue(ui->firstOperateComboBox->currentText());
       on_tabWidget_currentChanged(index);
    }
    if(ui->secondOperateCheckBox->isChecked())
    {
        showImg.setCurrentImageNum(2);
        index=multiOperate_set.getTabValue(ui->secondOperateComboBox->currentText());
        on_tabWidget_currentChanged(index);
    }
    if(ui->thirdOperateCheckBox->isChecked())
    {
        showImg.setCurrentImageNum(3);
        index=multiOperate_set.getTabValue(ui->thirdOperateComboBox->currentText());
        on_tabWidget_currentChanged(index);
    }
    if(ui->forthOperateCheckBox->isChecked())
    {
        showImg.setCurrentImageNum(4);
        index=multiOperate_set.getTabValue(ui->forthOperateComboBox->currentText());
        on_tabWidget_currentChanged(index);
    }
    if(ui->fifthOperateCheckBox->isChecked())
    {
        showImg.setCurrentImageNum(5);
        index=multiOperate_set.getTabValue(ui->forthOperateComboBox->currentText());
        on_tabWidget_currentChanged(index);
    }
    if(ui->sixthOperateCheckBox->isChecked())
    {
        showImg.setCurrentImageNum(6);
        index=multiOperate_set.getTabValue(ui->forthOperateComboBox->currentText());
        on_tabWidget_currentChanged(index);
    }
    showImg.setCurrentImageNum(1);//输出图像序号复位
}
