/**
  ******************************************************************************
  * @file    bilateralfilterset.h
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    记录双边滤波设置窗体中设置的值
  ******************************************************************************
  */

#include "bilateralfilterset.h"

BilateralFilterSet bilateralfilter_set;//这个对象来存储双边滤波设置的值

/**
* @brief  得到设置的值，写入类中
* @param  d 自适应方法
* @param  sigmaColor 阈值方法
* @param  sigmaSpace 块大小
* @retval NONE
* @author  BugAngel
* @attention
*/
void BilateralFilterSet::setValue(int &d, double &sigmaColor, double &sigmaSpace)
{
    this->d=d;
    this->sigmaColor=sigmaColor;
    this->sigmaSpace=sigmaSpace;
}

/**
* @brief  得到类中设置的值
* @param  d 自适应方法
* @param  sigmaColor 阈值方法
* @param  sigmaSpace 块大小
* @retval NONE
* @author  BugAngel
* @attention
*/
void BilateralFilterSet::getValue(int &d, double &sigmaColor, double &sigmaSpace)
{
    d=this->d;
    sigmaColor=this->sigmaColor;
    sigmaSpace=this->sigmaSpace;
}
