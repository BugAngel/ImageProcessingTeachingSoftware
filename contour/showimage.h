/**
  ******************************************************************************
  * @file    showimage.h
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    图像显示相关操作
  ******************************************************************************
  */

#ifndef SHOWIMAGE_H
#define SHOWIMAGE_H

#include <QMainWindow>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

/**
* @brief  存储图像显示类型，提供显示图像方法
* @author  BugAngel
* @attention
*/
class ShowImage
{
private:
    int srcShowImageType=0;//0为饱满缩放，1为按比例缩放，2为原图
    int dstShowImageType=0;//0为饱满缩放，1为按比例缩放，2为原图
    int currentImageNum=1;//标记显示的输出图像序号

    QString ImgSuffix=".jpeg";

    QLabel *srcLabel;
    QLabel *dstLabel_1;
    QLabel *dstLabel_2;
    QLabel *dstLabel_3;
    QLabel *dstLabel_4;
    QLabel *dstLabel_5;
    QLabel *dstLabel_6;

public:
    const static int SRCImage =0;
    const static int DSTImage =1;

    const static int IGNORE=0;
    const static int KEEPASPECT=1;
    const static int ART=2;

    QString getImageSuffix();
    void clearSrcImage();
    void clearDstImage();
    void setCurrentImageNum(int num);
    int getCurrentImageNum();
    void setSrcShowImageType(int showImageType);
    void setDstShowImageType(int showImageType);
    int getSrcShowImageType();
    int getDstShowImageType();
    int IgnoreAspectRatio(Ui::MainWindow *ui,QString s,const int type,const int num);//饱满填充
    int KeepAspectRatio(Ui::MainWindow *ui,QString s,const int type,const int num);//按比例缩放
    int ARTWork(Ui::MainWindow *ui,QString s,const int type,const int num);//使用滚动条显示原图
    void showImage(Ui::MainWindow *ui,QString s,const int type,const int num);
};

extern ShowImage showImg;
#endif // SHOWIMAGE_H
