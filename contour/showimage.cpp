/**
  ******************************************************************************
  * @file    showimage.cpp
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    图像显示相关操作
  ******************************************************************************
  */

#include "showimage.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include "file.h"
#include <QProcess>

ShowImage showImg;//这个对象来存储图像显示设置的值

/**
* @brief  清空输入图像的显示并删除写入磁盘的输入图像临时文件;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void ShowImage::clearSrcImage()
{
    delete srcLabel;

    QString qstr="del "+QString::number(0)+showImg.getImageSuffix();
    QProcess p(0);
    p.start("cmd", QStringList()<<"/c"<<qstr);
    p.waitForStarted();
    p.waitForFinished();
}

/**
* @brief  清空输出图像的显示并删除写入磁盘的输出图像临时文件;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void ShowImage::clearDstImage()
{
    delete dstLabel_1;
    delete dstLabel_2;
    delete dstLabel_3;
    delete dstLabel_4;
    delete dstLabel_5;
    delete dstLabel_6;

    QString qstr="del "+QString::number(1)+showImg.getImageSuffix()+" "
                       +QString::number(2)+showImg.getImageSuffix()+" "
                       +QString::number(3)+showImg.getImageSuffix()+" "
                       +QString::number(4)+showImg.getImageSuffix()+" "
                       +QString::number(5)+showImg.getImageSuffix()+" "
                       +QString::number(6)+showImg.getImageSuffix()+" ";
    QProcess p(0);
    p.start("cmd", QStringList()<<"/c"<<qstr);
    p.waitForStarted();
    p.waitForFinished();
}

/**
* @brief  得到设定的写入磁盘临时文件的后缀;
* @param  NONE
* @retval 被设定的写入磁盘临时文件的后缀
* @author  BugAngel
* @attention
*/
QString ShowImage::getImageSuffix()
{
    return ImgSuffix;
}

/**
* @brief  设置当前的输出图像序号;
* @param  num 需要被设置的图像序号
* @retval NONE
* @author  BugAngel
* @attention
*/
void ShowImage::setCurrentImageNum(int num)
{
    currentImageNum=num;
}

/**
* @brief  得到当前的输出图像序号;
* @param  NONE
* @retval 当前的输出图像序号
* @author  BugAngel
* @attention
*/
int ShowImage::getCurrentImageNum()
{
    return currentImageNum;
}

/**
* @brief  设置输入图像模式;
* @param  显示图像模式
* @retval NONE
* @author  BugAngel
* @attention
*/
void ShowImage::setSrcShowImageType(int showImageType){
    srcShowImageType=showImageType;
}

/**
* @brief  设置输出图像模式;
* @param  显示图像模式
* @retval NONE
* @author  BugAngel
* @attention
*/
void ShowImage::setDstShowImageType(int showImageType){
    dstShowImageType=showImageType;
}

/**
* @brief  得到当前输入图像显示模式;
* @param  NONE
* @retval 当前输入图像显示模式
* @author  BugAngel
* @attention
*/
int ShowImage::getSrcShowImageType(){
    return srcShowImageType;
}

/**
* @brief  得到当前输出图像显示模式;
* @param  NONE
* @retval 当前输出图像显示模式
* @author  BugAngel
* @attention
*/
int ShowImage::getDstShowImageType(){
    return dstShowImageType;
}

/**
* @brief  以饱满填充显示模式显示图像;
* @param  ui 窗口指针
* @param  s 文件名
* @param  type 输入图像与输出图像模式
* @param  num 输入图像序号，仅在type为输出图像时起作用
* @retval 0 显示成功
* @retval -1 读取文件失败
* @author  BugAngel
* @attention
*/
int ShowImage::IgnoreAspectRatio(Ui::MainWindow* ui,QString s,const int type,const int num)
{
    QImage* img=new QImage;
    if(! ( img->load(s) ) ) //加载图像
    {
        return -1;
    }

    QPixmap pixmap = QPixmap::fromImage(*img);
    if(type==SRCImage){
        int width=ui->scrollAreaSrcImage->width();
        int height=ui->scrollAreaSrcImage->height();
        QPixmap fitpixmap = pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充

        srcLabel = new QLabel();
        srcLabel->setPixmap(fitpixmap);
        ui->scrollAreaSrcImage->setWidget(srcLabel);
    }
    else if(type==DSTImage)
    {
        int width=ui->scrollAreaDstImage->width();
        int height=ui->scrollAreaDstImage->height();
        QPixmap fitpixmap = pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充        
        if(num==1)
        {
            dstLabel_1 = new QLabel();
            dstLabel_1->setPixmap(fitpixmap);
            ui->scrollAreaDstImage->setWidget(dstLabel_1);
        }
        else if(num==2)
        {
            dstLabel_2 = new QLabel();
            dstLabel_2->setPixmap(fitpixmap);
            ui->scrollAreaDstImage_2->setWidget(dstLabel_2);
        }
        else if(num==3)
        {
            dstLabel_3 = new QLabel();
            dstLabel_3->setPixmap(fitpixmap);
            ui->scrollAreaDstImage_3->setWidget(dstLabel_3);
        }
        else if(num==4)
        {
            dstLabel_4 = new QLabel();
            dstLabel_4->setPixmap(fitpixmap);
            ui->scrollAreaDstImage_4->setWidget(dstLabel_4);
        }
        else if(num==5)
        {
            dstLabel_5 = new QLabel();
            dstLabel_5->setPixmap(fitpixmap);
            ui->scrollAreaDstImage_5->setWidget(dstLabel_5);
        }
        else if(num==6)
        {
            dstLabel_6 = new QLabel();
            dstLabel_6->setPixmap(fitpixmap);
            ui->scrollAreaDstImage_6->setWidget(dstLabel_6);
        }
    }
    delete img;
    return 0;
}

/**
* @brief  以按比例填充显示模式显示图像;
* @param  ui 窗口指针
* @param  s 文件名
* @param  type 输入图像与输出图像模式
* @param  num 输入图像序号，仅在type为输出图像时起作用
* @retval 0 显示成功
* @retval -1 读取文件失败
* @author  BugAngel
* @attention
*/
ShowImage::KeepAspectRatio(Ui::MainWindow* ui, QString s, const int type,const int num)
{
    QImage* img=new QImage;

    if(! ( img->load(s) ) ) //加载图像
    {
        return -1;
    }

    QPixmap pixmap = QPixmap::fromImage(*img);
    if(type==SRCImage)
    {
        int width=ui->scrollAreaSrcImage->width();
        int height=ui->scrollAreaSrcImage->height();
        QPixmap fitpixmap = pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例填充

        srcLabel = new QLabel();
        srcLabel->setPixmap(fitpixmap);
        ui->scrollAreaSrcImage->setWidget(srcLabel);
    }
    else if(type==DSTImage)
    {
        int width=ui->scrollAreaDstImage->width();
        int height=ui->scrollAreaDstImage->height();
        QPixmap fitpixmap = pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例填充
        if(num==1)
        {
            dstLabel_1 = new QLabel();
            dstLabel_1->setPixmap(fitpixmap);
            ui->scrollAreaDstImage->setWidget(dstLabel_1);
        }
        else if(num==2)
        {
            dstLabel_2 = new QLabel();
            dstLabel_2->setPixmap(fitpixmap);
            ui->scrollAreaDstImage_2->setWidget(dstLabel_2);
        }
        else if(num==3)
        {
            dstLabel_3 = new QLabel();
            dstLabel_3->setPixmap(fitpixmap);
            ui->scrollAreaDstImage_3->setWidget(dstLabel_3);
        }
        else if(num==4)
        {
            dstLabel_4 = new QLabel();
            dstLabel_4->setPixmap(fitpixmap);
            ui->scrollAreaDstImage_4->setWidget(dstLabel_4);
        }
        else if(num==5)
        {
            dstLabel_5 = new QLabel();
            dstLabel_5->setPixmap(fitpixmap);
            ui->scrollAreaDstImage_5->setWidget(dstLabel_5);
        }
        else if(num==6)
        {
            dstLabel_6 = new QLabel();
            dstLabel_6->setPixmap(fitpixmap);
            ui->scrollAreaDstImage_6->setWidget(dstLabel_6);
        }
    }
    delete img;
    return 0;
}

/**
* @brief  以显示原图显示模式显示图像，如果图像过大，会自动出现滚动条
* @param  ui 窗口指针
* @param  s 文件名
* @param  type 输入图像与输出图像模式
* @param  num 输入图像序号，仅在type为输出图像时起作用
* @retval 0 显示成功
* @retval -1 读取文件失败
* @author  BugAngel
* @attention
*/
ShowImage::ARTWork(Ui::MainWindow* ui, QString s, const int type,const int num){
    QImage* img=new QImage;
    if(! ( img->load(s) ) ) //加载图像
    {
        return -1;
    }
    if(type==SRCImage)
    {
        srcLabel = new QLabel();
        srcLabel->setPixmap(QPixmap::fromImage(*img));
        ui->scrollAreaSrcImage->setWidget(srcLabel);
    }
    else if(type==DSTImage)
    {
        if(num==1)
        {
            dstLabel_1 = new QLabel();
            dstLabel_1->setPixmap(QPixmap::fromImage(*img));
            ui->scrollAreaDstImage->setWidget(dstLabel_1);
        }
        else if(num==2)
        {
            dstLabel_2 = new QLabel();
            dstLabel_2->setPixmap(QPixmap::fromImage(*img));
            ui->scrollAreaDstImage_2->setWidget(dstLabel_2);
        }
        else if(num==3)
        {
            dstLabel_3 = new QLabel();
            dstLabel_3->setPixmap(QPixmap::fromImage(*img));
            ui->scrollAreaDstImage_3->setWidget(dstLabel_3);
        }
        else if(num==4)
        {
            dstLabel_4 = new QLabel();
            dstLabel_4->setPixmap(QPixmap::fromImage(*img));
            ui->scrollAreaDstImage_4->setWidget(dstLabel_4);
        }
        else if(num==5)
        {
            dstLabel_5 = new QLabel();
            dstLabel_5->setPixmap(QPixmap::fromImage(*img));
            ui->scrollAreaDstImage_5->setWidget(dstLabel_5);
        }
        else if(num==6)
        {
            dstLabel_6 = new QLabel();
            dstLabel_6->setPixmap(QPixmap::fromImage(*img));
            ui->scrollAreaDstImage_6->setWidget(dstLabel_6);
        }
    }
    delete img;
    return 0;
}

/**
* @brief  以饱满填充显示模式显示图像;
* @param  ui 窗口指针
* @param  s 文件名
* @param  type 输入图像与输出图像模式
* @param  num 输入图像序号，仅在type为输出图像时起作用
* @retval NONE
* @author  BugAngel
* @attention
*/
void ShowImage::showImage(Ui::MainWindow* ui, QString s, const int type,const int num){
    int flag=-1;
    if(type==SRCImage)
    {
        flag=srcShowImageType;
    }
    else if(type==DSTImage)
    {
        flag=dstShowImageType;
    }
    if(flag==IGNORE)
    {
        showImg.IgnoreAspectRatio(ui,s,type,num);
    }
    else if(flag==KEEPASPECT)
    {
        showImg.KeepAspectRatio(ui,s,type,num);
    }
    else if(flag==ART)
    {
        showImg.ARTWork(ui,s,type,num);
    }
}
