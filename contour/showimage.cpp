#include "showimage.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include "file.h"

ShowImage showImg;

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

void MainWindow::on_radioButtonIgnoreAspectRatio_2_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("输入图像采用饱满填充");
    showImg.setSrcShowImageType(ShowImage::IGNORE);

    try{
        QImage* img=new QImage;//QT界面显示图像
        showImg.showImage(ui,file.getFileString(),showImg.SRCImage,showImg.getCurrentImageNum());
        delete img;
    }catch(std::exception& e){
        QMessageBox::information(this,
                                 tr("打开图像失败"),
                                 tr(e.what()));
    }
}

void MainWindow::on_radioButtonKeepAspectRatio_2_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("输入图像采用按比例填充");
    showImg.setSrcShowImageType(ShowImage::KEEPASPECT);

    try{
        QImage* img=new QImage;//QT界面显示图像
        showImg.showImage(ui,file.getFileString(),showImg.SRCImage,showImg.getCurrentImageNum());
        delete img;
    }catch(std::exception& e){
        QMessageBox::information(this,
                                 tr("打开图像失败"),
                                 tr(e.what()));
    }
}

void MainWindow::on_radioButtonArtWork_2_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("输入图像显示原图");
    showImg.setSrcShowImageType(ShowImage::ART);

    try{
        QImage* img=new QImage;//QT界面显示图像
        showImg.showImage(ui,file.getFileString(),showImg.SRCImage,showImg.getCurrentImageNum());
        delete img;
    }catch(std::exception& e){
        QMessageBox::information(this,
                                 tr("打开图像失败"),
                                 tr(e.what()));
    }
}

void MainWindow::on_radioButtonIgnoreAspectRatio_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("输出图像采用饱满填充");
    showImg.setDstShowImageType(ShowImage::IGNORE);

    try{
        int num=showImg.getCurrentImageNum();//当前图像数目
        QString tempFileName=QString::number(num)+showImg.ImgSuffix;
        QImage* img=new QImage;//QT界面显示图像
        showImg.showImage(ui,tempFileName,showImg.DSTImage,showImg.getCurrentImageNum());
        delete img;
    }catch(std::exception& e){
        QMessageBox::information(this,
                                 tr("打开图像失败"),
                                 tr(e.what()));
    }
}

void MainWindow::on_radioButtonKeepAspectRatio_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("输出图像采用按比例填充");
    showImg.setDstShowImageType(ShowImage::KEEPASPECT);

    try{
        int num=showImg.getCurrentImageNum();//当前图像数目
        QString tempFileName=QString::number(num)+showImg.ImgSuffix;
        QImage* img=new QImage;//QT界面显示图像
        showImg.showImage(ui,tempFileName,showImg.DSTImage,showImg.getCurrentImageNum());
        delete img;
    }catch(std::exception& e){
        QMessageBox::information(this,
                                 tr("打开图像失败"),
                                 tr(e.what()));
    }
}

void MainWindow::on_radioButtonArtWork_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("输出图像显示原图");
    showImg.setDstShowImageType(ShowImage::ART);

    try{
        int num=showImg.getCurrentImageNum();//当前图像数目
        QString tempFileName=QString::number(num)+showImg.ImgSuffix;
        QImage* img=new QImage;//QT界面显示图像
        showImg.showImage(ui,tempFileName,showImg.DSTImage,showImg.getCurrentImageNum());
        delete img;
    }catch(std::exception& e){
        QMessageBox::information(this,
                                 tr("打开图像失败"),
                                 tr(e.what()));
    }
}

ShowImage::IgnoreAspectRatio(Ui::MainWindow *ui,QString s,const int type,const int num)
{
    QImage* img=new QImage;
    if(! ( img->load(s) ) ) //加载图像
    {
        return -1;
    }

    QPixmap pixmap = QPixmap::fromImage(*img);
    QLabel *label = new QLabel();
    if(type==SRCImage){
        int width=ui->scrollAreaSrcImage->width();
        int height=ui->scrollAreaSrcImage->height();
        QPixmap fitpixmap = pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充

        label->setPixmap(fitpixmap);
        ui->scrollAreaSrcImage->setWidget(label);
    }
    else if(type==DSTImage)
    {
        int width=ui->scrollAreaDstImage->width();
        int height=ui->scrollAreaDstImage->height();
        QPixmap fitpixmap = pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
        label->setPixmap(fitpixmap);
        if(num==1)
        {
            ui->scrollAreaDstImage->setWidget(label);
        }
        else if(num==2)
        {
            ui->scrollAreaDstImage_2->setWidget(label);
        }
        else if(num==3)
        {
            ui->scrollAreaDstImage_3->setWidget(label);
        }
        else if(num==4)
        {
            ui->scrollAreaDstImage_4->setWidget(label);
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
    QLabel *label = new QLabel();
    if(type==SRCImage)
    {
        int width=ui->scrollAreaSrcImage->width();
        int height=ui->scrollAreaSrcImage->height();
        QPixmap fitpixmap = pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例填充

        label->setPixmap(fitpixmap);
        ui->scrollAreaSrcImage->setWidget(label);
    }
    else if(type==DSTImage)
    {
        int width=ui->scrollAreaDstImage->width();
        int height=ui->scrollAreaDstImage->height();
        QPixmap fitpixmap = pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例填充
        label->setPixmap(fitpixmap);
        if(num==1)
        {
            ui->scrollAreaDstImage->setWidget(label);
        }
        else if(num==2)
        {
            ui->scrollAreaDstImage_2->setWidget(label);
        }
        else if(num==3)
        {
            ui->scrollAreaDstImage_3->setWidget(label);
        }
        else if(num==4)
        {
            ui->scrollAreaDstImage_4->setWidget(label);
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
    QLabel *label = new QLabel();
    if(type==SRCImage)
    {
        label->setPixmap(QPixmap::fromImage(*img));
        ui->scrollAreaSrcImage->setWidget(label);
    }
    else if(type==DSTImage)
    {
        label->setPixmap(QPixmap::fromImage(*img));
        if(num==1)
        {            
            ui->scrollAreaDstImage->setWidget(label);
        }
        else if(num==2)
        {
            ui->scrollAreaDstImage_2->setWidget(label);
        }
        else if(num==3)
        {
            ui->scrollAreaDstImage_3->setWidget(label);
        }
        else if(num==4)
        {
            ui->scrollAreaDstImage_4->setWidget(label);
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
