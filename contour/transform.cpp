/**
  ******************************************************************************
  * @file    transform.cpp
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.20
  * @note    主窗口缩放旋转与对称部分控件操作
  ******************************************************************************
  */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QMessageBox>
#include "showimage.h"
#include "file.h"
#include <QFile>
#include <QTextStream>

/**
* @brief  图像变换操作
* @param  ui 窗口指针
* @retval NONE
* @author  BugAngel
* @attention 不管哪个控件状态改变，都执行这个函数出图
*/
void MainWindow::transform()
{
    cv::Mat src,dst_1,dst_2,dst_3,dst_4;//依次为输入图像，第一步，第二步，第三步，第四步的输出图像
    std::string fileString=file.getFileString().toLocal8Bit().toStdString();
    src=cv::imread(fileString);//输入图像
    if(!src.data )
    {
        QMessageBox::information(this,
                                 tr("打开图像失败"),
                                 tr("请打开合适的图像！"));
        return;
    }
    int num=showImg.getCurrentImageNum();//当前图像数目
    QString tempFileName=QString::number(num)+showImg.getImageSuffix();//输出图像文件名
    cv::Mat map_x, map_y;

    if(ui->upDownCheckBox->isChecked())//上下对称
    {
        //创建和原始图一样的效果图，x重映射图，y重映射图
        dst_1.create( src.size(), src.type() );
        map_x.create( src.size(), CV_32FC1 );
        map_y.create( src.size(), CV_32FC1 );

        //双层循环，遍历每一个像素点，改变map_x & map_y的值
        for( int j = 0; j < src.rows;j++)
        {
            for( int i = 0; i < src.cols;i++)
            {
                //改变map_x & map_y的值.
                map_x.at<float>(j,i) = static_cast<float>(i);
                map_y.at<float>(j,i) = static_cast<float>(src.rows - j);
            }
        }

        //进行重映射操作
        cv::remap( src, dst_1, map_x, map_y, CV_INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0,0, 0) );
    }
    else
    {
        dst_1=src;
    }

    if(ui->leftRightCheckBox->isChecked())//左右对称
    {
        //创建和原始图一样的效果图，x重映射图，y重映射图
        dst_2.create( dst_1.size(), dst_1.type() );
        map_x.create( dst_1.size(), CV_32FC1 );
        map_y.create( dst_1.size(), CV_32FC1 );

        //双层循环，遍历每一个像素点，改变map_x & map_y的值
        for( int j = 0; j < dst_1.rows;j++)
        {
            for( int i = 0; i < dst_1.cols;i++)
            {
                //改变map_x & map_y的值.
                map_x.at<float>(j,i) = static_cast<float>(dst_1.cols - i);
                map_y.at<float>(j,i) = static_cast<float>(j);
            }
        }

        //进行重映射操作
        cv::remap( dst_1, dst_2, map_x, map_y, CV_INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0,0, 0) );
    }
    else
    {
        dst_2=dst_1;
    }

    if(ui->resizeCheckBox->isChecked())//尺寸缩放
    {
        double value=ui->resizeDoubleSpinBox->value();
        if(value==1.0)
        {
            dst_3=dst_2;
        }
        else if(value<1.0)
        {
            cv::resize(dst_2,dst_3,cv::Size(),value,value,CV_INTER_AREA);
        }
        else//value>1.0
        {
            cv::resize(dst_2,dst_3,cv::Size(),value,value,CV_INTER_LINEAR);
        }
    }
    else
    {
        dst_3=dst_2;
    }

    if(ui->rotateCheckBox->isChecked())//缩放旋转
    {
        //定义一些Mat变量
        cv::Mat rotMat( 2, 3, CV_32FC1 );

        // 设置目标图像的大小和类型与源图像一致
        dst_4 = cv::Mat::zeros( dst_3.rows, dst_3.cols, dst_3.type() );

        //对图像进行旋转
        cv::Point center = cv::Point( dst_3.cols/2, dst_3.rows/2 );
        double angle = ui->rotateHorizontalSlider->value();
        double scale = ((double)ui->warpHorizontalSlider->value())/10;
        // 通过上面的旋转细节信息求得旋转矩阵
        rotMat = cv::getRotationMatrix2D( center, angle, scale );
        // 旋转已缩放后的图像
        cv::warpAffine( dst_3, dst_4, rotMat, dst_3.size() );
    }
    else
    {
        dst_4=dst_3;
    }

    cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dst_4);
    showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
}

/**
* @brief  上下对称打对勾
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_upDownCheckBox_stateChanged()
{
    if(ui->upDownCheckBox->isChecked())
    {
        ui->helpTextBrowser->clear();

        QFile txtFile("updown.txt");
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
    }

    try
    {
        transform();
    }catch(std::exception& e){
        QMessageBox::information(this,
                                 tr("图像处理失败"),
                                 tr("操作过程出错！"));
    }
}

/**
* @brief  左右对称打对勾
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_leftRightCheckBox_stateChanged()
{
    if(ui->leftRightCheckBox->isChecked())
    {
        ui->helpTextBrowser->clear();

        QFile txtFile("leftright.txt");
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
    }

    try
    {
        transform();
    }catch(std::exception& e){
        QMessageBox::information(this,
                                 tr("图像处理失败"),
                                 tr("操作过程出错！"));
    }
}

/**
* @brief  尺寸缩放打对勾
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_resizeCheckBox_stateChanged()
{    
    if(ui->resizeCheckBox->isChecked())
    {
        on_radioButtonArtWork_clicked();
        on_radioButtonArtWork_2_clicked();

        double resize=ui->resizeDoubleSpinBox->value();
        ui->helpTextBrowser->clear();
        char temp[200];
        sprintf(temp,"数字框的值为尺寸缩放倍数,其值为:%.2f\n\n",resize);
        ui->helpTextBrowser->insertPlainText(temp);

        QFile txtFile("resize.txt");
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
    }

    try
    {
        transform();
    }catch(std::exception& e){
        QMessageBox::information(this,
                                 tr("图像处理失败"),
                                 tr("操作过程出错！"));
    }
}

/**
* @brief  尺寸缩放对应数字框数字改变
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_resizeDoubleSpinBox_valueChanged()
{
    on_resizeCheckBox_stateChanged();
}

/**
* @brief  旋转缩放打对勾
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_rotateCheckBox_stateChanged()
{
    if(ui->rotateCheckBox->isChecked())
    {
        ui->helpTextBrowser->clear();
        int angle = ui->rotateHorizontalSlider->value();
        double scale = ((double)ui->warpHorizontalSlider->value())/10;
        char temp[200];
        sprintf(temp,"左边滑动条表示缩放倍数,其值为:%.1f\n"
                     "右边滑动条表示旋转角度,其值为:%d\n\n",
                scale,angle);
        ui->helpTextBrowser->insertPlainText(temp);

        QFile txtFile("rotate.txt");
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
    }

    try
    {
        transform();
    }catch(std::exception& e){
        QMessageBox::information(this,
                                 tr("图像处理失败"),
                                 tr("操作过程出错！"));
    }
}

/**
* @brief  旋转缩放对应缩放滑动条滑动
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_warpHorizontalSlider_valueChanged()
{
    on_rotateCheckBox_stateChanged();
}

/**
* @brief  旋转缩放对应旋转滑动条滑动
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_rotateHorizontalSlider_valueChanged()
{
    on_rotateCheckBox_stateChanged();
}
