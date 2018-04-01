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
    ui->helpTextBrowser->insertPlainText("\t 输出内容: 面积和轮廓长度\n");
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

        cv::cvtColor( g_srcImage, g_grayImage, CV_BGR2GRAY );//转成灰度图

        // 使用Canndy检测边缘
        cv::Canny( g_grayImage, g_cannyMat_output, thresh, thresh*2, 3 );

        // 找到轮廓
        cv::findContours( g_cannyMat_output, g_vContours, g_vHierarchy, mode, method, cv::Point(0, 0) );

        // 计算矩
        std::vector<cv::Moments> mu(g_vContours.size() );
        for(unsigned int i = 0; i < g_vContours.size(); i++ )
        { mu[i] = cv::moments( g_vContours[i], false ); }

        //  计算中心矩
        std::vector<cv::Point2f> mc( g_vContours.size() );
        for( unsigned int i = 0; i < g_vContours.size(); i++ )
        { mc[i] = cv::Point2f( static_cast<float>(mu[i].m10/mu[i].m00), static_cast<float>(mu[i].m01/mu[i].m00 )); }

        // 绘制轮廓
        cv::Mat drawing = cv::Mat::zeros( g_cannyMat_output.size(), CV_8UC3 );
        for( unsigned int i = 0; i< g_vContours.size(); i++ )
        {
            cv::Scalar color = cv::Scalar( g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255) );//随机生成颜色值
            cv::drawContours( drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, cv::Point() );//绘制外层和内层轮廓
            cv::circle( drawing, mc[i], 4, color, -1, 8, 0 );;//绘制圆
        }

        // 通过m00计算轮廓面积并且和OpenCV函数比较
        for(unsigned  int i = 0; i< g_vContours.size(); i++ )
        {
            char s[200];
            sprintf(s," >通过m00计算出轮廓[%d]的面积: (M_00) = %.2f \n OpenCV函数计算出的面积=%.2f , 长度: %.2f \n\n",
                    i, mu[i].m00, cv::contourArea(g_vContours[i]), cv::arcLength( g_vContours[i], true ));
            ui->helpTextBrowser->insertPlainText(s);
            cv::Scalar color = cv::Scalar( g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255) );
            cv::drawContours( drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, cv::Point() );
            cv::circle( drawing, mc[i], 4, color, -1, 8, 0 );
        }

        cv::imwrite("temp.jpg",drawing);
        showImg.showImage(ui,"temp.jpg",ShowImage::DSTImage);
    }catch(std::exception& e){
        QMessageBox::information(this,tr("打开图像失败"),tr(e.what()));
    }

}

void MainWindow::on_contourButton_clicked()
{
    Contour contour(this);
    contour.exec();
}
