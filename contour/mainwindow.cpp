/**
  ******************************************************************************
  * @file    mainwindow.cpp
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    主窗口控件与按钮组默认值设置与菜单栏控件功能
  ******************************************************************************
  */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QMessageBox>
#include "file.h"
#include "showimage.h"
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

/**
* @brief  构造函数，设置各个按钮组与默认按下的单选按钮
* @author  BugAngel
* @attention
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->helpTextBrowser->setFontPointSize(14);
    ui->helpTextBrowser->setFontFamily("楷体");

    QFile txtFile("initializtion.txt");
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

    ui->binaryButtonGroup->setId(ui->radioButton_Binary,0);//设置灰度与二值化按钮组的ID值
    ui->binaryButtonGroup->setId(ui->radioButton_BinaryInv,1);
    ui->binaryButtonGroup->setId(ui->radioButton_TRUNC,2);
    ui->binaryButtonGroup->setId(ui->radioButton_TOZERO,3);
    ui->binaryButtonGroup->setId(ui->radioButton_TOZERO_INV,4);
    ui->binaryButtonGroup->setId(ui->adaptiveRadioButton,5);
    ui->binaryButtonGroup->setId(ui->grayRadioButton,6);
    ui->grayRadioButton->setChecked(true);//设置默认选项

    ui->edgeButtonGroup->setId(ui->cannyRadioButton,0);
    ui->edgeButtonGroup->setId(ui->sobelRadioButton,1);
    ui->edgeButtonGroup->setId(ui->laplacianRadioButton,2);
    ui->edgeButtonGroup->setId(ui->scharrRadioButton,3);
    ui->edgeButtonGroup->setId(ui->contourRadioButton,4);//设置轮廓检测按钮组的ID值
    ui->cannyRadioButton->setChecked(true);//设置默认选项

    ui->srcImageButtonGroup->setId(ui->radioButtonIgnoreAspectRatio_2,0);//设置输入图像显示方式按钮组的ID值
    ui->srcImageButtonGroup->setId(ui->radioButtonKeepAspectRatio_2,1);
    ui->srcImageButtonGroup->setId(ui->radioButtonArtWork_2,2);
    ui->radioButtonIgnoreAspectRatio_2->setChecked(true);

    ui->dstImageButtonGroup->setId(ui->radioButtonIgnoreAspectRatio,0);//设置输出图像显示方式按钮组的ID值
    ui->dstImageButtonGroup->setId(ui->radioButtonKeepAspectRatio,1);
    ui->dstImageButtonGroup->setId(ui->radioButtonArtWork,2);
    ui->radioButtonIgnoreAspectRatio->setChecked(true);

    ui->BlurButtonGroup->setId(ui->boxFilterRadioButton,0);
    ui->BlurButtonGroup->setId(ui->blurRadioButton,1);
    ui->BlurButtonGroup->setId(ui->gaussianBlurRadioButton,2);
    ui->BlurButtonGroup->setId(ui->medianFilterRadioButton,3);
    ui->BlurButtonGroup->setId(ui->bilateralFilterRadioButton,4);
    ui->boxFilterRadioButton->setChecked(true);//设置默认选项

    ui->morphButtonGroup->setId(ui->erodeRadioButton,0);
    ui->morphButtonGroup->setId(ui->dilateRadioButton,1);
    ui->morphButtonGroup->setId(ui->morphOpenRadioButton,2);
    ui->morphButtonGroup->setId(ui->morphCloseRadioButton,3);
    ui->morphButtonGroup->setId(ui->morphGradientRadioButton,4);
    ui->morphButtonGroup->setId(ui->morphTopHatRadioButton,5);
    ui->morphButtonGroup->setId(ui->morphBlackHatRadioButton,6);
    ui->erodeRadioButton->setChecked(true);//设置默认选项

    ui->practicalButtonGroup->setId(ui->maxContourCenterRadioButton,0);
    ui->practicalButtonGroup->setId(ui->searchPolygonRadioButton,1);
    ui->practicalButtonGroup->setId(ui->faceDetectionRadioButton,2);
    ui->practicalButtonGroup->setId(ui->asciiRadioButton,3);
    ui->maxContourCenterRadioButton->setChecked(true);//设置默认选项

    ui->tabWidget->setCurrentIndex(0);//设置图像操作Tab的默认显示
    ui->dstImageTabWidget->setCurrentIndex(0);//设置图像显示Tab的默认显示

    QStringList tempQStringList;
    tempQStringList<<"缩放旋转与对称";
    tempQStringList<<"图像滤波";
    tempQStringList<<"形态学处理";
    tempQStringList<<"灰度与阈值化";
    tempQStringList<<"边缘与轮廓";
    tempQStringList<<"实践项目";
    ui->firstOperateComboBox->addItems(tempQStringList);
    ui->secondOperateComboBox->addItems(tempQStringList);
    ui->thirdOperateComboBox->addItems(tempQStringList);
    ui->forthOperateComboBox->addItems(tempQStringList);
    ui->fifthOperateComboBox->addItems(tempQStringList);
    ui->sixthOperateComboBox->addItems(tempQStringList);
}

/**
* @brief  析构函数，删除临时产生的文件
* @author  BugAngel
* @attention
*/
MainWindow::~MainWindow()
{
    showImg.clearSrcImage();
    showImg.clearDstImage();
    delete ui;
}

/**
* @brief  保存图像按键按下，保存正在显示的图像
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_savePushButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("文件另存为"),
            tr("未命名.png"),
            tr( "PNG图片(*.png);;\
                JPEG文件 (*.jpg *.jpeg *.jpe);;\
                Windows位图 (*.bmp *.dib);; \
                便携文件格式(*.pbm *.pgm *.ppm);;\
                TIFF文件 (*.tif *.tiff)"));

    if(!fileName.isEmpty())
    {
        QString tempFileName;
        cv::Mat img;
        switch(ui->dstImageTabWidget->currentIndex())
        {
        case 0:
            tempFileName=QString::number(1)+showImg.getImageSuffix();
            img=cv::imread(tempFileName.toLocal8Bit().toStdString());
            cv::imwrite(fileName.toLocal8Bit().data(),img);
            break;
        case 1:
            tempFileName=QString::number(2)+showImg.getImageSuffix();
            img=cv::imread(tempFileName.toLocal8Bit().toStdString());
            cv::imwrite(fileName.toLocal8Bit().data(),img);
            break;
        case 2:
            tempFileName=QString::number(3)+showImg.getImageSuffix();
            img=cv::imread(tempFileName.toLocal8Bit().toStdString());
            cv::imwrite(fileName.toLocal8Bit().data(),img);
            break;
        case 3:
            tempFileName=QString::number(4)+showImg.getImageSuffix();
            img=cv::imread(tempFileName.toLocal8Bit().toStdString());
            cv::imwrite(fileName.toLocal8Bit().data(),img);
            break;
        case 4:
            tempFileName=QString::number(5)+showImg.getImageSuffix();
            img=cv::imread(tempFileName.toLocal8Bit().toStdString());
            cv::imwrite(fileName.toLocal8Bit().data(),img);
            break;
        case 5:
            tempFileName=QString::number(6)+showImg.getImageSuffix();
            img=cv::imread(tempFileName.toLocal8Bit().toStdString());
            cv::imwrite(fileName.toLocal8Bit().data(),img);
            break;
        }
    }
    else
    {
        QMessageBox::information(this,
                                tr("保存文件失败"),
                                tr("请输入文件名"));
    }
}

/**
* @brief  菜单栏中按下打开图像，执行打开图像按键操作
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_openImageAction_triggered()
{
    on_openImagePushButton_clicked();
}

/**
* @brief  菜单栏中按下保存图像，执行保存图像按键操作
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_saveImageAction_triggered()
{
    on_savePushButton_clicked();
}
