/**
  ******************************************************************************
  * @file    edge.cpp
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    主窗口轮廓检测部分控件操作
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

#include "contour.h"
#include "contourset.h"
#include "canny.h"
#include "cannyset.h"
#include "sobel.h"
#include "sobelset.h"

/**
* @brief  canny边缘检测单选按钮按下，显示说明，执行canny边缘检测;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_cannyRadioButton_clicked()
{   
    double threshold1;
    double threshold2;
    int apertureSize;

    canny_set.getValue(threshold1,threshold2,apertureSize);

    ui->helpTextBrowser->clear();
    char temp[200];
    sprintf(temp,"设置对话框中的选项及它们的值依次为\n"
                 "第一个滞后性阈值:%.2f\n"
                 "第一个滞后性阈值:%.2f\n"
                 "Sobel算子的孔径大小:%d\n\n",
            threshold1, threshold2,apertureSize);
    ui->helpTextBrowser->insertPlainText(temp);

    QFile txtFile("canny.txt");
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

    ui->cannyRadioButton->setChecked(true);

    try{
        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString,0);//输入图像
        if(!srcImage.data )
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("请打开合适的图像！"));
            return;
        }
        int num=showImg.getCurrentImageNum();//当前图像序号
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        cv::Canny(srcImage,srcImage,threshold1,threshold2,apertureSize);
        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),srcImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("图像处理失败"),
                                          tr("操作过程出错！"));
    }
}

/**
* @brief  sobel算子单选按钮按下，显示说明，执行sobel算子;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_sobelRadioButton_clicked()
{
    int dx;
    int dy;
    int ksize;
    double x_weight;

    sobel_set.getValue(dx, dy, ksize, x_weight);

    ui->helpTextBrowser->clear();
    char temp[200];
    sprintf(temp,"设置对话框中的选项及它们的值依次为\n"
                 "X方向差分阶数:%d\n"
                 "Y方向差分阶数:%d\n"
                 "Sobel核大小:%d\n"
                 "X方向差分结果所占权重:%.2f\n"
                 "Y方向差分结果所占权重:%.2f\n\n",
            dx, dy,ksize,x_weight,1-x_weight);
    ui->helpTextBrowser->insertPlainText(temp);

    QFile txtFile("sobel.txt");
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

    ui->sobelRadioButton->setChecked(true);

    try{
        cv::Mat dstImage;//输出图像
        cv::Mat grad_x, grad_y;
        cv::Mat abs_grad_x, abs_grad_y;
        int num=showImg.getCurrentImageNum();//当前图像序号
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString);//输入图像
        if(!srcImage.data )
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("请打开合适的图像！"));
            return;
        }

        cv::Sobel( srcImage, grad_x, -1, dx, 0, ksize, 1, 1, cv::BORDER_DEFAULT ); //x方向
        cv::convertScaleAbs( grad_x, abs_grad_x );

        cv::Sobel( srcImage, grad_y, -1, 0, dy, ksize, 1, 1, cv::BORDER_DEFAULT );   //y方向
        cv::convertScaleAbs( grad_y, abs_grad_y );

        cv::addWeighted( abs_grad_x, x_weight, abs_grad_y, 1-x_weight, 0, dstImage );   //合并

        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("图像处理失败"),
                                          tr("操作过程出错！"));
    }
}

/**
* @brief  laplacian算子单选按钮按下，显示说明，执行laplacian算子;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_laplacianRadioButton_clicked()
{
    int ksize=ui->laplacianSpinBox->value();
    ui->helpTextBrowser->clear();
    char temp[200];
    sprintf(temp,"数字框的值为滤波器孔径尺寸，其值为:%d\n\n",ksize);
    ui->helpTextBrowser->insertPlainText(temp);

    QFile txtFile("laplacian.txt");
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

    ui->laplacianRadioButton->setChecked(true);

    if(ksize%2==0){
        QMessageBox::information(this,
                                          tr("请输入合适的数字"),
                                          tr("滤波器的孔径尺寸大小必须为正奇数!"));
        return;
    }


    try{
        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString,0);//输入图像
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

        cv::Laplacian( srcImage, dstImage, -1, ksize, 1, 0, cv::BORDER_DEFAULT );
        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("图像处理失败"),
                                          tr("操作过程出错！"));
    }
}

/**
* @brief  scharr滤波器单选按钮按下，显示说明，执行scharr滤波器;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_scharrRadioButton_clicked()
{
    double x_weight=ui->scharrDoubleSpinBox->value();
    ui->helpTextBrowser->clear();
    char temp[200];
    sprintf(temp,"数字框的值为X方向差分所占权重,其值为:%.2f\n\n",x_weight);
    ui->helpTextBrowser->insertPlainText(temp);

    QFile txtFile("scharr.txt");
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

    ui->scharrRadioButton->setChecked(true);

    try{
        cv::Mat dstImage;//输出图像
        cv::Mat grad_x, grad_y;
        cv::Mat abs_grad_x, abs_grad_y;
        int num=showImg.getCurrentImageNum();//当前图像序号
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString);//输入图像
        if(!srcImage.data )
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("请打开合适的图像！"));
            return;
        }

        cv::Scharr( srcImage, grad_x, -1, 1, 0, 1, 1, cv::BORDER_DEFAULT ); //x方向
        cv::convertScaleAbs( grad_x, abs_grad_x );

        cv::Scharr( srcImage, grad_y, -1, 0, 1, 1, 1, cv::BORDER_DEFAULT );   //y方向
        cv::convertScaleAbs( grad_y, abs_grad_y );

        cv::addWeighted( abs_grad_x, x_weight, abs_grad_y, 1-x_weight, 0, dstImage );   //合并

        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("图像处理失败"),
                                          tr("操作过程出错！"));
    }
}

/**
* @brief  轮廓检测单选按钮按下，显示说明，执行轮廓检测;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_contourRadioButton_clicked()
{
    double thresh;
    int mode;
    int method;
    char searchMode[4][20]={"CV_RETR_EXTERNAL","CV_RETR_LIST","CV_RETE_CCOMP","CV_RETE_TREE"};
    char searchMethod[4][30]={"CV_CHAIN_APPROX_NONE","CV_CHAIN_APPROX_SIMPLE","CV_CHAIN_APPROX_TC89_L1","CV_CHAIN_APPROX_TC89_KCOS"};

    contour_set.getValue(thresh,mode,method);

    ui->helpTextBrowser->clear();
    char temp[200];
    sprintf(temp,"设置对话框中的选项及它们的值依次为\n"
                 "边缘查找阈值:%.2f\n"
                 "轮廓检索模式:%s\n"
                 "轮廓近似办法:%s\n\n",
            thresh, searchMode[mode],searchMethod[method]);
    ui->helpTextBrowser->insertPlainText(temp);

    QFile txtFile("contour.txt");
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

    ui->helpTextBrowser->insertPlainText("\t 轮廓的面积和长度\n");
    ui->contourRadioButton->setChecked(true);

    try{
        cv::Mat g_grayImage;
        cv::RNG g_rng(12345);
        cv::Mat g_cannyMat_output;
        std::vector<std::vector<cv::Point> > g_vContours;
        std::vector<cv::Vec4i> g_vHierarchy;
        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat g_srcImage=cv::imread(fileString);//输入图像
        if(!g_srcImage.data )
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("请打开合适的图像！"));
            return;
        }

        int num=showImg.getCurrentImageNum();//当前图像序号
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();
        cv::cvtColor( g_srcImage, g_grayImage, CV_BGR2GRAY );//转成灰度图

        // 使用Canndy检测边缘
        cv::Canny( g_grayImage, g_cannyMat_output, thresh, thresh*2, 3 );

        // 找到轮廓
        cv::findContours( g_cannyMat_output, g_vContours, g_vHierarchy, mode, method+1, cv::Point(0, 0) );

        // 绘制轮廓
        cv::Mat drawing = cv::Mat::zeros( g_cannyMat_output.size(), CV_8UC3 );
        for( unsigned int i = 0; i< g_vContours.size(); i++ )
        {
            cv::Scalar color = cv::Scalar( g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255) );//随机生成颜色值
            cv::drawContours( drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, cv::Point() );//绘制外层和内层轮廓
        }

        for(unsigned  int i = 0; i< g_vContours.size(); i++ )
        {
            char s[200];
            sprintf(s,"轮廓[%d]的面积: %.2f , 长度: %.2f \n\n",
                    i, cv::contourArea(g_vContours[i]), cv::arcLength( g_vContours[i], true ));
            ui->helpTextBrowser->insertPlainText(s);
            cv::Scalar color = cv::Scalar( g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255) );
            cv::drawContours( drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, cv::Point() );
        }

        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),drawing);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("图像处理失败"),
                                          tr("操作过程出错！"));
    }

}

/**
* @brief  canny边缘检测设置按键按下，显示设置界面;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_cannyButton_clicked()
{
    Canny canny(this);
    canny.exec();
}

/**
* @brief  sobel算子设置按键按下，显示设置界面;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_sobelPushButton_clicked()
{
    Sobel sobel(this);
    sobel.exec();
}

/**
* @brief  laplacian算子对应数字框数字改变，执行laplacian算子单选按钮按下的操作;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_laplacianSpinBox_valueChanged()
{
    on_laplacianRadioButton_clicked();
}

/**
* @brief  scharr滤波器对应数字框数字改变，执行scharr滤波器单选按钮按下的操作;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_scharrDoubleSpinBox_valueChanged()
{
    on_scharrRadioButton_clicked();
}

/**
* @brief  轮廓检测设置按键按下，显示设置界面;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_contourButton_clicked()
{
    Contour contour(this);
    contour.exec();
}


