/**
  ******************************************************************************
  * @file    sobelset.cpp
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    记录sobel算子设置窗体中设置的值
  ******************************************************************************
  */

#include "sobelset.h"

SobelSet sobel_set;//这个对象来存储sobel算子设置的值

/**
* @brief  得到设置的值，写入类中
* @param  dx X方向差分阶数
* @param  dy Y方向差分阶数
* @param  ksize sobel核大小
* @param  x_weight X方向所占权重
* @retval NONE
* @author  BugAngel
* @attention
*/
void SobelSet::setValue(int &dx, int &dy, int &ksize, double &x_weight)
{
    this->dx=dx;
    this->dy=dy;
    this->ksize=ksize;
    this->x_weight=x_weight;
}

/**
* @brief  得到类中设置的值
* @param  dx X方向差分阶数
* @param  dy Y方向差分阶数
* @param  ksize sobel核大小
* @param  x_weight X方向所占权重
* @retval NONE
* @author  BugAngel
* @attention
*/
void SobelSet::getValue(int &dx, int &dy, int &ksize, double &x_weight)
{
    dx=this->dx;
    dy=this->dy;
    ksize=this->ksize;
    x_weight=this->x_weight;
}
