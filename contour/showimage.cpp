#include "showimage.h"

ShowImage::IgnoreAspectRatio(Ui::MainWindow *ui,QImage* img,QString s,int type)
{
    if(! ( img->load(s) ) ) //加载图像
    {
       return -1;
     }

    QPixmap pixmap = QPixmap::fromImage(*img);

    if(type==0){
        int width = ui->srcImage->width();
        int height = ui->srcImage->height();
        QPixmap fitpixmap = pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
        ui->srcImage->setPixmap(fitpixmap);
    }else{
        int width = ui->dstImage->width();
        int height = ui->dstImage->height();
        QPixmap fitpixmap = pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
        ui->dstImage->setPixmap(fitpixmap);
    }

    return 0;
}

ShowImage::KeepAspectRatio(Ui::MainWindow *ui,QImage* img,QString s,int type)
{
    if(! ( img->load(s) ) ) //加载图像
    {
       return -1;
     }

    QPixmap pixmap = QPixmap::fromImage(*img);

    if(type==0){
        int width = ui->srcImage->width();
        int height = ui->srcImage->height();
        QPixmap fitpixmap = pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 饱满填充
        ui->srcImage->setPixmap(fitpixmap);
    }else{
        int width = ui->dstImage->width();
        int height = ui->dstImage->height();
        QPixmap fitpixmap = pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 饱满填充
        ui->dstImage->setPixmap(fitpixmap);
    }
    return 0;
}
