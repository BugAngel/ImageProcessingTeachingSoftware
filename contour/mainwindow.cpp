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
#include "QProcess"
#include "boxfilter.h"

using namespace  cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->helpTextBrowser->setFontPointSize(14);
    ui->helpTextBrowser->setFontFamily("楷体");
    ui->helpTextBrowser->insertPlainText("王容出品，必属精品\n\n");
    ui->helpTextBrowser->insertPlainText("点击图像处理设置里的选项即可立即处理图像，无需任何繁杂操作\n\n");
    ui->helpTextBrowser->insertPlainText("等我调剂归来，再来做轮廓检测和形态学滤波");

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
    QProcess p(0);
    p.start("cmd", QStringList()<<"/c"<<"del temp.jpg");
    p.waitForStarted();
    p.waitForFinished();
    delete ui;
}

void MainWindow::on_actionOpenImg_triggered()
{
    qDebug()<< "打开文件键有反应";

    file.setFileString(QFileDialog::getOpenFileName(this,tr("打开图像文件"),"/"));

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

