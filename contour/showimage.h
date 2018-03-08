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

public:
    int IgnoreAspectRatio(Ui::MainWindow *ui,QImage* img,QString s,int type);//饱满填充
    int KeepAspectRatio(Ui::MainWindow *ui,QImage* img,QString s,int type);//按比例缩放
};

#endif // SHOWIMAGE_H
