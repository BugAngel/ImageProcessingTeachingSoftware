/**
  ******************************************************************************
  * @file    file.h
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    文件操作
  ******************************************************************************
  */

#ifndef FILE_H
#define FILE_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
* @brief  存储文件名
* @author  BugAngel
* @attention
*/
class File
{
private:
    QString FileString;//文件路径
public:
    void setFileString(QString fileString);
    QString getFileString();
};

extern File file;
#endif // FILE_H
