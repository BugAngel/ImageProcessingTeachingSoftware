/**
  ******************************************************************************
  * @file    contourset.cpp
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    记录轮廓检测设置窗体中设置的值
  ******************************************************************************
  */

#include "contourset.h"

ContourSet contour_set;//这个对象来存储轮廓检测设置的值

/**
* @brief  得到设置的值，写入类中
* @param  thresh 阈值
* @param  mode 轮廓检索模式
* @param  method 轮廓近似方法
* @retval NONE
* @author  BugAngel
* @attention
*/
void ContourSet::setValue(double &thresh,int &mode,int &method)
{
    this->thresh=thresh;
    this->mode=mode;
    this->method=method;
}

/**
* @brief  得到类中设置的值
* @param  thresh 阈值
* @param  mode 轮廓检索模式
* @param  method 轮廓近似方法
* @retval NONE
* @author  BugAngel
* @attention
*/
void ContourSet::getValue(double &thresh,int &mode,int &method)
{
    thresh=this->thresh;
    mode=this->mode;
    method=this->method;
}
