/**
  ******************************************************************************
  * @file    adaptiveset.cpp
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    记录自适应阈值设置窗体中设置的值
  ******************************************************************************
  */

#include "adaptiveset.h"

adaptiveSet adaptive_set;//这个对象来存储自适应二值化设置的值

/**
* @brief  得到设置的值，写入类中
* @param  method 自适应方法
* @param  type 阈值方法
* @param  size 块大小
* @param  C 常数值
* @retval NONE
* @author  BugAngel
* @attention
*/
void adaptiveSet::setValue(int &method,int &type,int &size,double &C)
{
    this->adaptiveMethod=method;
    this->thresholdType=type;
    this->blockSize=size;
    this->C=C;
}

/**
* @brief  得到类中设置的值
* @param  method 自适应方法
* @param  type 阈值方法
* @param  size 块大小
* @param  C 常数值
* @retval NONE
* @author  BugAngel
* @attention
*/
void adaptiveSet::getValue(int &method,int &type,int &size,double &C)
{
    method=this->adaptiveMethod;
    type=this->thresholdType;
    size=this->blockSize;
    C=this->C;
}
