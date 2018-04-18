/**
  ******************************************************************************
  * @file    gaussianblurset.cpp
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    记录高斯滤波设置窗体中设置的值
  ******************************************************************************
  */

#include "gaussianblurset.h"

GaussianBlurSet gaussianblur_set;//这个对象来存储高斯滤波设置的值

/**
* @brief  得到设置的值，写入类中
* @param  width 像素宽度
* @param  height 像素高度
* @param  sigmaX sigmaX
* @param  sigmaY sigmaY
* @retval NONE
* @author  BugAngel
* @attention
*/
void GaussianBlurSet::setValue(int &width,int &height,double &sigmaX,double &sigmaY)
{
    this->width=width;
    this->height=height;
    this->sigmaX=sigmaX;
    this->sigmaY=sigmaY;
}

/**
* @brief  得到类中设置的值
* @param  width 像素宽度
* @param  height 像素高度
* @param  sigmaX sigmaX
* @param  sigmaY sigmaY
* @retval NONE
* @author  BugAngel
* @attention
*/
void GaussianBlurSet::getValue(int &width, int &height, double &sigmaX, double &sigmaY)
{
    width=this->width;
    height=this->height;
    sigmaX=this->sigmaX;
    sigmaY=this->sigmaY;
}
