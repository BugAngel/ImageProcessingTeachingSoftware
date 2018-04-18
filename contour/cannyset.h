/**
  ******************************************************************************
  * @file    cannyset.h
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    记录canny边缘检测设置窗体中设置的值
  ******************************************************************************
  */

#ifndef CANNYSET_H
#define CANNYSET_H

/**
* @brief  存储canny边缘检测设置的值
* @author  BugAngel
* @attention
*/
class CannySet
{
private:
    double threshold1=150;
    double threshold2=100;
    int apertureSize=3;

public:
    void setValue(double &threshold1,double &threshold2,int &apertureSize);
    void getValue(double &threshold1,double &threshold2,int &apertureSize);
};

extern CannySet canny_set;
#endif // CANNYSET_H
