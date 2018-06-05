/**
  ******************************************************************************
  * @file    morph.cpp
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    主窗口二值化部分控件操作
  ******************************************************************************
  */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "file.h"
#include "showimage.h"

#include "adaptiveset.h"
#include "adaptivethreshold.h"

/**
* @brief  显示灰度图
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention 注意灰度按钮的ID是6
*/
void MainWindow::on_grayRadioButton_clicked()
{   
    ui->helpTextBrowser->clear();

    QFile txtFile("gray.txt");
    if(!txtFile.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::information(this,
                                 tr("打开讲解文件失败"),
                                 tr("请重新安装本软件"));
        return;
    }
    //构建QTextStream以便读取文本
    QTextStream txtFileContent(&txtFile);
    //将应用程序的光标设置为等待状态
    QApplication::setOverrideCursor(Qt::WaitCursor);
    //将读取的所有文本设置到QTextEdit控件中显示出来
    ui->helpTextBrowser->insertPlainText(txtFileContent.readAll());
    //读取完成后，恢复光标状态
    QApplication::restoreOverrideCursor();

    ui->grayRadioButton->setChecked(true);

    try{
        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString);//输入图像
        if(!srcImage.data )
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("请打开合适的图像"));
            return;
        }
        cv::Mat dstImage;//输出图像
        int num=showImg.getCurrentImageNum();//当前图像数目
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        cv::cvtColor(srcImage,dstImage,CV_RGB2GRAY);
        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("图像处理失败"),
                                          tr("操作过程出错！"));
    }
}

/**
* @brief  Binary单选按钮按下，显示说明，执行Binary;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_radioButton_Binary_clicked()
{
    double thresh=ui->binaryDoubleSpinBox->value();
    ui->helpTextBrowser->clear();
    char temp[200];
    sprintf(temp,"数字框的值为阈值,其值为:%.2f\n\n",thresh);
    ui->helpTextBrowser->insertPlainText(temp);

    QFile txtFile("binary.txt");
    if(!txtFile.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::information(this,
                                 tr("打开讲解文件失败"),
                                 tr("请重新安装本软件"));
        return;
    }
    //构建QTextStream以便读取文本
    QTextStream txtFileContent(&txtFile);
    //将应用程序的光标设置为等待状态
    QApplication::setOverrideCursor(Qt::WaitCursor);
    //将读取的所有文本设置到QTextEdit控件中显示出来
    ui->helpTextBrowser->insertPlainText(txtFileContent.readAll());
    //读取完成后，恢复光标状态
    QApplication::restoreOverrideCursor();

    ui->radioButton_Binary->setChecked(true);

    try{
        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString,0);//输入图像
        if(!srcImage.data )
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("请打开合适的图像"));
            return;
        }
        cv::Mat dstImage;//输出图像
        int num=showImg.getCurrentImageNum();//当前图像数目
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        cv::threshold(srcImage,dstImage,thresh,255,cv::THRESH_BINARY);
        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                 tr("图像处理失败"),
                                 tr("操作过程出错！"));
    }
}

/**
* @brief  BinaryInv单选按钮按下，显示说明，执行BinaryInv;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_radioButton_BinaryInv_clicked()
{
    double thresh=ui->binaryInvDoubleSpinBox->value();
    ui->helpTextBrowser->clear();
    char temp[200];
    sprintf(temp,"数字框的值为阈值,其值为:%.2f\n\n",thresh);
    ui->helpTextBrowser->insertPlainText(temp);

    QFile txtFile("binaryinv.txt");
    if(!txtFile.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::information(this,
                                 tr("打开讲解文件失败"),
                                 tr("请重新安装本软件"));
        return;
    }
    //构建QTextStream以便读取文本
    QTextStream txtFileContent(&txtFile);
    //将应用程序的光标设置为等待状态
    QApplication::setOverrideCursor(Qt::WaitCursor);
    //将读取的所有文本设置到QTextEdit控件中显示出来
    ui->helpTextBrowser->insertPlainText(txtFileContent.readAll());
    //读取完成后，恢复光标状态
    QApplication::restoreOverrideCursor();

    ui->radioButton_BinaryInv->setChecked(true);

    try{
        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString,0);//输入图像
        if(!srcImage.data )
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("请打开合适的图像"));
            return;
        }
        cv::Mat dstImage;//输出图像
        int num=showImg.getCurrentImageNum();//当前图像数目
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        cv::threshold(srcImage,dstImage,thresh,255,cv::THRESH_BINARY_INV);
        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                 tr("图像处理失败"),
                                 tr("操作过程出错！"));
    }
}

/**
* @brief  TRUNC单选按钮按下，显示说明，执行TRUNC;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_radioButton_TRUNC_clicked()
{
    double thresh=ui->truncDoubleSpinBox->value();
    ui->helpTextBrowser->clear();
    char temp[200];
    sprintf(temp,"数字框的值为阈值,其值为:%.2f\n\n",thresh);
    ui->helpTextBrowser->insertPlainText(temp);

    QFile txtFile("trunc.txt");
    if(!txtFile.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::information(this,
                                 tr("打开讲解文件失败"),
                                 tr("请重新安装本软件"));
        return;
    }
    //构建QTextStream以便读取文本
    QTextStream txtFileContent(&txtFile);
    //将应用程序的光标设置为等待状态
    QApplication::setOverrideCursor(Qt::WaitCursor);
    //将读取的所有文本设置到QTextEdit控件中显示出来
    ui->helpTextBrowser->insertPlainText(txtFileContent.readAll());
    //读取完成后，恢复光标状态
    QApplication::restoreOverrideCursor();

    ui->radioButton_TRUNC->setChecked(true);

    try{
        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString,0);//输入图像
        if(!srcImage.data )
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("请打开合适的图像"));
            return;
        }
        cv::Mat dstImage;//输出图像
        int num=showImg.getCurrentImageNum();//当前图像数目
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        cv::threshold(srcImage,dstImage,thresh,255,cv::THRESH_TRUNC);
        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                 tr("图像处理失败"),
                                 tr("操作过程出错！"));
    }
}

/**
* @brief  TRZERO单选按钮按下，显示说明，执行TRZERO;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_radioButton_TOZERO_clicked()
{
    double thresh=ui->tozeroDoubleSpinBox->value();
    ui->helpTextBrowser->clear();
    char temp[200];
    sprintf(temp,"数字框的值为阈值,其值为:%.2f\n\n",thresh);
    ui->helpTextBrowser->insertPlainText(temp);

    QFile txtFile("tozero.txt");
    if(!txtFile.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::information(this,
                                 tr("打开讲解文件失败"),
                                 tr("请重新安装本软件"));
        return;
    }
    //构建QTextStream以便读取文本
    QTextStream txtFileContent(&txtFile);
    //将应用程序的光标设置为等待状态
    QApplication::setOverrideCursor(Qt::WaitCursor);
    //将读取的所有文本设置到QTextEdit控件中显示出来
    ui->helpTextBrowser->insertPlainText(txtFileContent.readAll());
    //读取完成后，恢复光标状态
    QApplication::restoreOverrideCursor();

    ui->radioButton_TOZERO->setChecked(true);

    try{
        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString,0);//输入图像
        if(!srcImage.data )
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("请打开合适的图像"));
            return;
        }
        cv::Mat dstImage;//输出图像
        int num=showImg.getCurrentImageNum();//当前图像数目
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        cv::threshold(srcImage,dstImage,thresh,255,cv::THRESH_TOZERO);
        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                 tr("图像处理失败"),
                                 tr("操作过程出错！"));
    }
}

/**
* @brief  TRZERO_INV单选按钮按下，显示说明，执行TRZERO_INV;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_radioButton_TOZERO_INV_clicked()
{
    double thresh=ui->tozeroInvDoubleSpinBox->value();
    ui->helpTextBrowser->clear();
    char temp[200];
    sprintf(temp,"数字框的值为阈值,其值为:%.2f\n\n",thresh);
    ui->helpTextBrowser->insertPlainText(temp);

    QFile txtFile("tozeroinv.txt");
    if(!txtFile.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::information(this,
                                 tr("打开讲解文件失败"),
                                 tr("请重新安装本软件"));
        return;
    }
    //构建QTextStream以便读取文本
    QTextStream txtFileContent(&txtFile);
    //将应用程序的光标设置为等待状态
    QApplication::setOverrideCursor(Qt::WaitCursor);
    //将读取的所有文本设置到QTextEdit控件中显示出来
    ui->helpTextBrowser->insertPlainText(txtFileContent.readAll());
    //读取完成后，恢复光标状态
    QApplication::restoreOverrideCursor();

    ui->radioButton_TOZERO_INV->setChecked(true);

    try{
        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString,0);//输入图像
        if(!srcImage.data )
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("请打开合适的图像"));
            return;
        }
        cv::Mat dstImage;//输出图像
        int num=showImg.getCurrentImageNum();//当前图像数目
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        cv::threshold(srcImage,dstImage,thresh,255,cv::THRESH_TOZERO_INV);
        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                 tr("图像处理失败"),
                                 tr("操作过程出错！"));
    }
}

/**
* @brief  自适应二值化单选按钮按下，显示说明，执行自适应二值化;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_adaptiveRadioButton_clicked()
{
    int method;
    int type;
    int size;
    double C;
    char adaptiveMethod[2][30]={"ADAPTIVE_THRESH_MEAN_C","ADAPTIVE_THRESH_GUSSIAN_C"};
    char threshType[2][30]={"THRESH_BINARY","THRESH_BINARY_INV"};

    adaptive_set.getValue(method,type,size,C);

    ui->helpTextBrowser->clear();
    char temp[200];
    sprintf(temp,"设置对话框中的选项及它们的值依次为\n"
                 "自适应方法:%s\n"
                 "阈值方法:%s\n"
                 "块大小:%d\n"
                 "常数值:%.2f\n\n",
            adaptiveMethod[method], threshType[type],size,C);
    ui->helpTextBrowser->insertPlainText(temp);

    QFile txtFile("adaptive.txt");
    if(!txtFile.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::information(this,
                                 tr("打开讲解文件失败"),
                                 tr("请重新安装本软件"));
        return;
    }
    //构建QTextStream以便读取文本
    QTextStream txtFileContent(&txtFile);
    //将应用程序的光标设置为等待状态
    QApplication::setOverrideCursor(Qt::WaitCursor);
    //将读取的所有文本设置到QTextEdit控件中显示出来
    ui->helpTextBrowser->insertPlainText(txtFileContent.readAll());
    //读取完成后，恢复光标状态
    QApplication::restoreOverrideCursor();

    ui->adaptiveRadioButton->setChecked(true);//设置被选上

    try{
        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString,0);//输入图像
        if(!srcImage.data )
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("请打开合适的图像"));
            return;
        }
        cv::Mat dstImage;//输出图像

        int num=showImg.getCurrentImageNum();//当前图像数目
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        adaptiveThreshold(srcImage,dstImage,255,method,type,size,C);
        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                 tr("图像处理失败"),
                                 tr("操作过程出错！"));
    }
}

/**
* @brief  binary对应数字框数字改变;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_binaryDoubleSpinBox_valueChanged()
{
    on_radioButton_Binary_clicked();
}

/**
* @brief  binaryInv对应数字框数字改变;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_binaryInvDoubleSpinBox_valueChanged()
{
    on_radioButton_BinaryInv_clicked();
}

/**
* @brief  trunc对应数字框数字改变;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_truncDoubleSpinBox_valueChanged()
{
    on_radioButton_TRUNC_clicked();
}

/**
* @brief  tozero对应数字框数字改变;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_tozeroDoubleSpinBox_valueChanged()
{
    on_radioButton_TOZERO_clicked();
}

/**
* @brief  tozeroInv对应数字框数字改变;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_tozeroInvDoubleSpinBox_valueChanged()
{
    on_radioButton_TOZERO_INV_clicked();
}

/**
* @brief  自适应二值化对应设置按键按下;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_adaptiveButton_clicked()
{
    AdaptiveThreshold adaptivethreshold(this);
    adaptivethreshold.exec();
}
