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
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("Canny边缘检测算子是John F.Canny于 1986 年开发出来的一个多级边缘检测算法。"
                                         "更为重要的是 Canny 创立了边缘检测计算理论（Computational theory ofedge detection），"
                                         "解释了这项技术是如何工作的。Canny边缘检测算法以Canny的名字命名，被很多人推崇为当今最优的边缘检测的算法。"
                                         "Canny 边缘检测的步骤:\n"
                                         "1.消除噪声。\n"
                                         "2.计算梯度幅值和方向。\n"
                                         "3.非极大值抑制。"
                                         "4.滞后阈值。\n"
                                         "tips：对于Canny函数的使用，推荐的高低阈值比在2:1到3:1之间。\n\n"
                                         "函数原型为： \n"
                                         "void Canny(InputArray image,OutputArray edges, double threshold1, double threshold2, "
                                         "int apertureSize=3,bool L2gradient=false ) \n\n"
                                         "第一个参数，InputArray类型的image，输入图像，即源图像，填Mat类的对象即可，且需为单通道8位图像。\n\n"
                                         "第二个参数，OutputArray类型的edges，输出的边缘图，需要和源图片有一样的尺寸和类型。\n\n"
                                         "第三个参数，double类型的threshold1，第一个滞后性阈值。\n\n"
                                         "第四个参数，double类型的threshold2，第二个滞后性阈值。\n\n"
                                         "第五个参数，int类型的apertureSize，表示应用Sobel算子的孔径大小，其有默认值3。\n\n"
                                         "第六个参数，bool类型的L2gradient，一个计算图像梯度幅值的标识，有默认值false。\n\n");
    ui->cannyRadioButton->setChecked(true);

    try{
        double threshold1;
        double threshold2;
        int apertureSize;

        canny_set.getValue(threshold1,threshold2,apertureSize);

        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString,0);//输入图像
        int num=showImg.getCurrentImageNum();//当前图像序号
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        cv::Canny(srcImage,srcImage,threshold1,threshold2,apertureSize);
        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),srcImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("打开图像失败"),
                                          tr("请打开合适的图像"));
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
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("Sobel算子是一个主要用作边缘检测的离散微分算子 (discrete differentiation operator)。 "
                                         "它结合了高斯平滑和微分求导，用来计算图像灰度函数的近似梯度。在图像的任何一点使用此算子，"
                                         "将会产生对应的梯度矢量或是其法矢量。\n\n"
                                         "函数原型为： \n"
                                         "void Sobel ( InputArray src, OutputArray dst, int ddepth, int dx,int dy,  "
                                          "int ksize=3, double scale=1,double delta=0,int borderType=BORDER_DEFAULT ); \n\n"
                                         "第一个参数，InputArray 类型的src，为输入图像，填Mat类型即可。\n\n"
                                         "第二个参数，OutputArray类型的dst，即目标图像，函数的输出参数，需要和源图片有一样的尺寸和类型。\n\n"
                                         "第三个参数，int类型的ddepth，输出图像的深度，支持如下src.depth()和ddepth的组合：\n"
                                         "若src.depth() = CV_8U, 取ddepth =-1/CV_16S/CV_32F/CV_64F\n"
                                         "若src.depth() = CV_16U/CV_16S, 取ddepth =-1/CV_32F/CV_64F\n"
                                         "若src.depth() = CV_32F, 取ddepth =-1/CV_32F/CV_64F\n"
                                         "若src.depth() = CV_64F, 取ddepth = -1/CV_64F\n\n"
                                         "第四个参数，int类型dx，x 方向上的差分阶数。\n\n"
                                         "第五个参数，int类型dy，y方向上的差分阶数。\n\n"
                                         "第六个参数，int类型ksize，有默认值3，表示Sobel核的大小;必须取1，3，5或7。\n\n"
                                         "第七个参数，double类型的scale，计算导数值时可选的缩放因子，默认值是1，"
                                         "表示默认情况下是没有应用缩放的。我们可以在文档中查阅getDerivKernels的相关介绍，来得到这个参数的更多信息。\n\n"
                                         "第八个参数，double类型的delta，表示在结果存入目标图（第二个参数dst）之前可选的delta值，有默认值0。\n\n"
                                         "第九个参数， int类型的borderType，我们的老朋友了（万年是最后一个参数），"
                                         "边界模式，默认值为BORDER_DEFAULT。这个参数可以在官方文档中borderInterpolate处得到更详细的信息。\n\n");
    ui->sobelRadioButton->setChecked(true);

    try{
        int dx;
        int dy;
        int ksize;
        double x_weight;

        cv::Mat dstImage;//输出图像
        cv::Mat grad_x, grad_y;
        cv::Mat abs_grad_x, abs_grad_y;
        int num=showImg.getCurrentImageNum();//当前图像序号
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        sobel_set.getValue(dx, dy, ksize, x_weight);

        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString);//输入图像

        cv::Sobel( srcImage, grad_x, -1, dx, 0, ksize, 1, 1, cv::BORDER_DEFAULT ); //x方向
        cv::convertScaleAbs( grad_x, abs_grad_x );

        cv::Sobel( srcImage, grad_y, -1, 0, dy, ksize, 1, 1, cv::BORDER_DEFAULT );   //y方向
        cv::convertScaleAbs( grad_y, abs_grad_y );

        cv::addWeighted( abs_grad_x, x_weight, abs_grad_y, 1-x_weight, 0, dstImage );   //合并

        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("打开图像失败"),
                                          tr("请打开合适的图像"));
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
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("数字为滤波器孔径尺寸\n"
                                         "Laplacian 算子是n维欧几里德空间中的一个二阶微分算子，定义为梯度grad（）的散度div（）。\n"
                                         "需要点破的是，由于 Laplacian使用了图像梯度，它内部的代码其实是调用了 Sobel 算子的。\n\n"
                                         "函数原型为： \n"
                                         "void Laplacian(InputArray src,OutputArray dst, int ddepth, int ksize=1, "
                                         "double scale=1, double delta=0, intborderType=BORDER_DEFAULT ); \n\n"
                                         "第一个参数，InputArray类型的image，输入图像，即源图像，填Mat类的对象即可，且需为单通道8位图像。\n\n"
                                         "第二个参数，OutputArray类型的edges，输出的边缘图，需要和源图片有一样的尺寸和通道数。\n\n"
                                         "第三个参数，int类型的ddept，目标图像的深度。\n\n"
                                         "第四个参数，int类型的ksize，用于计算二阶导数的滤波器的孔径尺寸，大小必须为正奇数，且有默认值1。\n\n"
                                         "第五个参数，double类型的scale，计算拉普拉斯值的时候可选的比例因子，有默认值1。\n\n"
                                         "第六个参数，double类型的delta，表示在结果存入目标图（第二个参数dst）之前可选的delta值，有默认值0。\n\n"
                                         "第七个参数， int类型的borderType，边界模式，默认值为BORDER_DEFAULT。这个参数可以在官方文档中borderInterpolate()处得到更详细的信息。\n\n");
    ui->laplacianRadioButton->setChecked(true);

    int ksize=ui->laplacianSpinBox->value();

    if(ksize%2==0){
        QMessageBox::information(this,
                                          tr("请输入合适的数字"),
                                          tr("滤波器的孔径尺寸大小必须为正奇数!"));
        return;
    }


    try{
        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString,0);//输入图像
        cv::Mat dstImage;//输出图像
        int num=showImg.getCurrentImageNum();//当前图像序号
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        cv::Laplacian( srcImage, dstImage, -1, ksize, 1, 0, cv::BORDER_DEFAULT );
        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                 tr("打开图像失败"),
                                 tr("请打开合适的图像"));
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
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("数字为X方向差分所占权重\n"
                                         "实践中一般直接称scharr为滤波器而不是算子，它在OPENCV中主要是配合Sobel算子的运算而存在的。\n"
                                         "Scharr(src, dst, ddepth, dx, dy, scale,delta, borderType)与"
                                         "Sobel(src, dst, ddepth, dx, dy, CV_SCHARR,scale, delta, borderType)完全等价\n\n"
                                         "函数原型为： \n"
                                         "void Scharr(InputArray src,OutputArray dst, int ddepth,int dx,int dy,"
                                         "double scale=1,double delta=0,intborderType=BORDER_DEFAULT )\n\n"
                                         "第一个参数，InputArray 类型的src，为输入图像，填Mat类型即可。\n\n"
                                         "第二个参数，OutputArray类型的dst，即目标图像，函数的输出参数，需要和源图片有一样的尺寸和类型。\n\n"
                                         "第三个参数，int类型的ddepth，输出图像的深度，支持如下src.depth()和ddepth的组合：\n"
                                         "若src.depth() = CV_8U, 取ddepth =-1/CV_16S/CV_32F/CV_64F\n"
                                         "若src.depth() = CV_16U/CV_16S, 取ddepth =-1/CV_32F/CV_64F\n"
                                         "若src.depth() = CV_32F, 取ddepth =-1/CV_32F/CV_64F\n"
                                         "若src.depth() = CV_64F, 取ddepth = -1/CV_64F\n\n"
                                         "第四个参数，int类型dx，x 方向上的差分阶数。\n\n"
                                         "第五个参数，int类型dy，y方向上的差分阶数。\n\n"
                                         "第六个参数，double类型的scale，计算导数值时可选的缩放因子，默认值是1，"
                                         "表示默认情况下是没有应用缩放的。我们可以在文档中查阅getDerivKernels的相关介绍，来得到这个参数的更多信息。\n\n"
                                         "第七个参数，double类型的delta，表示在结果存入目标图（第二个参数dst）之前可选的delta值，有默认值0。\n\n"
                                         "第八个参数， int类型的borderType，我们的老朋友了（万年是最后一个参数），"
                                         "边界模式，默认值为BORDER_DEFAULT。这个参数可以在官方文档中borderInterpolate处得到更详细的信息。\n\n");
    ui->scharrRadioButton->setChecked(true);

    try{
        double x_weight;

        cv::Mat dstImage;//输出图像
        cv::Mat grad_x, grad_y;
        cv::Mat abs_grad_x, abs_grad_y;
        int num=showImg.getCurrentImageNum();//当前图像序号
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        x_weight=ui->scharrDoubleSpinBox->value();

        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString);//输入图像

        cv::Scharr( srcImage, grad_x, -1, 1, 0, 1, 1, cv::BORDER_DEFAULT ); //x方向
        cv::convertScaleAbs( grad_x, abs_grad_x );

        cv::Scharr( srcImage, grad_y, -1, 0, 1, 1, 1, cv::BORDER_DEFAULT );   //y方向
        cv::convertScaleAbs( grad_y, abs_grad_y );

        cv::addWeighted( abs_grad_x, x_weight, abs_grad_y, 1-x_weight, 0, dstImage );   //合并

        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("打开图像失败"),
                                          tr("请打开合适的图像"));
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
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("一个轮廓一般对应一系列的点，也就是图像中的一条曲线，其表示方法可能根据不同的情况而有所不同，"
                                         "本例使用canny算子求得边缘，使用边缘得到轮廓，进而使用图形的矩求得轮廓的周长与面积,"
                                         "本例中canny阈值采用1:2\n"
                                         "opencv中，可以用findContours()函数从二值图像中查找轮廓\n\n"
                                         "函数原型为： \n"
                                         "void findContours(InputOutputArray image,OutputArrayOfArrays contours,  OutputArray hierarchy,"
                                         "int mode,int method, Point offset=Point())\n\n"
                                         "第一个参数，InputArray类型的img，输入图像，即源图像，填Mat类的对象即可,且需为8位单通道图像。"
                                         "此函数会在提取图像轮廓的同时修改图像的内容\n\n"
                                         "第二个参数，OutputArrayOfArrays类型的contours，检测到的轮廓、函数调用后的运算结果存在这里。"
                                         "每个轮廓存储为一个点向量，即用point类型的vector表示\n\n"
                                         "第三个参数，OutputArray类型的hierarchy,可选的输出向量，包含图像的拓扑信息。其作为轮廓数量的表示，包含了许多元素。"
                                         "每个轮廓contours[i]对应四个hierarchy元素hierarchy[i][0]~hierarchy[i][3]，"
                                         "分别表示后一个轮廓、前一个轮廓、父轮廓、内嵌轮廓的索引编号。如果没有对应项，对应的hierarchy[i]的值设置为负数\n\n"
                                         "第四个参数，int类型的mode，轮廓检索模式，一共四种\n"
                                         "第一种是CV_RETR_EXTERNAL,它表示只检测最外层轮廓。对所有轮廓，设置hierarchy[i][2]=hierarchy[i][3]=-1\n"
                                         "第二种是CV_RETR_LIST，提取所有轮廓，并且放置在list中。检测的轮廓不建立等级关系。\n"
                                         "第三种是CV_RETE_CCOMP,提取所有轮廓，并且将其组织为双层结构(顶层为连通域的外围边界，次层为孔的内层边界)\n"
                                         "第四种是CV_RETE_TREE,提取所有轮廓，并重新建立网状的轮廓结构\n\n"
                                         "第五个参数，int类型的method，为轮廓近似办法，一共四种\n"
                                         "第一种是CV_CHAIN_APPROX_NONE,获取每个轮廓的每个像素，相邻两个点的像素位置差不超过1\n"
                                         "第二种是CV_CHAIN_APPROX_SIMPLE，压缩水平方向，垂直方向，对角线方向的元素，只保留该方向的终点坐标，例如一个矩形轮廓只需四个点来保存轮廓信息\n"
                                         "第三种和第四种是CV_CHAIN_APPROX_TC89_L1和CV_CHAIN_APPROX_TC89_KCOS,使用Teh-Chinl链逼近算法中一个\n\n"
                                         "第六个参数，Point类型的offset，每个轮廓点的可选偏移量，有默认值Point()。对ROI图像中找出的轮廓，并要在整个图像中进行分析时，这个参数便可派上用场\n\n");
    ui->helpTextBrowser->insertPlainText("\t 输出内容: 轮廓的面积和长度\n");
    ui->contourRadioButton->setChecked(true);

    double thresh;
    int mode;
    int method;

    contour_set.getValue(thresh,mode,method);

    try{
        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat g_srcImage=cv::imread(fileString);//输入图像
        cv::Mat g_grayImage;
        cv::RNG g_rng(12345);
        cv::Mat g_cannyMat_output;
        std::vector<std::vector<cv::Point> > g_vContours;
        std::vector<cv::Vec4i> g_vHierarchy;
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
            sprintf(s," >轮廓[%d]的面积: %.2f , 长度: %.2f \n\n",
                    i, cv::contourArea(g_vContours[i]), cv::arcLength( g_vContours[i], true ));
            ui->helpTextBrowser->insertPlainText(s);
            cv::Scalar color = cv::Scalar( g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255) );
            cv::drawContours( drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, cv::Point() );
        }

        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),drawing);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,tr("打开图像失败"),tr("请打开合适的图像"));
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


