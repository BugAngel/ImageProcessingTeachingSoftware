#include "showimage.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include "file.h"
#include <QProcess>

ShowImage showImg;

void ShowImage::clearSrcImage()
{
    delete srcLabel;

    QString qstr="del "+QString::number(0)+showImg.getImageSuffix();
    QProcess p(0);
    p.start("cmd", QStringList()<<"/c"<<qstr);
    p.waitForStarted();
    p.waitForFinished();
}

void ShowImage::clearDstImage()
{
    delete dstLabel_1;
    delete dstLabel_2;
    delete dstLabel_3;
    delete dstLabel_4;

    QString qstr="del "+QString::number(1)+showImg.getImageSuffix()+" "
                       +QString::number(2)+showImg.getImageSuffix()+" "
                       +QString::number(3)+showImg.getImageSuffix()+" "
                       +QString::number(4)+showImg.getImageSuffix()+" ";
    QProcess p(0);
    p.start("cmd", QStringList()<<"/c"<<qstr);
    p.waitForStarted();
    p.waitForFinished();
}

QString ShowImage::getImageSuffix()
{
    return ImgSuffix;
}

void ShowImage::clearCurrentImageNum()
{
    currentImageNum=0;
}

void ShowImage::setCurrentImageNum(int num)
{
    currentImageNum=num;
}

ShowImage::getCurrentImageNum()
{
    return currentImageNum;
}

ShowImage::setSrcShowImageType(int showImageType){
    srcShowImageType=showImageType;
    return 0;
}

ShowImage::setDstShowImageType(int showImageType){
    dstShowImageType=showImageType;
    return 0;
}

ShowImage::getSrcShowImageType(){
    return srcShowImageType;
}

ShowImage::getDstShowImageType(){
    return dstShowImageType;
}

ShowImage::IgnoreAspectRatio(Ui::MainWindow *ui,QString s,const int type,const int num)
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
    }
    delete img;
    return 0;
}

ShowImage::KeepAspectRatio(Ui::MainWindow *ui, QString s, const int type,const int num)
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
    }
    delete img;
    return 0;
}

ShowImage::ARTWork(Ui::MainWindow *ui, QString s, const int type,const int num){
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
    }
    delete img;
    return 0;
}

ShowImage::showImage(Ui::MainWindow *ui, QString s, const int type,const int num){
    int flag;
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
    return 0;
}
