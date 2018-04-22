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
#include <QtDebug>
#include <QFileDialog>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QTextCodec>
#include <QMessageBox>
#include "file.h"
#include "showimage.h"
#include "adaptiveset.h"
#include "adaptivethreshold.h"
#include <exception>

/**
* @brief  显示灰度图
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention 注意灰度按钮的ID是6
*/
void MainWindow::on_garyRadioButton_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("cvtColor()函数是openCV里的颜色空间转换函数，可以实现RGB颜色向HSV,HSI等颜色空间的转换，也可以转换为灰度图像，由src输入，dst输出\n\n"
                                         "函数原型为：\n"
                                         "void cvtColor(InputArray src, OutputArray dst, int code, int dstCn=0)"
                                         "第一个参数，InputArray类型的src，输入图像 \n\n"
                                         "第二个参数，OutputArray类型的dst，输出图像\n\n"
                                         "第三个参数，int类型的code，颜色空间转换的标识符\n"
                                         "转换关系与标识符的对应关系有\n"
                                         "RGB<->GRAY : CV_BGR2GRAY, CV_RGB2GRAY, CV_GRAY2BGR, CV_GRAY2RGB \n\n"
                                         "RGB<->CIE XYZ : CV_BGR2XYZ, CV_RGB2XYZ, CV_XYZ2BGR, CV_XYZ2RGB \n\n"
                                         "RGB<->YCrCb(YUV) JPEG (或 YCC) : CV_BGR2YCrCb, CV_RGB2YCrCb, CV_YCrCb2BGR, CV_YCrCb2RGB \n\n"
                                         "RGB<->HSV : CV_BGR2HSV, CV_RGB2HSV, CV_HSV2BGR, CV_HSV2RGB \n\n"
                                         "RGB<->HLS : CV_BGR2HLS, CV_RGB2HLS, CV_HLS2BGR, CV_HLS2RGB \n\n"
                                         "RGB<->CIE L*a*b* : CV_BGR2Lab, CV_RGB2Lab, CV_Lab2BGR, CV_Lab2RGB \n\n"
                                         "RGB<->CIE L*u*v* : CV_BGR2Luv, CV_RGB2Luv, CV_Luv2BGR, CV_Luv2RGB \n\n"
                                         "Bayer<->RGB : CV_BayerBG2BGR, CV_BayerGB2BGR, CV_BayerRG2BGR, CV_BayerGR2BGR, CV_BayerBG2RGB, "
                                         "CV_BayerGB2RGB, CV_BayerRG2RGB, CV_BayerGR2RGB \n\n"
                                         "第四个参数，int类型的dstCn，目标图像的通道数，若该参数为0，表示目标图像取源图像的通道数\n\n");
    ui->garyRadioButton->setChecked(true);

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
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("当前点值大于阈值时，取最大值，否则设置为0 ，由src输入，dst输出\n\n"
                                         "函数原型为：\n"
                                         "double threshold(InputArray src, OutputArray dst, double thresh, double maxval, THRESH_BINARY)"
                                         "第一个参数，InputArray类型的src，输入图像，即源图像，填单通道，8或32位浮点类型的Mat对象即可。 \n\n"
                                         "第二个参数，OutputArray类型的dst，函数调用后的运算结果存放在这里，即这个参数用于存放输出结果，\n\n"
                                         "且和第一个参数中的Mat变量有一样的尺寸和类型"
                                         "第三个参数，double类型的thresh,阈值的具体值\n\n"
                                         "第四个参数，double类型的maxval，阈值的最大值\n\n"
                                         "第五个参数，阈值类型\n\n");
    ui->radioButton_Binary->setChecked(true);

    double thresh=ui->binaryDoubleSpinBox->value();

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
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("当前点值大于阈值时，设置为0，否则取最大值 ，由src输入，dst输出\n\n"
                                         "函数原型为： \n"
                                         "double threshold(InputArray src, OutputArray dst, double thresh, double maxval, THRESH_BINARY_INV) "
                                         "第一个参数，InputArray类型的src，输入图像，即源图像，填单通道，8或32位浮点类型的Mat对象即可。 \n\n"
                                         "第二个参数，OutputArray类型的dst，函数调用后的运算结果存放在这里，即这个参数用于存放输出结果，\n\n"
                                         "且和第一个参数中的Mat变量有一样的尺寸和类型"
                                         "第三个参数，double类型的thresh,阈值的具体值\n\n"
                                         "第四个参数，double类型的maxval，阈值的最大值\n\n"
                                         "第五个参数，阈值类型\n\n");
    ui->radioButton_BinaryInv->setChecked(true);

    double thresh=ui->binaryInvDoubleSpinBox->value();

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
        showImg.showImage(ui,"temp.jpg",ShowImage::DSTImage,num);
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
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("当前点值大于阈值时，设置为阈值，否则不改变，由src输入，dst输出 \n\n"
                                         "函数原型为： \n"
                                         "double threshold(InputArray src, OutputArray dst, double thresh, double maxval,THRESH_TRUNC) "
                                         "第一个参数，InputArray类型的src，输入图像，即源图像，填单通道，8或32位浮点类型的Mat对象即可。 \n\n"
                                         "第二个参数，OutputArray类型的dst，函数调用后的运算结果存放在这里，即这个参数用于存放输出结果，\n\n"
                                         "且和第一个参数中的Mat变量有一样的尺寸和类型"
                                         "第三个参数，double类型的thresh,阈值的具体值\n\n"
                                         "第四个参数，double类型的maxval，阈值的最大值\n\n"
                                         "第五个参数，阈值类型\n\n");
    ui->radioButton_TRUNC->setChecked(true);

    double thresh=ui->truncDoubleSpinBox->value();

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
void MainWindow::on_radioButton_TRZERO_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("当前点值大于阈值时，不改变，否则设置为0 ，由src输入，dst输出\n\n"
                                         "函数原型为： \n"
                                         "double threshold(InputArray src, OutputArray dst, double thresh, double maxval,THRESH_TOZERO) "
                                         "第一个参数，InputArray类型的src，输入图像，即源图像，填单通道，8或32位浮点类型的Mat对象即可。 \n\n"
                                         "第二个参数，OutputArray类型的dst，函数调用后的运算结果存放在这里，即这个参数用于存放输出结果，\n\n"
                                         "且和第一个参数中的Mat变量有一样的尺寸和类型"
                                         "第三个参数，double类型的thresh,阈值的具体值\n\n"
                                         "第四个参数，double类型的maxval，阈值的最大值\n\n"
                                         "第五个参数，阈值类型\n\n");
    ui->radioButton_TRZERO->setChecked(true);

    double thresh=ui->tozeroDoubleSpinBox->value();

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
void MainWindow::on_radioButton_TRZERO_INV_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("当前点值大于阈值时，不改变，否则设置为0，由src输入，dst输出 \n\n"
                                         "函数原型为： \n"
                                         "double threshold(InputArray src, OutputArray dst, double thresh, double maxval,THRESH_TOZERO_INV) "
                                         "第一个参数，InputArray类型的src，输入图像，即源图像，填单通道，8或32位浮点类型的Mat对象即可。 \n\n"
                                         "第二个参数，OutputArray类型的dst，函数调用后的运算结果存放在这里，即这个参数用于存放输出结果，\n\n"
                                         "且和第一个参数中的Mat变量有一样的尺寸和类型"
                                         "第三个参数，double类型的thresh,阈值的具体值\n\n"
                                         "第四个参数，double类型的maxval，阈值的最大值\n\n"
                                         "第五个参数，阈值类型\n\n");
    ui->radioButton_TRZERO_INV->setChecked(true);

    int thresh=ui->tozeroInvDoubleSpinBox->value();

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
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("采用自适应阈值操作，，由src输入，dst输出\n\n"
                                         "函数原型为： \n"
                                         "void adaptiveThreshold(InputArray src, OutputArray dst, double maxval, "
                                         "int adaptiveMethod, int thresholdType,int blockSize,double C)\n\n"

                                         "第一个参数，InputArray类型的src，输入图像，即源图像，填单通道，8或32位浮点类型的Mat对象即可。 \n\n"
                                         "第二个参数，OutputArray类型的dst，函数调用后的运算结果存放在这里，即这个参数用于存放输出结果，\n\n"
                                         "第三个参数，double类型的maxval，阈值的最大值\n\n"
                                         "第四个参数为int类型的adaptiveMethod,用于指定要使用的自适应阈值算法，可取值为"
                                         "ADAPTIVE_THRESH_MEAN_C 或 ADAPTIVE_THRESH_GUSSIAN_C\n"
                                         "前者阈值T(x,y)为blockSize*blockSize邻域内(x,y)减去第七个参数C的平均值\n"
                                         "后者阈值T(x,y)为blockSize*blockSize邻域内(x,y)减去第七个参数C与高斯窗交叉相关的加权总和\n\n"
                                         "第五个参数为thresholdType，表示阈值类型，取值为THRESH_BINARY或THRESH_BINARY_INV\n"
                                         "这两者的说明见第一个和第二个单选框\n\n"
                                         "第六个参数为blockSize，用于计算阈值大小的一个像素的邻域尺寸，取值为3,5,7等\n\n"
                                         "第七个参数为C，为减去平均或加权平均值后的常数值，通常为正数，但少数情况下也可以为负数或0\n\n"
                                         );
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
        int method,type,size;
        double C;
        adaptive_set.getValue(method,type,size,C);
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
    on_radioButton_TRZERO_clicked();
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
    on_radioButton_TRZERO_INV_clicked();
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
