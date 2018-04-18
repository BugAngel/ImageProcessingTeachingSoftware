/**
  ******************************************************************************
  * @file    blurset.h
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    记录均值滤波设置窗体中设置的值
  ******************************************************************************
  */

#ifndef BLURSET_H
#define BLURSET_H

/**
* @brief  存储均值滤波设置的值
* @author  BugAngel
* @attention
*/
class BlurSet
{
private:
    int width=5;
    int height=5;

public:
    void setValue(int &width,int &height);
    void getValue(int &width,int &height);
};

extern BlurSet blur_set;
#endif // BLURSET_H
