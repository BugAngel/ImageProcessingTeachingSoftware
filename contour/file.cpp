/**
  ******************************************************************************
  * @file    file.cpp
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    文件操作
  ******************************************************************************
  */

#include "file.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "showimage.h"

File file;//这个变量来存储程序中使用的文件名

/**
* @brief  读取文件,设置文件名;
* @param  fileString 带有路径的文件名
* @retval NONE
* @author  BugAngel
* @attention 读取文件，重新设置文件名为ShowImage类中CurrentImageNum值减一，后缀为ShowImage类中ImgSuffix
*/
void File::setFileString(QString fileString)
{
    std::string stdFileString=fileString.toLocal8Bit().toStdString();
    cv::Mat srcImage=cv::imread(stdFileString);//输入图像

    int num=showImg.getCurrentImageNum()-1;
    QString tempQString=QString::number(num)+showImg.getImageSuffix();//输入图像默认为 输出图像序号减一.jpeg
    std::string stdFileString_2=tempQString.toLocal8Bit().toStdString();//默认的输入图像
    cv::imwrite(stdFileString_2,srcImage);
    FileString=QString::fromStdString(stdFileString_2);
}

/**
* @brief  返回类中保存的文件名;
* @param  NONE
* @retval 类中保存的文件名
* @author  BugAngel
* @attention
*/
QString File::getFileString()
{
    return FileString;
}
