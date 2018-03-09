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

    ui->contourButtonGroup->setId(ui->contourRadioButton,0);//设置轮廓检测按钮组的ID值
    ui->contourButtonGroup->setId(ui->convexHullRadioButton,1);
    ui->contourButtonGroup->setId(ui->circleRadioButton,2);
    ui->contourButtonGroup->setId(ui->rectRadioButton,3);

    ui->ImageButtonGroup->setId(ui->radioButtonIgnoreAspectRatio,0);//设置图像显示方式按钮组的ID值
    ui->ImageButtonGroup->setId(ui->radioButtonKeepAspectRatio,1);
    ui->ImageButtonGroup->setId(ui->radioButtonArtWork,2);
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
    if(showImg.showImage(ui,img,file.getFileString(),SRCImage)==-1){
        QMessageBox::information(this,
                                          tr("打开图像失败"),
                                          tr("打开图像失败!"));
    }
    delete img;

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

    std::string threSholdString=file.getFileString().toLocal8Bit().toStdString();
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
            if(showImg.showImage(ui,img,"temp.jpg",DSTImage)==-1){
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
    ui->helpTextBrowser->insertPlainText("当前点值大于阈值时，取最大值，否则设置为0 ，由src输入，dst输出\n\n"
                                         "函数原型为：\n"
                                         "double threshold(InputArray src, OutputArray dst, double thresh, double maxval, THRESH_BINARY)"
                                         "第一个参数，InputArray类型的src，输入图像，即源图像，填单通道，8或32位浮点类型的Mat对象即可。 \n\n"
                                         "第二个参数，InputArray类型的dst，函数调用后的运算结果存放在这里，即这个参数用于存放输出结果，\n\n"
                                         "且和第一个参数中的Mat变量有一样的尺寸和类型"
                                         "第三个参数，double类型的thresh,阈值的具体值\n\n"
                                         "第四个参数，double类型的maxval，阈值的最大值\n\n"
                                         "第五个参数，阈值类型\n\n");

    bool ok=true;
    int thresh=ui->binaryThreshold->text().toDouble(&ok);
    if(ok==false){
        QMessageBox::information(this,
                                          tr("输入错误"),
                                          tr("请输入正确数字!"));
        return ;
    }
    std::string threSholdString=file.getFileString().toLocal8Bit().toStdString();
    Mat srcImage=imread(threSholdString,0);//输入图像
    Mat dstImage;//输出图像
    QImage* img=new QImage;//QT界面显示图像

    threshold(srcImage,dstImage,thresh,255,THRESH_BINARY);
    imwrite("temp.jpg",dstImage);
    if(showImg.showImage(ui,img,"temp.jpg",DSTImage)==-1){
        QMessageBox::information(this,
                                          tr("打开图像失败"),
                                          tr("打开图像失败!"));
    }
    delete img;

}

void MainWindow::on_radioButton_BinaryInv_clicked()
{
     ui->helpTextBrowser->clear();
     ui->helpTextBrowser->insertPlainText("当前点值大于阈值时，设置为0，否则取最大值 ，由src输入，dst输出\n\n"
                                          "函数原型为： \n"
                                          "double threshold(InputArray src, OutputArray dst, double thresh, double maxval, THRESH_BINARY_INV) "
                                          "第一个参数，InputArray类型的src，输入图像，即源图像，填单通道，8或32位浮点类型的Mat对象即可。 \n\n"
                                          "第二个参数，InputArray类型的dst，函数调用后的运算结果存放在这里，即这个参数用于存放输出结果，\n\n"
                                          "且和第一个参数中的Mat变量有一样的尺寸和类型"
                                          "第三个参数，double类型的thresh,阈值的具体值\n\n"
                                          "第四个参数，double类型的maxval，阈值的最大值\n\n"
                                          "第五个参数，阈值类型\n\n");
     bool ok=true;
     int thresh=ui->binaryThreshold->text().toDouble(&ok);
     if(ok==false){
         QMessageBox::information(this,
                                           tr("输入错误"),
                                           tr("请输入正确数字!"));
         return ;
     }
     std::string threSholdString=file.getFileString().toLocal8Bit().toStdString();
     Mat srcImage=imread(threSholdString,0);//输入图像
     Mat dstImage;//输出图像
     QImage* img=new QImage;//QT界面显示图像

     threshold(srcImage,dstImage,thresh,255,THRESH_BINARY_INV);
     imwrite("temp.jpg",dstImage);
     if(showImg.showImage(ui,img,"temp.jpg",DSTImage)==-1){
         QMessageBox::information(this,
                                           tr("打开图像失败"),
                                           tr("打开图像失败!"));
     }
     delete img;
}

void MainWindow::on_radioButton_TRUNC_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("当前点值大于阈值时，设置为阈值，否则不改变，由src输入，dst输出 \n\n"
                                         "函数原型为： \n"
                                         "double threshold(InputArray src, OutputArray dst, double thresh, double maxval,THRESH_TRUNC) "
                                         "第一个参数，InputArray类型的src，输入图像，即源图像，填单通道，8或32位浮点类型的Mat对象即可。 \n\n"
                                         "第二个参数，InputArray类型的dst，函数调用后的运算结果存放在这里，即这个参数用于存放输出结果，\n\n"
                                         "且和第一个参数中的Mat变量有一样的尺寸和类型"
                                         "第三个参数，double类型的thresh,阈值的具体值\n\n"
                                         "第四个参数，double类型的maxval，阈值的最大值\n\n"
                                         "第五个参数，阈值类型\n\n");

    bool ok=true;
    int thresh=ui->binaryThreshold->text().toDouble(&ok);
    if(ok==false){
        QMessageBox::information(this,
                                          tr("输入错误"),
                                          tr("请输入正确数字!"));
        return ;
    }
    std::string threSholdString=file.getFileString().toLocal8Bit().toStdString();
    Mat srcImage=imread(threSholdString,0);//输入图像
    Mat dstImage;//输出图像
    QImage* img=new QImage;//QT界面显示图像

    threshold(srcImage,dstImage,thresh,255,THRESH_TRUNC);
    imwrite("temp.jpg",dstImage);
    if(showImg.showImage(ui,img,"temp.jpg",DSTImage)==-1){
        QMessageBox::information(this,
                                          tr("打开图像失败"),
                                          tr("打开图像失败!"));
    }
    delete img;
}

void MainWindow::on_radioButton_TRZERO_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("当前点值大于阈值时，不改变，否则设置为0 ，由src输入，dst输出\n\n"
                                         "函数原型为： \n"
                                         "double threshold(InputArray src, OutputArray dst, double thresh, double maxval,THRESH_TOZERO) "
                                         "第一个参数，InputArray类型的src，输入图像，即源图像，填单通道，8或32位浮点类型的Mat对象即可。 \n\n"
                                         "第二个参数，InputArray类型的dst，函数调用后的运算结果存放在这里，即这个参数用于存放输出结果，\n\n"
                                         "且和第一个参数中的Mat变量有一样的尺寸和类型"
                                         "第三个参数，double类型的thresh,阈值的具体值\n\n"
                                         "第四个参数，double类型的maxval，阈值的最大值\n\n"
                                         "第五个参数，阈值类型\n\n");

    bool ok=true;
    int thresh=ui->binaryThreshold->text().toDouble(&ok);
    if(ok==false){
        QMessageBox::information(this,
                                          tr("输入错误"),
                                          tr("请输入正确数字!"));
        return ;
    }
    std::string threSholdString=file.getFileString().toLocal8Bit().toStdString();
    Mat srcImage=imread(threSholdString,0);//输入图像
    Mat dstImage;//输出图像
    QImage* img=new QImage;//QT界面显示图像

    threshold(srcImage,dstImage,thresh,255,THRESH_TOZERO);
    imwrite("temp.jpg",dstImage);
    if(showImg.showImage(ui,img,"temp.jpg",DSTImage)==-1){
        QMessageBox::information(this,
                                          tr("打开图像失败"),
                                          tr("打开图像失败!"));
    }
    delete img;
}

void MainWindow::on_radioButton_TRZERO_INV_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("当前点值大于阈值时，不改变，否则设置为0，由src输入，dst输出 \n\n"
                                         "函数原型为： \n"
                                         "double threshold(InputArray src, OutputArray dst, double thresh, double maxval,THRESH_TOZERO_INV) "
                                         "第一个参数，InputArray类型的src，输入图像，即源图像，填单通道，8或32位浮点类型的Mat对象即可。 \n\n"
                                         "第二个参数，InputArray类型的dst，函数调用后的运算结果存放在这里，即这个参数用于存放输出结果，\n\n"
                                         "且和第一个参数中的Mat变量有一样的尺寸和类型"
                                         "第三个参数，double类型的thresh,阈值的具体值\n\n"
                                         "第四个参数，double类型的maxval，阈值的最大值\n\n"
                                         "第五个参数，阈值类型\n\n");

    bool ok=true;
    int thresh=ui->binaryThreshold->text().toDouble(&ok);
    if(ok==false){
        QMessageBox::information(this,
                                          tr("输入错误"),
                                          tr("请输入正确数字!"));
        return ;
    }
    std::string threSholdString=file.getFileString().toLocal8Bit().toStdString();
    Mat srcImage=imread(threSholdString,0);//输入图像
    Mat dstImage;//输出图像
    QImage* img=new QImage;//QT界面显示图像

    threshold(srcImage,dstImage,thresh,255,THRESH_TOZERO_INV);
    imwrite("temp.jpg",dstImage);
    if(showImg.showImage(ui,img,"temp.jpg",DSTImage)==-1){
        QMessageBox::information(this,
                                          tr("打开图像失败"),
                                          tr("打开图像失败!"));
    }
    delete img;
}

void MainWindow::on_adaptiveRadioButton_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("采用自适应阈值操作，，由src输入，dst输出\n\n"
                                         "函数原型为： \n"
                                         "void adaptiveThreshold(InputArray src, OutputArray dst, double maxval, "
                                         "int adaptiveMethod, int thresholdType,int blockSize,double C)\n\n"

                                         "第一个参数，InputArray类型的src，输入图像，即源图像，填单通道，8或32位浮点类型的Mat对象即可。 \n\n"
                                         "第二个参数，InputArray类型的dst，函数调用后的运算结果存放在这里，即这个参数用于存放输出结果，\n\n"
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

    std::string threSholdString=file.getFileString().toLocal8Bit().toStdString();
    Mat srcImage=imread(threSholdString,0);//输入图像
    Mat dstImage;//输出图像
    QImage* img=new QImage;//QT界面显示图像
    int method,type,size;
    double C;
    adaptive_set.getAdaptiveSet(method,type,size,C);
    adaptiveThreshold(srcImage,dstImage,255,method,type,size,C);
    imwrite("temp.jpg",dstImage);
    if(showImg.showImage(ui,img,"temp.jpg",DSTImage)==-1){
        QMessageBox::information(this,
                                          tr("打开图像失败"),
                                          tr("打开图像失败!"));
    }
    delete img;
}

void MainWindow::on_adaptiveButton_clicked()
{
    AdaptiveThreshold *adaptivethreshold=new AdaptiveThreshold;
    adaptivethreshold->show();
}

void MainWindow::on_radioButtonIgnoreAspectRatio_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("输入图像与输出图像采用饱满填充");
    showImg.setShowImageType(0);
}

void MainWindow::on_radioButtonKeepAspectRatio_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("输入图像与输出图像采用按比例填充");
    showImg.setShowImageType(1);
}

void MainWindow::on_radioButtonArtWork_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("输入图像与输出图像显示原图");
    showImg.setShowImageType(2);
}

void MainWindow::on_boxFilterRadioButton_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("使用方框滤波来模糊一张图片，由src输入，dst输出\n\n"
                                         "函数原型为： \n"
                                         "void boxFilter(InputArray src, OutputArray dst, int ddepth, "
                                         "Size ksize, Point anchor=Point(-1,-1), boolnormalize=true, int borderType=BORDER_DEFAULT)\n\n"
                                         "第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可。该函数对通道是独立处理的，"
                                         "且可以处理任意通道数的图片，但需要注意，待处理的图片深度应该为CV_8U, CV_16U, CV_16S, CV_32F 以及 CV_64F之一。\n\n"
                                         "第二个参数，OutputArray类型的dst，即目标图像，需要和源图片有一样的尺寸和类型。\n\n"
                                         "第三个参数，int类型的ddepth，输出图像的深度，-1代表使用原图深度，即src.depth()。\n\n"
                                         "第四个参数，Size类型（对Size类型稍后有讲解）的ksize，内核的大小。\n\n"
                                         "一般这样写Size( w,h )来表示内核的大小( 其中，w 为像素宽度， h为像素高度)。Size（3,3）就表示3x3的核大小，Size（5,5）就表示5x5的核大小"
                                         "第五个参数，Point类型的anchor，表示锚点（即被平滑的那个点），注意他有默认值Point(-1,-1)。\n\n"
                                         "如果这个点坐标是负值的话，就表示取核的中心为锚点，所以默认值Point(-1,-1)表示这个锚点在核的中心。"
                                         "第六个参数，bool类型的normalize，默认值为true，一个标识符，表示内核是否被其区域归一化（normalized）了。\n\n"
                                         "第七个参数，int类型的borderType，用于推断图像外部像素的某种边界模式。有默认值BORDER_DEFAULT，我们一般不去管它。");
}

void MainWindow::on_contourRadioButton_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("敬请期待");
}

void MainWindow::on_convexHullRadioButton_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("敬请期待");
}

void MainWindow::on_circleRadioButton_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("敬请期待");
}

void MainWindow::on_rectRadioButton_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("敬请期待");
}
