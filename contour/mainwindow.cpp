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

using namespace  cv;
using namespace std;

File file;
ShowImage showImage;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->helpTextBrowser->setFontPointSize(14);
    ui->helpTextBrowser->setFontFamily("楷体");

    ui->binaryButtonGroup->setId(ui->radioButton_Binary,0);//设置二值化按钮组的ID值
    ui->binaryButtonGroup->setId(ui->radioButton_BinaryInv,1);
    ui->binaryButtonGroup->setId(ui->radioButton_TRUNC,2);
    ui->binaryButtonGroup->setId(ui->radioButton_TRZERO,3);
    ui->binaryButtonGroup->setId(ui->radioButton_TRZERO_INV,4);
    ui->binaryButtonGroup->setId(ui->adaptiveRadioButton,5);

    ui->contourButtonGroup->setId(ui->radioButtonContour,0);//设置轮廓检测按钮组的ID值
    ui->contourButtonGroup->setId(ui->radioButtonConvexHull,1);
    ui->contourButtonGroup->setId(ui->radioButtonCircle,2);
    ui->contourButtonGroup->setId(ui->radioButtonRect,3);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpenImg_triggered()
{
    qDebug()<< "打开文件键有反应";

    file.setFileString(QFileDialog::getOpenFileName(this,tr("打开图像文件"),"/"));
    ui->lineEdit_FileName->setText(file.getFileString());

    QImage* img=new QImage;
    if(showImage.IgnoreAspectRatio(ui,img,file.getFileString(),SRCImage)==-1){
        QMessageBox::information(this,
                                          tr("打开图像失败"),
                                          tr("打开图像失败!"));
    }
    delete img;

}

void MainWindow::on_binaryButton_clicked()
{
    bool ok=true;
    int max=255;
    int thresh=ui->binaryThreshold->text().toDouble(&ok);
    if(ok==false){
        QMessageBox::information(this,
                                          tr("输入错误"),
                                          tr("请输入正确数字!"));
        return ;
    }  
    std::string threSholdString=file.getFileString().toStdString();
    Mat srcImage=imread(threSholdString,0);//输入图像
    Mat dstImage;//输出图像
    QImage* img=new QImage;//QT界面显示图像
    switch (ui->binaryButtonGroup->checkedId()) {
        case 0:
            threshold(srcImage,dstImage,thresh,max,THRESH_BINARY);
            imwrite("temp.jpg",dstImage);
            if(showImage.IgnoreAspectRatio(ui,img,"temp.jpg",DSTImage)==-1){
                QMessageBox::information(this,
                                                  tr("打开图像失败"),
                                                  tr("打开图像失败!"));
            }
            delete img;
            //qDebug() << QString::fromLocal8Bit("0");
            break;

        case 1:
            threshold(srcImage,dstImage,thresh,max,THRESH_BINARY_INV);
            imwrite("temp.jpg",dstImage);
            if(showImage.IgnoreAspectRatio(ui,img,"temp.jpg",DSTImage)==-1){
                QMessageBox::information(this,
                                                  tr("打开图像失败"),
                                                  tr("打开图像失败!"));
            }
            delete img;
            break;

        case 2:
            threshold(srcImage,dstImage,thresh,max,THRESH_TRUNC);
            imwrite("temp.jpg",dstImage);
            if(showImage.IgnoreAspectRatio(ui,img,"temp.jpg",DSTImage)==-1){
                QMessageBox::information(this,
                                                  tr("打开图像失败"),
                                                  tr("打开图像失败!"));
            }
            delete img;
            break;

        case 3:
            threshold(srcImage,dstImage,thresh,max,THRESH_TOZERO);
            imwrite("temp.jpg",dstImage);
            if(showImage.IgnoreAspectRatio(ui,img,"temp.jpg",DSTImage)==-1){
                QMessageBox::information(this,
                                                  tr("打开图像失败"),
                                                  tr("打开图像失败!"));
            }
            delete img;
            break;

        case 4:
            threshold(srcImage,dstImage,thresh,max,THRESH_TOZERO_INV);
            imwrite("temp.jpg",dstImage);
            if(showImage.IgnoreAspectRatio(ui,img,"temp.jpg",DSTImage)==-1){
                QMessageBox::information(this,
                                                  tr("打开图像失败"),
                                                  tr("打开图像失败!"));
            }
            delete img;
            break;

        case 5:
            int method,type,size;
            double C;
            adaptive_set.getAdaptiveSet(method,type,size,C);
            adaptiveThreshold(srcImage,dstImage,255,method,type,size,C);
            imwrite("temp.jpg",dstImage);
            if(showImage.IgnoreAspectRatio(ui,img,"temp.jpg",DSTImage)==-1){
                QMessageBox::information(this,
                                                  tr("打开图像失败"),
                                                  tr("打开图像失败!"));
            }
            delete img;
            break;
        default:
            break;
    }
}

void MainWindow::on_contourButton_clicked()
{
    bool ok=true;
    int thresh=ui->contourThreshold->text().toDouble(&ok);
    if(ok==false){
        QMessageBox::information(this,
                                          tr("输入错误"),
                                          tr("请输入正确数字!"));
        return ;
    }

    std::string threSholdString=file.getFileString().toStdString();
    Mat srcImage=imread(threSholdString,0);//输入图像
    Mat dstImage;//输出图像
    QImage* img=new QImage;//QT界面显示图像
    switch (ui->contourButtonGroup->checkedId()){
        case 0:
            vector<vector<Point>> g_vContours;
            vector<Vec4i> g_vHierarchy;
            Mat g_cannyMat_output;
            RNG g_rng(12345);
            // 用Canny算子检测边缘
            Canny( srcImage, g_cannyMat_output, thresh, thresh*2, 3 );

            // 寻找轮廓
            findContours( g_cannyMat_output, g_vContours, g_vHierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

            // 绘出轮廓
            Mat drawing = Mat::zeros( g_cannyMat_output.size(), CV_8UC3 );
            for( unsigned int i = 0; i< g_vContours.size(); i++ )
            {
                Scalar color = Scalar( g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255) );//任意值
                drawContours( drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point() );
            }

            imwrite("temp.jpg",drawing);
            if(showImage.IgnoreAspectRatio(ui,img,"temp.jpg",DSTImage)==-1){
                QMessageBox::information(this,
                                                  tr("打开图像失败"),
                                                  tr("打开图像失败!"));
            }
            delete img;
        break;

//        case 1:

//            break;
//        case 2:

//            break;
//        case 3:

//            break;
    }
}

void MainWindow::on_radioButton_Binary_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("当前点值大于阈值时，取最大值，否则设置为0 \n\n"
                                         "函数原型为：\n"
                                         "double threshold(InputArray src, OutputArray dst, double thresh, double maxval, THRESH_BINARY) ");
}

void MainWindow::on_radioButton_BinaryInv_clicked()
{
     ui->helpTextBrowser->clear();
     ui->helpTextBrowser->insertPlainText("当前点值大于阈值时，设置为0，否则取最大值 \n\n"
                                          "函数原型为： \n"
                                          "double threshold(InputArray src, OutputArray dst, double thresh, double maxval, THRESH_BINARY_INV) ");
}

void MainWindow::on_radioButton_TRUNC_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("当前点值大于阈值时，设置为阈值，否则不改变 \n\n"
                                         "函数原型为： \n"
                                         "double threshold(InputArray src, OutputArray dst, double thresh, double maxval,THRESH_TRUNC) ");
}

void MainWindow::on_radioButton_TRZERO_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("当前点值大于阈值时，不改变，否则设置为0 \n\n"
                                         "函数原型为： \n"
                                         "double threshold(InputArray src, OutputArray dst, double thresh, double maxval,THRESH_TOZERO) ");
}

void MainWindow::on_radioButton_TRZERO_INV_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("当前点值大于阈值时，不改变，否则设置为0 \n\n"
                                         "函数原型为： \n"
                                         "double threshold(InputArray src, OutputArray dst, double thresh, double maxval,THRESH_TOZERO_INV) ");
}

void MainWindow::on_adaptiveRadioButton_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("采用自适应阈值操作\n\n"
                                         "函数原型为： \n"
                                         "void adaptiveThreshold(InputArray src, OutputArray dst, double maxval, "
                                         "int adaptiveMethod, int thresholdType,int blockSize,double C)\n\n"
                                         "第四个参数为int类型的adaptiveMethod,用于指定要使用的自适应阈值算法，可取值为"
                                         "ADAPTIVE_THRESH_MEAN_C 或 ADAPTIVE_THRESH_GUSSIAN_C\n"
                                         "前者阈值T(x,y)为blockSize*blockSize邻域内(x,y)减去第七个参数C的平均值\n"
                                         "后者阈值T(x,y)为blockSize*blockSize邻域内(x,y)减去第七个参数C与高斯窗交叉相关的加权总和\n\n"
                                         "第五个参数为thresholdType，表示阈值类型，取值为THRESH_BINARY或THRESH_BINARY_INV\n"
                                         "这两者的说明见第一个和第二个单选框\n\n"
                                         "第六个参数为blockSize，用于计算阈值大小的一个像素的邻域尺寸，取值为3,5,7等\n\n"
                                         "第七个参数为C，为减去平均或加权平均值后的常数值，通常为正数，但少数情况下也可以为负数或0\n\n"
                                         );
}

void MainWindow::on_adaptiveButton_clicked()
{
    AdaptiveThreshold *adaptivethreshold=new AdaptiveThreshold;
    adaptivethreshold->show();
}
