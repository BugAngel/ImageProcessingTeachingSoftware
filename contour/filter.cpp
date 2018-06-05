/**
  ******************************************************************************
  * @file    filter.cpp
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    主窗口线性与非线性滤波部分控件操作
  ******************************************************************************
  */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "file.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QMessageBox>
#include "showimage.h"
#include <QFile>
#include <QTextStream>

#include "boxfilter.h"
#include "boxfilterset.h"
#include "blur.h"
#include "blurset.h"
#include "gaussianblur.h"
#include "gaussianblurset.h"
#include "bilateralfilter.h"
#include "bilateralfilterset.h"

/**
* @brief  方框滤波单选按钮按下，显示说明，执行方框滤波;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_boxFilterRadioButton_clicked()
{
    int width;
    int heigth;
    boxfilter_set.getValue(width,heigth);

    ui->helpTextBrowser->clear();
    char temp[200];
    sprintf(temp,"设置对话框中的选项及它们的值依次为\n"
                 "像素宽度:%d\n"
                 "像素高度:%d\n\n",
            width,heigth);
    ui->helpTextBrowser->insertPlainText(temp);

    QFile txtFile("boxfilter.txt");
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

    ui->boxFilterRadioButton->setChecked(true);

    try{
        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString);//输入图像
        if(!srcImage.data )
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("请打开合适的图像！"));
            return;
        }
        cv::Mat dstImage;//输出图像
        int num=showImg.getCurrentImageNum();//当前图像序号
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        cv::boxFilter(srcImage, dstImage, -1,cv::Size(heigth, width),cv::Point(-1,-1),false);
        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("图像处理失败"),
                                          tr("操作过程出错！"));
    }

}

/**
* @brief  均值滤波单选按钮按下，显示说明，执行均值滤波;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_blurRadioButton_clicked()
{
    int width;
    int heigth;
    blur_set.getValue(width,heigth);

    ui->helpTextBrowser->clear();
    char temp[200];
    sprintf(temp,"设置对话框中的选项及它们的值依次为\n"
                 "像素宽度:%d\n"
                 "像素高度:%d\n\n",
            width,heigth);
    ui->helpTextBrowser->insertPlainText(temp);

    QFile txtFile("blur.txt");
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

    ui->blurRadioButton->setChecked(true);

    try{
        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString);//输入图像
        if(!srcImage.data )
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("请打开合适的图像！"));
            return;
        }
        cv::Mat dstImage;//输出图像
        int num=showImg.getCurrentImageNum();//当前图像序号
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        cv::blur(srcImage, dstImage, cv::Size(heigth,width ));
        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("图像处理失败"),
                                          tr("操作过程出错！"));
    }

}

/**
* @brief  高斯滤波单选按钮按下，显示说明，执行高斯滤波;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_gaussianBlurRadioButton_clicked()
{
    int width;
    int height;
    double sigmaX;
    double sigmaY;
    gaussianblur_set.getValue(width, height, sigmaX, sigmaY);

    ui->helpTextBrowser->clear();
    char temp[200];
    sprintf(temp,"设置对话框中的选项及它们的值依次为\n"
                 "像素宽度:%d\n"
                 "像素高度:%d\n"
                 "sigmaX:%.2f\n"
                 "sigmaY:%.2f\n\n",
            width,height,sigmaX,sigmaY);
    ui->helpTextBrowser->insertPlainText(temp);

    QFile txtFile("gaussianblur.txt");
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

    ui->gaussianBlurRadioButton->setChecked(true);

    try{
        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString);//输入图像
        if(!srcImage.data )
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("请打开合适的图像！"));
            return;
        }
        cv::Mat dstImage;//输出图像
        int num=showImg.getCurrentImageNum();//当前图像序号
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        cv::GaussianBlur(srcImage, dstImage, cv::Size(height, width),sigmaX,sigmaY);
        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("图像处理失败"),
                                          tr("操作过程出错！"));
    }
}

/**
* @brief  中值滤波单选按钮按下，显示说明，执行中值滤波;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_medianFilterRadioButton_clicked()
{
    int ksize=ui->medianFilterSpinBox->value();
    ui->helpTextBrowser->clear();
    char temp[200];
    sprintf(temp,"数字框的值为孔径的线性尺寸,其值为:%d\n\n",ksize);
    ui->helpTextBrowser->insertPlainText(temp);

    QFile txtFile("medianblur.txt");
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

    ui->medianFilterRadioButton->setChecked(true);

    if(ksize<3 || ksize%2==0){
        QMessageBox::information(this,
                                          tr("输入数据错误"),
                                          tr("这个参数必须是大于1的奇数!"));
        return;
    }
    try{
        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString);//输入图像
        if(!srcImage.data )
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("请打开合适的图像！"));
            return;
        }
        cv::Mat dstImage;//输出图像
        int num=showImg.getCurrentImageNum();//当前图像序号
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        cv::medianBlur(srcImage, dstImage, ksize);
        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("图像处理失败"),
                                          tr("操作过程出错！"));
    }
}

/**
* @brief  双边滤波单选按钮按下，显示说明，执行双边滤波;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_bilateralFilterRadioButton_clicked()
{
    int d;
    double sigmaColor;
    double sigmaSpace;
    bilateralfilter_set.getValue(d,sigmaColor,sigmaSpace);

    ui->helpTextBrowser->clear();
    char temp[200];
    sprintf(temp,"设置对话框中的选项及它们的值依次为\n"
                 "像素邻域的直径:%d\n"
                 "颜色空间滤波器的sigma值:%.2f\n"
                 "坐标空间滤波器的sigma值:%.2f\n\n",
            d,sigmaColor,sigmaSpace);
    ui->helpTextBrowser->insertPlainText(temp);

    QFile txtFile("bilateralfilter.txt");
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

    ui->bilateralFilterRadioButton->setChecked(true);

    try{
        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString);//输入图像
        if(!srcImage.data )
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("请打开合适的图像！"));
            return;
        }
        cv::Mat dstImage;//输出图像
        int num=showImg.getCurrentImageNum();//当前图像序号
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        cv::bilateralFilter( srcImage, dstImage, d, sigmaColor, sigmaSpace );

        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("图像处理失败"),
                                          tr("操作过程出错！"));
    }
}

/**
* @brief  方框滤波设置按键按下，显示设置界面;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_boxFilterButton_clicked()
{
    BoxFilter boxfilter(this);
    boxfilter.exec();
}

/**
* @brief  均值滤波设置按键按下，显示设置界面;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_blurButton_clicked()
{
    Blur blur(this);
    blur.exec();
}

/**
* @brief  高斯滤波设置按键按下，显示设置界面;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_gaussianBlurButton_clicked()
{
    GaussianBlur gaussianblur(this);
    gaussianblur.exec();
}

/**
* @brief  双边滤波设置按键按下，显示设置界面;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_bilateralFilterButton_clicked()
{
    BilateralFilter bilateralfilter(this);
    bilateralfilter.exec();
}

/**
* @brief  中值滤波对应数字框数字改变，执行中值滤波单选按钮按下的操作;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_medianFilterSpinBox_valueChanged()
{
    on_medianFilterRadioButton_clicked();
}
