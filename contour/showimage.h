#ifndef SHOWIMAGE_H
#define SHOWIMAGE_H

#include <QMainWindow>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

class ShowImage
{
private:
    int srcShowImageType=0;//0为饱满缩放，1为按比例缩放，2为原图
    int dstShowImageType=0;//0为饱满缩放，1为按比例缩放，2为原图
    int currentImageNum=1;//标记显示的输出图像序号

public:
    const static int SRCImage =0;
    const static int DSTImage =1;

    const static int IGNORE=0;
    const static int KEEPASPECT=1;
    const static int ART=2;

    QString ImgSuffix=".jpeg";

    void clearCurrentImageNum();
    void setCurrentImageNum(int num);
    int getCurrentImageNum();
    int setSrcShowImageType(int showImageType);
    int setDstShowImageType(int showImageType);
    int getSrcShowImageType();
    int getDstShowImageType();
    int showImage(Ui::MainWindow *ui,QString s,const int type,const int num);
    int IgnoreAspectRatio(Ui::MainWindow *ui,QString s,const int type,const int num);//饱满填充
    int KeepAspectRatio(Ui::MainWindow *ui,QString s,const int type,const int num);//按比例缩放
    int ARTWork(Ui::MainWindow *ui,QString s,const int type,const int num);//使用滚动条显示原图
};

extern ShowImage showImg;
#endif // SHOWIMAGE_H
