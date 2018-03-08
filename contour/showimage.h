#ifndef SHOWIMAGE_H
#define SHOWIMAGE_H

#include <QMainWindow>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

const int SRCImage =0;
const int DSTImage =1;

class ShowImage
{
private:
    int showImageType=0;//0为饱满缩放，1为按比例缩放，2为原图
public:
    int setShowImageType(int showImageType);
    int getShowImageType();
    int showImage(Ui::MainWindow *ui,QImage* img,QString s,int type);
    int IgnoreAspectRatio(Ui::MainWindow *ui,QImage* img,QString s,int type);//饱满填充
    int KeepAspectRatio(Ui::MainWindow *ui,QImage* img,QString s,int type);//按比例缩放
    int ARTWork(Ui::MainWindow *ui,QImage* img,QString s,int type);//使用滚动条显示原图
};

extern ShowImage showImg;
#endif // SHOWIMAGE_H
