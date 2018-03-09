#include "showimage.h"

ShowImage showImg;

ShowImage::setShowImageType(int showImageType){
    this->showImageType=showImageType;
    return 0;
}

ShowImage::getShowImageType(){
    return this->showImageType;
}

ShowImage::IgnoreAspectRatio(Ui::MainWindow *ui,QImage* img,QString s,int type)
{
    if(! ( img->load(s) ) ) //加载图像
    {
       return -1;
     }

    QPixmap pixmap = QPixmap::fromImage(*img);
    QLabel *label = new QLabel();
    if(type==0){
//        int width = ui->srcImage->width();
//        int height = ui->srcImage->height();
        int width=ui->scrollAreaSrcImage->width();
        int height=ui->scrollAreaSrcImage->height();
        QPixmap fitpixmap = pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充

        label->setPixmap(fitpixmap);
        ui->scrollAreaSrcImage->setWidget(label);
//        ui->srcImage->setPixmap(fitpixmap);
    }else if(type==1){
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

ShowImage::KeepAspectRatio(Ui::MainWindow *ui,QImage* img,QString s,int type)
{
    if(! ( img->load(s) ) ) //加载图像
    {
       return -1;
     }

    QPixmap pixmap = QPixmap::fromImage(*img);
    QLabel *label = new QLabel();
    if(type==0){
//        int width = ui->srcImage->width();
//        int height = ui->srcImage->height();
        int width=ui->scrollAreaSrcImage->width();
        int height=ui->scrollAreaSrcImage->height();
        QPixmap fitpixmap = pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例填充

        label->setPixmap(fitpixmap);
        ui->scrollAreaSrcImage->setWidget(label);
        delete label;
//        ui->srcImage->setPixmap(fitpixmap);
    }else if(type==1){
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

ShowImage::ARTWork(Ui::MainWindow *ui, QImage *img, QString s, int type){
    if(! ( img->load(s) ) ) //加载图像
    {
       return -1;
    }
    QLabel *label = new QLabel();
    if(type==0){       
        label->setPixmap(QPixmap::fromImage(*img));
        ui->scrollAreaSrcImage->setWidget(label);
    }else if(type==1){
        label->setPixmap(QPixmap::fromImage(*img));
        ui->scrollAreaDstImage->setWidget(label);        
    }
//    delete label;
    return 0;
}

ShowImage::showImage(Ui::MainWindow *ui, QImage *img, QString s, int type){
    int flag=ShowImage::showImageType;
    if(flag==0){
        showImg.IgnoreAspectRatio(ui,img,s,type);
    }else if(flag==1){
        showImg.KeepAspectRatio(ui,img,s,type);
    }else if(flag==2){
        showImg.ARTWork(ui,img,s,type);
    }
    return 0;
}
