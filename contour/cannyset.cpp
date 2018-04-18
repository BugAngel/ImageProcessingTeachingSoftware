/**
  ******************************************************************************
  * @file    cannyset.cpp
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    记录canny边缘检测设置窗体中设置的值
  ******************************************************************************
  */

#include "cannyset.h"

CannySet canny_set;//这个对象来存储canny边缘检测设置的值

/**
* @brief  得到设置的值，写入类中
* @param  threshold1 第一个滞后性阈值
* @param  threshold2 第一个滞后性阈值
* @param  apertureSize Sobel算子对应的孔径大小
* @retval NONE
* @author  BugAngel
* @attention
*/
void CannySet::setValue(double &threshold1,double &threshold2,int &apertureSize)
{
    this->threshold1=threshold1;
    this->threshold2=threshold2;
    this->apertureSize=apertureSize;
}

/**
* @brief  得到类中设置的值
* @param  threshold1 第一个滞后性阈值
* @param  threshold2 第一个滞后性阈值
* @param  apertureSize Sobel算子对应的孔径大小
* @retval NONE
* @author  BugAngel
* @attention
*/
void CannySet::getValue(double &threshold1,double &threshold2,int &apertureSize)
{
    threshold1=this->threshold1;
    threshold2=this->threshold2;
    apertureSize=this->apertureSize;
}
