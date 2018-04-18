/**
  ******************************************************************************
  * @file    sobelset.h
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    记录sobel算子设置窗体中设置的值
  ******************************************************************************
  */

#ifndef SOBELSET_H
#define SOBELSET_H

/**
* @brief  存储sobel算子设置的值
* @author  BugAngel
* @attention
*/
class SobelSet
{
private:
    int dx=1;
    int dy=1;
    int ksize=3;
    double x_weight=0.5;

public:
    void setValue(int &dx,int &dy,int &ksize,double &x_weight);
    void getValue(int &dx,int &dy,int &ksize,double &x_weight);
};

extern SobelSet sobel_set;
#endif // SOBELSET_H
