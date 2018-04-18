/**
  ******************************************************************************
  * @file    adaptiveset.h
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    记录自适应阈值设置窗体中设置的值
  ******************************************************************************
  */

#ifndef ADAPTIVESET_H
#define ADAPTIVESET_H

/**
* @brief  存储自适应二值化设置的值
* @author  BugAngel
* @attention
*/
class adaptiveSet
{
private:
    int adaptiveMethod=0;
    int thresholdType=0;
    int blockSize=3;
    double C=5;

public:
    void setValue(int &method,int &type,int &size,double &C);
    void getValue(int &method,int &type,int &size,double &C);
};

extern adaptiveSet adaptive_set;
#endif // ADAPTIVESET_H
