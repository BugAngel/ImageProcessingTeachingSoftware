#ifndef FILE_H
#define FILE_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

class File
{
private:
    QString FileString;//文件路径
public:
    void setFileString(QString fileString);
    QString getFileString();
};

#endif // FILE_H
