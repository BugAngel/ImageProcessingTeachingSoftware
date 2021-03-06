/**
  ******************************************************************************
  * @file    blurset.cpp
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    记录方框滤波设置窗体中设置的值
  ******************************************************************************
  */

#include "boxfilterset.h"

BoxFilterSet boxfilter_set;//这个对象来存储方框滤波设置的值

/**
* @brief  得到设置的值，写入类中
* @param  width 像素宽度
* @param  height 像素高度
* @retval NONE
* @author  BugAngel
* @attention
*/
void BoxFilterSet::setValue(int &width,int &height)
{
    this->width=width;
    this->height=height;
}

/**
* @brief  得到类中设置的值
* @param  width 像素宽度
* @param  height 像素高度
* @retval NONE
* @author  BugAngel
* @attention
*/
void BoxFilterSet::getValue( int &width, int &height)
{
    width=this->width;
    height=this->height;
}
