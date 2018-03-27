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
        if(showImg.showImage(ui,img,file.getFileString(),SRCImage)==-1){
            QMessageBox::information(this,
                                              tr("打开图像失败"),
                                              tr("未找到输出图像!"));
        }
        delete img;
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("打开图像失败"),
                                          tr("打开图像失败,请输入正确图像!"));
    }
}

void MainWindow::on_radioButtonKeepAspectRatio_2_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("输入图像采用按比例填充");
    showImg.setSrcShowImageType(KEEPASPECT);

    try{
        QImage* img=new QImage;//QT界面显示图像
        if(showImg.showImage(ui,img,file.getFileString(),SRCImage)==-1){
            QMessageBox::information(this,
                                              tr("打开图像失败"),
                                              tr("未找到输出图像!"));
        }
        delete img;
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("打开图像失败"),
                                          tr("打开图像失败,请输入正确图像!"));
    }
}

void MainWindow::on_radioButtonArtWork_2_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("输入图像显示原图");
    showImg.setSrcShowImageType(ART);

    try{
        QImage* img=new QImage;//QT界面显示图像
        if(showImg.showImage(ui,img,file.getFileString(),SRCImage)==-1){
            QMessageBox::information(this,
                                              tr("打开图像失败"),
                                              tr("未找到输出图像!"));
        }
        delete img;
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("打开图像失败"),
                                          tr("打开图像失败,请输入正确图像!"));
    }
}

void MainWindow::on_radioButtonIgnoreAspectRatio_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("输出图像采用饱满填充");
    showImg.setDstShowImageType(IGNORE);

    try{
        QImage* img=new QImage;//QT界面显示图像
        if(showImg.showImage(ui,img,"temp.jpg",DSTImage)==-1){
            QMessageBox::information(this,
                                              tr("打开图像失败"),
                                              tr("未找到输出图像!"));
        }
        delete img;
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("打开图像失败"),
                                          tr("打开图像失败,请输入正确图像!"));
    }
}

void MainWindow::on_radioButtonKeepAspectRatio_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("输出图像采用按比例填充");
    showImg.setDstShowImageType(KEEPASPECT);

    try{
        QImage* img=new QImage;//QT界面显示图像
        if(showImg.showImage(ui,img,"temp.jpg",DSTImage)==-1){
            QMessageBox::information(this,
                                              tr("打开图像失败"),
                                              tr("未找到输出图像!"));
        }
        delete img;
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("打开图像失败"),
                                          tr("打开图像失败,请输入正确图像!"));
    }
}

void MainWindow::on_radioButtonArtWork_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("输出图像显示原图");
    showImg.setDstShowImageType(ART);

    try{
        QImage* img=new QImage;//QT界面显示图像
        if(showImg.showImage(ui,img,"temp.jpg",DSTImage)==-1){
            QMessageBox::information(this,
                                              tr("打开图像失败"),
                                              tr("未找到输出图像!"));
        }
        delete img;
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("打开图像失败"),
                                          tr("打开图像失败,请输入正确图像!"));
    }
}

ShowImage::IgnoreAspectRatio(Ui::MainWindow *ui,QImage* img,QString s,const int type)
{
    if(! ( img->load(s) ) ) //加载图像
    {
       return -1;
     }

    QPixmap pixmap = QPixmap::fromImage(*img);
    QLabel *label = new QLabel();
    if(type==SRCImage){
//        int width = ui->srcImage->width();
//        int height = ui->srcImage->height();
        int width=ui->scrollAreaSrcImage->width();
        int height=ui->scrollAreaSrcImage->height();
        QPixmap fitpixmap = pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充

        label->setPixmap(fitpixmap);
        ui->scrollAreaSrcImage->setWidget(label);
//        ui->srcImage->setPixmap(fitpixmap);
    }else if(type==DSTImage){
//        int width = ui->dstImage->width();
//        int height = ui->dstImage->height();
        int width=ui->scrollAreaDstImage->width();
        int height=ui->scrollAreaDstImage->height();
        QPixmap fitpixmap = pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
        label->setPixmap(fitpixmap);
        ui->scrollAreaDstImage->setWidget(label);      
//        ui->dstImage->setPixmap(fitpixmap);
    }
//    delete label;
    return 0;
}

ShowImage::KeepAspectRatio(Ui::MainWindow *ui,QImage* img,QString s,const int type)
{
    if(! ( img->load(s) ) ) //加载图像
    {
       return -1;
     }

    QPixmap pixmap = QPixmap::fromImage(*img);
    QLabel *label = new QLabel();
    if(type==SRCImage){
//        int width = ui->srcImage->width();
//        int height = ui->srcImage->height();
        int width=ui->scrollAreaSrcImage->width();
        int height=ui->scrollAreaSrcImage->height();
        QPixmap fitpixmap = pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例填充

        label->setPixmap(fitpixmap);
        ui->scrollAreaSrcImage->setWidget(label);
//        ui->srcImage->setPixmap(fitpixmap);
    }else if(type==DSTImage){
//        int width = ui->dstImage->width();
//        int height = ui->dstImage->height();
        int width=ui->scrollAreaDstImage->width();
        int height=ui->scrollAreaDstImage->height();
        QPixmap fitpixmap = pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例填充
        label->setPixmap(fitpixmap);
        ui->scrollAreaDstImage->setWidget(label);        
//        ui->dstImage->setPixmap(fitpixmap);
    }
//    delete label;
    return 0;
}

ShowImage::ARTWork(Ui::MainWindow *ui, QImage *img, QString s, const int type){
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
//    delete label;
    return 0;
}

ShowImage::showImage(Ui::MainWindow *ui, QImage *img, QString s, const int type){
    int flag;
    if(type==SRCImage){
        flag=getSrcShowImageType();
    }else if(type==DSTImage){
        flag=getDstShowImageType();
    }
    if(flag==IGNORE){
        showImg.IgnoreAspectRatio(ui,img,s,type);
    }else if(flag==KEEPASPECT){
        showImg.KeepAspectRatio(ui,img,s,type);
    }else if(flag==ART){
        showImg.ARTWork(ui,img,s,type);
    }
    return 0;
}
