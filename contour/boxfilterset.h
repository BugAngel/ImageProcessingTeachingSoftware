/**
  ******************************************************************************
  * @file    blurset.h
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    记录方框滤波设置窗体中设置的值
  ******************************************************************************
  */

#ifndef BOXFILTERSET_H
#define BOXFILTERSET_H

/**
* @brief  存储方框滤波设置的值
* @author  BugAngel
* @attention
*/
class BoxFilterSet
{
private:
    int width=5;
    int height=5;

public:
    void setValue(int &width,int &height);
    void getValue(int &width,int &height);
};

extern BoxFilterSet boxfilter_set;
#endif // BOXFILTERSET_H
