/**
  ******************************************************************************
  * @file    contourset.h
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    记录轮廓检测设置窗体中设置的值
  ******************************************************************************
  */

#ifndef CONTOURSET_H
#define CONTOURSET_H

/**
* @brief  存储轮廓检测设置的值
* @author  BugAngel
* @attention
*/
class ContourSet
{
private:
    int thresh=100;
    int mode=0;
    int method=0;//四个宏定义依次对应1、2、3、4

public:
    void setValue(double &thresh,int &mode,int &method);
    void getValue(double &thresh,int &mode,int &method);
};

extern ContourSet contour_set;
#endif // CONTOURSET_H
