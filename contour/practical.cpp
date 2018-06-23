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
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <QMessageBox>
#include "file.h"
#include "showimage.h"
#include <QProcess>
#include <algorithm>
#include <vector>
#include <QFile>
#include <QTextStream>
#include "imagetoascii.h"
#include "imagetoasciiset.h"
#include <string>
#include <fstream>

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
    int g_nThresh = ui->maxContourCenterHorizontalSlider->value();
    char Temp[200];
    sprintf(Temp,"滑动条表示边缘阈值,其值为:%d\n\n",g_nThresh);
    ui->helpTextBrowser->insertPlainText(Temp);

    QFile txtFile("maxcontourcenter.txt");
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

    ui->maxContourCenterRadioButton->setChecked(true);

    cv::Mat grayImage;
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
        //之所以使用排序是因为在实际项目中，最大的不一定是满足要求的，排序完了之后还要从大到小筛选，
        //这样写好，以后移植的时候方便

        // 计算矩
        cv::Moments mu = cv::moments( example[0].Contours, false );

        //  计算中心矩
        cv::Point2f mc = cv::Point2f( static_cast<float>(mu.m10/mu.m00), static_cast<float>(mu.m01/mu.m00 ));

        char s[200];
        sprintf(s,"面积最大轮廓的中心矩x坐标：%f  y坐标：%f\r\n", mc.x, mc.y);
        ui->helpTextBrowser->insertPlainText(s);

        dstImage=srcImage.clone();
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
* @brief  判断角度是否在范围内
* @param  angle为输入角度，rangeMin，rangeMax分别为范围的下限和上限
* @retval 在范围内返回true，不在返回false
* @author  BugAngel
* @attention
*/
bool angleRange(double angle,int rangeMin,int rangeMax)
{
    if(angle > rangeMin && angle < rangeMax)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
* @brief  寻找多边形单选按钮按下
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention 使用求内角和的方法找到多边形
*/
void MainWindow::on_searchPolygonRadioButton_clicked()
{
    ui->helpTextBrowser->clear();
    char shapeString[8][30]={"三角形","正三角形","四边形","矩形",
                            "五边形","正五边形","六边形","正六边形"};
    int shapeIndex = ui->searchPolygonComboBox->currentIndex();
    char Temp[200];
    sprintf(Temp,"当前选择检测形状为:%s\n\n",shapeString[shapeIndex]);
    ui->helpTextBrowser->insertPlainText(Temp);

    QFile txtFile("searchpolygon.txt");
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

    ui->searchPolygonRadioButton->setChecked(true);

    double minArea=1000;//最小面积
    double maxArea=120000;//最大面积
    unsigned int shape;//多边形边数
    cv::RNG g_rng(12345);
    cv::Mat grayImage;
    cv::Mat cannyMat_output;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    int thresh = 100;

    switch(shapeIndex)
    {
    case 0:
        shape=3;
        break;
    case 1:
        shape=13;//前面那个1表示正
        break;
    case 2:
        shape=4;
        break;
    case 3:
        shape=14;//前面那个1表示正
        break;
    case 4:
        shape=5;
        break;
    case 5:
        shape=15;//前面那个1表示正
        break;
    case 6:
        shape=6;
        break;
    case 7:
        shape=16;//前面那个1表示正
        break;
    }
    try
    {
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

        cv::Mat dstImage=srcImage.clone();

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
            if ((contours_poly[i].size() == shape || contours_poly[i].size() == (shape-10)) &&  tempArea > minArea  && tempArea < maxArea &&  cv::isContourConvex(contours_poly[i]))
            {
                int sumAngel=0;
                if(shape==3)
                {
                    double angel_1 = fabs(angle(contours_poly[i][0], contours_poly[i][1], contours_poly[i][2]));
                    double angel_2 = fabs(angle(contours_poly[i][0], contours_poly[i][2], contours_poly[i][1]));
                    double angel_3 = fabs(angle(contours_poly[i][1], contours_poly[i][2], contours_poly[i][0]));
                    sumAngel=angel_1+angel_2+angel_3;
                    if (angleRange(sumAngel,170,190))//判断内角和
                    {
                        cv::Scalar color = cv::Scalar( g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255) );//随机生成颜色值
                        cv::polylines(dstImage,contours_poly[i],true,color,5, CV_AA, 0);//画出多边形轮廓
                    }
                }
                else if(shape==4)
                {
                    double angel_1 = fabs(angle(contours_poly[i][1], contours_poly[i][3], contours_poly[i][0]));
                    double angel_2 = fabs(angle(contours_poly[i][0], contours_poly[i][2], contours_poly[i][1]));
                    double angel_3 = fabs(angle(contours_poly[i][1], contours_poly[i][3], contours_poly[i][2]));
                    double angel_4 = fabs(angle(contours_poly[i][2], contours_poly[i][0], contours_poly[i][3]));
                    sumAngel=angel_1+angel_2+angel_3+angel_4;
                    if (angleRange(sumAngel,350,370))//判断内角和
                    {
                        cv::Scalar color = cv::Scalar( g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255) );//随机生成颜色值
                        cv::polylines(dstImage,contours_poly[i],true,color,5, CV_AA, 0);//画出多边形轮廓
                    }
                }
                else if(shape==5)
                {
                    double angel_1 = fabs(angle(contours_poly[i][1], contours_poly[i][4], contours_poly[i][0]));
                    double angel_2 = fabs(angle(contours_poly[i][0], contours_poly[i][2], contours_poly[i][1]));
                    double angel_3 = fabs(angle(contours_poly[i][1], contours_poly[i][3], contours_poly[i][2]));
                    double angel_4 = fabs(angle(contours_poly[i][2], contours_poly[i][4], contours_poly[i][3]));
                    double angel_5 = fabs(angle(contours_poly[i][3], contours_poly[i][0], contours_poly[i][4]));
                    sumAngel=angel_1+angel_2+angel_3+angel_4+angel_5;
                    if (angleRange(sumAngel,530,550))//判断内角和
                    {
                        cv::Scalar color = cv::Scalar( g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255) );//随机生成颜色值
                        cv::polylines(dstImage,contours_poly[i],true,color,5, CV_AA, 0);//画出多边形轮廓
                    }
                }
                else if(shape==6)
                {
                    double angel_1 = fabs(angle(contours_poly[i][1], contours_poly[i][5], contours_poly[i][0]));
                    double angel_2 = fabs(angle(contours_poly[i][0], contours_poly[i][2], contours_poly[i][1]));
                    double angel_3 = fabs(angle(contours_poly[i][1], contours_poly[i][3], contours_poly[i][2]));
                    double angel_4 = fabs(angle(contours_poly[i][2], contours_poly[i][4], contours_poly[i][3]));
                    double angel_5 = fabs(angle(contours_poly[i][3], contours_poly[i][5], contours_poly[i][4]));
                    double angel_6 = fabs(angle(contours_poly[i][4], contours_poly[i][0], contours_poly[i][5]));
                    sumAngel=angel_1+angel_2+angel_3+angel_4+angel_5+angel_6;
                    if (angleRange(sumAngel,710,730))//判断内角和
                    {
                        cv::Scalar color = cv::Scalar( g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255) );//随机生成颜色值
                        cv::polylines(dstImage,contours_poly[i],true,color,5, CV_AA, 0);//画出多边形轮廓
                    }
                }
                else if(shape==13)
                {
                    double angel_1 = fabs(angle(contours_poly[i][0], contours_poly[i][1], contours_poly[i][2]));
                    double angel_2 = fabs(angle(contours_poly[i][0], contours_poly[i][2], contours_poly[i][1]));
                    double angel_3 = fabs(angle(contours_poly[i][1], contours_poly[i][2], contours_poly[i][0]));
                    if (angleRange(angel_1,50,70) && angleRange(angel_2,50,70) && angleRange(angel_3,50,70))//判断内角和
                    {
                        cv::Scalar color = cv::Scalar( g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255) );//随机生成颜色值
                        cv::polylines(dstImage,contours_poly[i],true,color,5, CV_AA, 0);//画出多边形轮廓
                    }
                }
                else if(shape==14)
                {
                    double angel_1 = fabs(angle(contours_poly[i][1], contours_poly[i][3], contours_poly[i][0]));
                    double angel_2 = fabs(angle(contours_poly[i][0], contours_poly[i][2], contours_poly[i][1]));
                    double angel_3 = fabs(angle(contours_poly[i][1], contours_poly[i][3], contours_poly[i][2]));
                    double angel_4 = fabs(angle(contours_poly[i][2], contours_poly[i][0], contours_poly[i][3]));
                    if (angleRange(angel_1,80,100)&&angleRange(angel_2,80,100)&&angleRange(angel_3,80,100)&&angleRange(angel_4,80,100))//判断内角和
                    {
                        cv::Scalar color = cv::Scalar( g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255) );//随机生成颜色值
                        cv::polylines(dstImage,contours_poly[i],true,color,5, CV_AA, 0);//画出多边形轮廓
                    }
                }
                else if(shape==15)
                {
                    double angel_1 = fabs(angle(contours_poly[i][1], contours_poly[i][4], contours_poly[i][0]));
                    double angel_2 = fabs(angle(contours_poly[i][0], contours_poly[i][2], contours_poly[i][1]));
                    double angel_3 = fabs(angle(contours_poly[i][1], contours_poly[i][3], contours_poly[i][2]));
                    double angel_4 = fabs(angle(contours_poly[i][2], contours_poly[i][4], contours_poly[i][3]));
                    double angel_5 = fabs(angle(contours_poly[i][3], contours_poly[i][0], contours_poly[i][4]));
                    if (angleRange(angel_1,98,118)&&angleRange(angel_2,98,118)&&angleRange(angel_3,98,118)&&angleRange(angel_4,98,118)&&angleRange(angel_5,98,118))//判断内角和
                    {
                        cv::Scalar color = cv::Scalar( g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255) );//随机生成颜色值
                        cv::polylines(dstImage,contours_poly[i],true,color,5, CV_AA, 0);//画出多边形轮廓
                    }
                }
                else if(shape==16)
                {
                    double angel_1 = fabs(angle(contours_poly[i][1], contours_poly[i][5], contours_poly[i][0]));
                    double angel_2 = fabs(angle(contours_poly[i][0], contours_poly[i][2], contours_poly[i][1]));
                    double angel_3 = fabs(angle(contours_poly[i][1], contours_poly[i][3], contours_poly[i][2]));
                    double angel_4 = fabs(angle(contours_poly[i][2], contours_poly[i][4], contours_poly[i][3]));
                    double angel_5 = fabs(angle(contours_poly[i][3], contours_poly[i][5], contours_poly[i][4]));
                    double angel_6 = fabs(angle(contours_poly[i][4], contours_poly[i][0], contours_poly[i][5]));
                    if (angleRange(angel_1,110,130)&&angleRange(angel_2,110,130)&&angleRange(angel_3,110,130)&&angleRange(angel_4,110,130)&&angleRange(angel_5,110,130)&&angleRange(angel_6,110,130))//判断内角和
                    {
                        cv::Scalar color = cv::Scalar( g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255) );//随机生成颜色值
                        cv::polylines(dstImage,contours_poly[i],true,color,5, CV_AA, 0);//画出多边形轮廓
                    }
                }
            }
        }
        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("图像处理失败"),
                                          tr("操作过程出错！"));
    }

}

/**
* @brief  改变寻找多边形边数
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_searchPolygonComboBox_currentIndexChanged()
{
    on_searchPolygonRadioButton_clicked();
}

/**
* @brief  人脸检测单选按钮按下
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention 使用CascadeClassifier完成,haarcascade_frontalface_default.xml在opencv的data文件夹下
*/
void MainWindow::on_faceDetectionRadioButton_clicked()
{
    ui->helpTextBrowser->clear();
    char faceString[2][30]={"单个人脸", "多个人脸"};
    int faceIndex = ui->faceDetectionComboBox->currentIndex();
    char Temp[200];
    sprintf(Temp,"当前选择检测人脸模式为:%s\n\n",faceString[faceIndex]);
    ui->helpTextBrowser->insertPlainText(Temp);

    QFile txtFile("facedetection.txt");
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

    ui->faceDetectionRadioButton->setChecked(true);

    cv::Mat grayImage;
    //加载Haar或LBP对象或人脸检测器
    cv::CascadeClassifier  faceDetector;
    std::string faceCascadeFilename = "haarcascade_frontalface_default.xml";

    //友好错误信息提示
    try{
        faceDetector.load(faceCascadeFilename);
    }catch (cv::Exception e){
        QMessageBox::information(this,
                                          tr("文件缺失"),
                                          tr("人脸检测器文件缺失！"));
        return;
    }

    if (faceDetector.empty())
    {
        QMessageBox::information(this,
                                          tr("脸部检测器不能加载"),
                                          tr("脸部检测器不能加载！"));
        return;
    }

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

    try
    {
        cv::Mat dstImage=srcImage.clone();
        cv::cvtColor(srcImage,grayImage,CV_RGB2GRAY);

        int flags;
        if(faceIndex==0)
        {
            flags = cv::CASCADE_FIND_BIGGEST_OBJECT|cv::CASCADE_DO_ROUGH_SEARCH;    //只检测脸最大的人
        }
        else
        {
            flags = cv::CASCADE_SCALE_IMAGE;  //检测多个人
        }
        cv::Size minFeatureSize(30, 30);
        float searchScaleFactor = 1.1f;
        int minNeighbors = 4;
        std::vector<cv::Rect> faces;
        faceDetector.detectMultiScale(grayImage, faces, searchScaleFactor, minNeighbors, flags, minFeatureSize);

        //画矩形框
        for(std::vector<cv::Rect>::const_iterator iter=faces.begin();iter!=faces.end();iter++)
        {
            cv::rectangle(dstImage,*iter,cv::Scalar(0,0,255),2,8); //画出脸部矩形
        }

        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                 tr("图像处理失败"),
                                 tr("操作过程出错！"));
    }
}

/**
* @brief  改变人脸检测模式
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_faceDetectionComboBox_currentIndexChanged()
{
    on_faceDetectionRadioButton_clicked();
}

/**
* @brief  图片转ASCII码单选按钮按下
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_asciiRadioButton_clicked()
{
    int row,col;
    char ascii_char[70] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
    float unit= (256.0 + 1)/69;
    cv::Mat resizeImage;
    std::string txt;
    char temp[200];

    imageToAscii_set.getValue(row,col);
    ui->helpTextBrowser->clear();
    sprintf(temp,"设置对话框中的选项及它们的值依次为\n"
                 "行:%d\n"
                 "列:%d\n\n",
            row,col);
    ui->helpTextBrowser->insertPlainText(temp);

    QFile txtFile("ascii.txt");
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

    ui->asciiRadioButton->setChecked(true);

    std::string fileString=file.getFileString().toLocal8Bit().toStdString();
    cv::Mat srcImage=cv::imread(fileString);//输入图像
    if(!srcImage.data )
    {
        QMessageBox::information(this,
                                 tr("打开图像失败"),
                                 tr("请打开合适的图像！"));
        return;
    }

    cv::cvtColor(srcImage,srcImage,CV_RGB2GRAY);
    cv::resize(srcImage,resizeImage,cv::Size(row,col));
    int rowNumber=resizeImage.rows;//行数
    int colNumber=resizeImage.cols;//列数

    for(int i=0;i<rowNumber;i++)//行循环
    {
        for(int j=0;j<colNumber;j++)//列循环
        {
            txt+=ascii_char[int((resizeImage.at<uchar>(i,j))/unit)];//灰度图像为uchar,RGB图像为Vec3b
        }
        txt+='\n';
    }

    //写入txt
    std::ofstream tempFile;
    tempFile.open("result.txt");
    if(tempFile.is_open())
    {
        tempFile<<txt;
    }
    else
    {
        QMessageBox::information(this,
                                 tr("打开文本文件失败"),
                                 tr("请关闭result.txt"));
        return;
    }
    tempFile.close();
}

/**
* @brief  图片转ASCII码设置按键按下
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_asciiPushButton_clicked()
{
    ImageToAscii imageToAscii(this);
    imageToAscii.exec();
}
