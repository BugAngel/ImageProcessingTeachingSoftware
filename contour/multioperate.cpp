#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "multioperateset.h"
#include <QMessageBox>
#include "showimage.h"

MultiOperateSet multiOperate_set;

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
    }
}

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
    }
}

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
    }
}

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
            }
        }
    }
}

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
        }
    }
}

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
    }
}


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
    showImg.setCurrentImageNum(1);//输出图像序号复位
}
