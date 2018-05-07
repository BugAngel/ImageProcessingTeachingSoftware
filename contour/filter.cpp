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
#include <QInputDialog>

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

    ui->helpTextBrowser->insertPlainText("以下为讲解部分:\n"
                                         "使用方框滤波来处理一张图片，由src输入，dst输出\n\n"
                                         "函数原型为： \n"
                                         "void boxFilter(InputArray src, OutputArray dst, int ddepth, "
                                         "Size ksize, Point anchor=Point(-1,-1), boolnormalize=true, int borderType=BORDER_DEFAULT)\n\n"
                                         "第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可。该函数对通道是独立处理的，"
                                         "且可以处理任意通道数的图片，但需要注意，待处理的图片深度应该为CV_8U, CV_16U, CV_16S, CV_32F 以及 CV_64F之一。\n\n"
                                         "第二个参数，OutputArray类型的dst，即目标图像，需要和源图片有一样的尺寸和类型。\n\n"
                                         "第三个参数，int类型的ddepth，输出图像的深度，-1代表使用原图深度，即src.depth()。\n\n"
                                         "第四个参数，Size类型（对Size类型稍后有讲解）的ksize，内核的大小。"
                                         "一般这样写Size( w,h )来表示内核的大小( 其中，w 为像素宽度， h为像素高度)。Size（3,3）就表示3x3的核大小，Size（5,5）就表示5x5的核大小\n\n"
                                         "第五个参数，Point类型的anchor，表示锚点（即被平滑的那个点），注意他有默认值Point(-1,-1)。"
                                         "如果这个点坐标是负值的话，就表示取核的中心为锚点，所以默认值Point(-1,-1)表示这个锚点在核的中心。\n\n"
                                         "第六个参数，bool类型的normalize，默认值为true，一个标识符，表示内核是否被其区域归一化（normalized）了。\n\n"
                                         "第七个参数，int类型的borderType，用于推断图像外部像素的某种边界模式。有默认值BORDER_DEFAULT，我们一般不去管它。");
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

        cv::boxFilter(srcImage, dstImage, -1,cv::Size(width, heigth));
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

    ui->helpTextBrowser->insertPlainText("以下为讲解部分:\n"
                                         "使用均值滤波来处理一张图片\n\n"
                                         "函数原型为： \n"
                                         "void blur(InputArray src, OutputArraydst, Size ksize, Point anchor=Point(-1,-1), "
                                         "int borderType=BORDER_DEFAULT )  \n\n"
                                         "第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可。该函数对通道是独立处理的，且可以处理任意通道数的图片，"
                                         "但需要注意，待处理的图片深度应该为CV_8U, CV_16U, CV_16S, CV_32F 以及 CV_64F之一。\n\n"
                                         "第二个参数，OutputArray类型的dst，即目标图像，需要和源图片有一样的尺寸和类型。"
                                         "如可以用Mat::Clone，以源图片为模板，来初始化得到如假包换的目标图。\n\n"
                                         "第三个参数，Size类型（对Size类型稍后有讲解）的ksize，内核的大小。"
                                         "一般这样写Size( w,h )来表示内核的大小( 其中，w 为像素宽度， h为像素高度)。Size（3,3）就表示3x3的核大小，Size（5,5）就表示5x5的核大小\n\n"
                                         "第四个参数，Point类型的anchor，表示锚点（即被平滑的那个点），注意他有默认值Point(-1,-1)。"
                                         "如果这个点坐标是负值的话，就表示取核的中心为锚点，所以默认值Point(-1,-1)表示这个锚点在核的中心。\n\n"
                                         "第五个参数，int类型的borderType，用于推断图像外部像素的某种边界模式。有默认值BORDER_DEFAULT，我们一般不去管它。");
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

        cv::blur(srcImage, dstImage, cv::Size(width, heigth));
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

    ui->helpTextBrowser->insertPlainText("以下为讲解部分:\n"
                                         "使用高斯滤波来处理一张图片\n\n"
                                         "函数原型为： \n"
                                         "void GaussianBlur(InputArray src,OutputArray dst, Size ksize, double sigmaX, "
                                         "double sigmaY=0, intborderType=BORDER_DEFAULT ) \n\n"
                                         "第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可。"
                                         "它可以是单独的任意通道数的图片，但需要注意，图片深度应该为CV_8U,CV_16U, CV_16S, CV_32F 以及 CV_64F之一。\n\n"
                                         "第二个参数，OutputArray类型的dst，即目标图像，需要和源图片有一样的尺寸和类型。"
                                         "比如可以用Mat::Clone，以源图片为模板，来初始化得到如假包换的目标图。\n\n"
                                         "第三个参数，Size类型的ksize高斯内核的大小。其中ksize.width和ksize.height可以不同，但他们都必须为正数和奇数。"
                                         "或者，它们可以是零的，它们都是由sigma计算而来。\n\n"
                                         "第四个参数，double类型的sigmaX，表示高斯核函数在X方向的的标准偏差。\n\n"
                                         "第五个参数，double类型的sigmaY，表示高斯核函数在Y方向的的标准偏差。"
                                         "若sigmaY为零，就将它设为sigmaX，如果sigmaX和sigmaY都是0，那么就由ksize.width和ksize.height计算出来。"
                                         "为了结果的正确性着想，最好是把第三个参数Size，第四个参数sigmaX和第五个参数sigmaY全部指定到。\n\n"
                                         "第六个参数，int类型的borderType，用于推断图像外部像素的某种边界模式。有默认值BORDER_DEFAULT，我们一般不去管它。\n\n");
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

        cv::GaussianBlur(srcImage, dstImage, cv::Size(width, height),sigmaX,sigmaY);
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

    ui->helpTextBrowser->insertPlainText("以下为讲解部分:\n"
                                         "使用中值滤波来处理一张图片\n\n"
                                         "函数原型为： \n"
                                         "void medianBlur(InputArray src,OutputArray dst, int ksize)\n\n"
                                         "第一个参数，InputArray类型的src，函数的输入参数，填1、3或者4通道的Mat类型的图像；"
                                         "当ksize为3或者5的时候，图像深度需为CV_8U，CV_16U，或CV_32F其中之一，而对于较大孔径尺寸的图片，它只能是CV_8U。\n\n"
                                         "第二个参数，OutputArray类型的dst，即目标图像，函数的输出参数，需要和源图片有一样的尺寸和类型。"
                                         "我们可以用Mat::Clone，以源图片为模板，来初始化得到如假包换的目标图。\n\n"
                                         "第三个参数，int类型的ksize，孔径的线性尺寸（aperture linear size），"
                                         "注意这个参数必须是大于1的奇数，比如：3，5，7，9 ...");
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

    ui->helpTextBrowser->insertPlainText("以下为讲解部分:\n"
                                         "使用双边滤波来处理一张图片\n\n"
                                         "这个算法有点卡，用起来要注意\n\n"
                                         "函数原型为：\n"
                                         "void bilateralFilter(InputArray src, OutputArraydst, int d, double sigmaColor, double sigmaSpace, "
                                         "int borderType=BORDER_DEFAULT)  \n\n"
                                         "第一个参数，InputArray类型的src，输入图像，即源图像，需要为8位或者浮点型单通道、三通道的图像。\n\n"
                                         "第二个参数，OutputArray类型的dst，即目标图像，需要和源图片有一样的尺寸和类型。\n\n"
                                         "第三个参数，int类型的d，表示在过滤过程中每个像素邻域的直径。如果这个值我们设其为非正数，那么OpenCV会从第五个参数sigmaSpace来计算出它来。\n\n"
                                         "第四个参数，double类型的sigmaColor，颜色空间滤波器的sigma值。"
                                         "这个参数的值越大，就表明该像素邻域内有更宽广的颜色会被混合到一起，产生较大的半相等颜色区域。\n\n"
                                         "第五个参数，double类型的sigmaSpace坐标空间中滤波器的sigma值，坐标空间的标注方差。"
                                         "他的数值越大，意味着越远的像素会相互影响，从而使更大的区域足够相似的颜色获取相同的颜色。"
                                         "当d>0，d指定了邻域大小且与sigmaSpace无关。否则，d正比于sigmaSpace。\n\n"
                                         "第六个参数，int类型的borderType，用于推断图像外部像素的某种边界模式。注意它有默认值BORDER_DEFAULT。");
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
