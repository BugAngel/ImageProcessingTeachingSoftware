/**
  ******************************************************************************
  * @file    practical.cpp
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.22
  * @note    主窗口实践项目部分控件操作
  ******************************************************************************
  */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QMessageBox>
#include "file.h"
#include "showimage.h"
#include <QProcess>
#include <algorithm>
#include <vector>

typedef struct Example
{
    int id;
    std::vector<cv::Point> Contours;
    double Area;
}Example;

//由大到小排序
bool cmp(Example a,Example b)
{
    return a.Area>b.Area;
}

/**
* @brief  找最大面积轮廓的控件
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_maxContourCenterRadioButton_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("此功能实现过程为：\n"
                                         "首先读入图片，将其转换为灰度图后使用canny边缘检测，使用边缘图得到轮廓\n"
                                         "将得到的轮廓按面积大小由大到小排序，将面积最大的轮廓画出\n"
                                         "之后计算图像中心矩并输出\n\n");
    ui->maxContourCenterRadioButton->setChecked(true);

    cv::Mat grayImage;
    int g_nThresh = ui->maxContourCenterHorizontalSlider->value();
    cv::RNG g_rng(12345);
    cv::Mat g_cannyMat_output;
    std::vector<std::vector<cv::Point>> g_vContours;
    std::vector<cv::Vec4i> g_vHierarchy;

    std::vector<Example> example;
    Example temp;
    cv::Mat dstImage;//输出图像

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

        int num=showImg.getCurrentImageNum();//当前图像数目
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        cv::cvtColor(srcImage,grayImage,CV_RGB2GRAY);

        // 用Canny算子检测边缘
        cv::Canny( grayImage, g_cannyMat_output, g_nThresh, g_nThresh*2, 3 );

        // 寻找轮廓
        cv::findContours( g_cannyMat_output, g_vContours, g_vHierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );

        //对example数组赋值
        for (unsigned int i = 0; i < g_vContours.size(); i++)
        {
            temp.id=i;
            temp.Contours = g_vContours[i];
            temp.Area = cv::contourArea(g_vContours[i]);
            example.push_back(temp);
        }

        //对example数组排序
        sort(example.begin(), example.end(), cmp);

        // 计算矩
        cv::Moments mu = cv::moments( example[0].Contours, false );

        //  计算中心矩
        cv::Point2f mc = cv::Point2f( static_cast<float>(mu.m10/mu.m00), static_cast<float>(mu.m01/mu.m00 ));

        char s[200];
        sprintf(s,"面积最大轮廓的中心矩x坐标：%f  y坐标：%f\r\n", mc.x, mc.y);
        ui->helpTextBrowser->insertPlainText(s);

        dstImage = cv::Mat::zeros( g_cannyMat_output.size(), CV_8UC3 );
        cv::Scalar color = cv::Scalar( g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255) );//随机生成颜色值
        cv::drawContours( dstImage, g_vContours, example[0].id, color, 2, 8, g_vHierarchy, 0, cv::Point() );//绘制外层和内层轮廓

        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }
    catch(std::exception& e){
        QMessageBox::information(this,
                                 tr("打开图像失败"),
                                 tr("操作过程出错！"));
    }
}

/**
* @brief  找最大面积轮廓的阈值改变
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_maxContourCenterHorizontalSlider_valueChanged()
{
    on_maxContourCenterRadioButton_clicked();
}

/**
* @brief  用向量来做COSα=两向量之积/两向量模的乘积求两条线段夹角
* @param  线段3个点坐标pt1,pt2,pt0,最后一个参数为公共点
* @retval 线段夹角，单位为角度
* @author  BugAngel
* @attention
*/
double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0)
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    double angle_line = (dx1*dx2 + dy1*dy2) / sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);//余弦值
    return acos(angle_line) * 180 / 3.141592653;
}

/**
* @brief  采用多边形逼近检测，通过约束条件寻找多边形
* @param  srcImage 原图像
* @param  minarea，maxarea 检测多边形的最小/最大面积
* @param  minangle,maxangle 检测多边形边夹角范围，单位为角度
* @param  shape 多边形边数
* @retval 多边形序列
* @author  BugAngel
* @attention
*/
CvSeq* findSquares(cv::Mat srcImage, int minarea, int maxarea, int minangle, int maxangle,int shape)
{
    cv::Mat grayImage;
    cv::Mat cannyMat_output;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    int thresh = 100;

    double t;
    double s;

    cv::cvtColor(srcImage,grayImage,CV_RGB2GRAY);

    // 用Canny算子检测边缘
    cv::Canny( grayImage, cannyMat_output, thresh, thresh*2, 3 );

    // 寻找轮廓
    cv::findContours( cannyMat_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );

    //多边形逼近轮廓
    std::vector<std::vector<cv::Point>> contours_poly(contours.size());

    for(unsigned int i=0;i<contours.size();i++)
    {
        cv::approxPolyDP(contours[i], contours_poly[i], 3, true);//多边形逼近
        double tempArea=cv::contourArea(contours_poly[i]);
        //如果是凸多边形并且面积在范围内,并且是凸的
        if (contours_poly[i].size() == shape &&  tempArea > minarea  && tempArea < maxarea &&  cv::isContourConvex(contours_poly[i]))
        {
            s = 0;
            //判断每一条边
            for (int i = 2; i < shape + 1; i++)
            {
                t = fabs(angle((CvPoint*)cvGetSeqElem(result, i), (CvPoint*)cvGetSeqElem(result, i - 2), (CvPoint*)cvGetSeqElem(result, i - 1)));
                s = s > t ? s : t;
            }
            //这里的S为直角判定条件 单位为角度
            if (s > minangle && s < maxangle)
                for (int i = 0; i < shape; i++)
                    cvSeqPush(squares, (CvPoint*)cvGetSeqElem(result, i));
        }
        contours = contours->h_next;
    }

    return squares;
}

void MainWindow::on_regularPolygonRadioButton_clicked()
{

}

void MainWindow::on_digitalVerificationCodeRadioButton_clicked()
{

}

void MainWindow::on_faceDetectionRadioButton_clicked()
{

}
