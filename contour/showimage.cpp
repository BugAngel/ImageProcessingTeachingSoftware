#include "showimage.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include "file.h"

ShowImage showImg;

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
    showImg.setSrcShowImageType(IGNORE);

    try{
        QImage* img=new QImage;//QT界面显示图像
        showImg.showImage(ui,file.getFileString(),SRCImage);
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
    showImg.setSrcShowImageType(KEEPASPECT);

    try{
        QImage* img=new QImage;//QT界面显示图像
        showImg.showImage(ui,file.getFileString(),SRCImage);
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
    showImg.setSrcShowImageType(ART);

    try{
        QImage* img=new QImage;//QT界面显示图像
        showImg.showImage(ui,file.getFileString(),SRCImage);
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
    showImg.setDstShowImageType(IGNORE);

    try{
        QImage* img=new QImage;//QT界面显示图像
        showImg.showImage(ui,"temp.jpg",DSTImage);
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
    showImg.setDstShowImageType(KEEPASPECT);

    try{
        QImage* img=new QImage;//QT界面显示图像
        showImg.showImage(ui,"temp.jpg",DSTImage);
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
    showImg.setDstShowImageType(ART);

    try{
        QImage* img=new QImage;//QT界面显示图像
        showImg.showImage(ui,"temp.jpg",DSTImage);
        delete img;
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("打开图像失败"),
                                          tr(e.what()));
    }
}

ShowImage::IgnoreAspectRatio(Ui::MainWindow *ui,QString s,const int type)
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
    }else if(type==DSTImage){
        int width=ui->scrollAreaDstImage->width();
        int height=ui->scrollAreaDstImage->height();
        QPixmap fitpixmap = pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
        label->setPixmap(fitpixmap);
        ui->scrollAreaDstImage->setWidget(label);
    }
    delete img;
    return 0;
}

ShowImage::KeepAspectRatio(Ui::MainWindow *ui, QString s, const int type)
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
        QPixmap fitpixmap = pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例填充

        label->setPixmap(fitpixmap);
        ui->scrollAreaSrcImage->setWidget(label);
    }else if(type==DSTImage){
        int width=ui->scrollAreaDstImage->width();
        int height=ui->scrollAreaDstImage->height();
        QPixmap fitpixmap = pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例填充
        label->setPixmap(fitpixmap);
        ui->scrollAreaDstImage->setWidget(label);
    }
    delete img;
    return 0;
}

ShowImage::ARTWork(Ui::MainWindow *ui, QString s, const int type){
     QImage* img=new QImage;
    if(! ( img->load(s) ) ) //加载图像
    {
       return -1;
    }
    QLabel *label = new QLabel();
    if(type==SRCImage){
        label->setPixmap(QPixmap::fromImage(*img));
        ui->scrollAreaSrcImage->setWidget(label);
    }else if(type==DSTImage){
        label->setPixmap(QPixmap::fromImage(*img));
        ui->scrollAreaDstImage->setWidget(label);        
    }
        delete img;
    return 0;
}

ShowImage::showImage(Ui::MainWindow *ui, QString s, const int type){
    int flag;
    if(type==SRCImage){
        flag=getSrcShowImageType();
    }else if(type==DSTImage){
        flag=getDstShowImageType();
    }
    if(flag==IGNORE){
        showImg.IgnoreAspectRatio(ui,s,type);
    }else if(flag==KEEPASPECT){
        showImg.KeepAspectRatio(ui,s,type);
    }else if(flag==ART){
        showImg.ARTWork(ui,s,type);
    }
    return 0;
}
