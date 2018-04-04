#ifndef CANNYSET_H
#define CANNYSET_H


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
