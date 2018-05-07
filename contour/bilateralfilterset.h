/**
  ******************************************************************************
  * @file    bilateralfilterset.h
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    记录双边滤波设置窗体中设置的值
  ******************************************************************************
  */

#ifndef BILATERALFILTERSET_H
#define BILATERALFILTERSET_H

/**
* @brief  存储双边滤波设置的值
* @author  BugAngel
* @attention
*/
class BilateralFilterSet
{
private:
    int d=25;
    double sigmaColor=50;
    double sigmaSpace=12.5;

public:
    void setValue(int &d,double &sigmaColor, double &sigmaSpace);
    void getValue(int &d,double &sigmaColor, double &sigmaSpace);
};

extern BilateralFilterSet bilateralfilter_set;
#endif // BILATERALFILTERSET_H
