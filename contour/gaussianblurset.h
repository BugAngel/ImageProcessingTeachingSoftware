/**
  ******************************************************************************
  * @file    gaussianblurset.h
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    记录高斯滤波设置窗体中设置的值
  ******************************************************************************
  */

#ifndef GAUSSIANBLURSET_H
#define GAUSSIANBLURSET_H

/**
* @brief  存储高斯滤波设置的值
* @author  BugAngel
* @attention
*/
class GaussianBlurSet
{
private:
    int width=5;
    int height=5;
    double sigmaX=0;
    double sigmaY=0;

public:
    void setValue(int &width,int &height,double &sigmaX,double &sigmaY);
    void getValue(int &width,int &height,double &sigmaX,double &sigmaY);
};
extern GaussianBlurSet gaussianblur_set;
#endif // GAUSSIANBLURSET_H
